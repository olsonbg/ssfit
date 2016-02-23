#include <vector>
#include <sstream>
#include "readPVT.h"
#include "readPVTblock.h"
#include "curves.h"
#include "savedata.h"
#include "fitstatistics.h"
#include "outlog.h"
#include "flags.h"
#include "ssfit.h"
#include "yfit.h"
#include "process.h"

extern FitStatistics minimize;

bool process( const std::string ifile, const std::string ifileTempRanges,
              const std::string saveprefix,
              const double Pstar, const double Vstar, const double Tstar,
              const unsigned int numpoints,
              const unsigned int flags )
{
	// P and T are inputs.
	std::vector< std::vector< double > > pts;
	// V was measured
	std::vector< double > volumes;
	// Variances of the measured values
	std::vector<double> var;
	// Range of temperatures, for each pressure, to use for fitting and curve
	// generation.
	std::vector< std::vector< double > > *ranges = new std::vector< std::vector< double > >;

	if (ifileTempRanges.empty() )
	{
		delete ranges;
		ranges = NULL;
	}

	std::stringstream ofilename;
	ofilename << saveprefix << "-summary.dat";

	outlog log(ofilename.str().c_str());

	// Get valid temperature ranges
	if( ( ranges != NULL) &&
	    !readTempRanges(ifileTempRanges, ranges, flags & Flags::KELVIN) )
	{
		std::cout << "Error reading " << ifileTempRanges << "\n";
		delete ranges;
		return(false);
	}

	if ( flags & Flags::BLOCKDATA )
	{
		if( !readPVTblock( ifile, &pts, &volumes, &var, ranges, flags & Flags::KELVIN ) )
		{
			if ( ranges != NULL ) delete ranges;
			return(false);
		}
	}
	else
	{
		if( !readPVT( ifile, &pts, &volumes, &var, ranges,  flags & Flags::KELVIN ) )
		{
			if ( ranges != NULL ) delete ranges;
			return(false);
		}
	}

	if ( flags & Flags::DATAONLY )
	{
		double Pprev = pts[0][0];
		log << "# " << pts[0][0] << "\n";
		for(unsigned int i=0; i < volumes.size(); ++i)
		{
			// Add a blank line between groups of pressures
			if ( pts[i][0] != Pprev )
			{
				log << "\n";
				log << "# " << pts[i][0] << "\n";
			}

			// log << pts[i][0] << " "
			log << pts[i][1] << " "
			          << volumes[i] << "\n";

			Pprev = pts[i][0];
		}
		if ( ranges != NULL ) delete ranges;
		return(true);
	}

	log << "Data points: " << pts.size() << "\n\n";

	minimize.Initialize( pts, volumes, var, 0 );

	// Only fit y. Typically used for temperature below the glass transition,
	// where the SS-EOS equilibrium condition does not hold.
	if ( flags & Flags::YONLY )
	{
		yfit( ofilename.str(), Pstar, Vstar, Tstar );
		save_PVTy( &saveprefix );

		if ( ranges != NULL ) delete ranges;
		return true;
	}


	double fitresults[5];

	// Do the fitting and save results.
	if (ssfit(fitresults, ofilename.str(), Pstar, Vstar, Tstar, flags) )
	{
		double yVr_initial[2] = { 0.90, 0.65 };

		save_PVTVy( &saveprefix );
		save_TVV( &saveprefix );

		if ( flags & Flags::CURVES )
			curves( &saveprefix, fitresults, ranges, yVr_initial, numpoints );

	}

	if ( ranges != NULL ) delete ranges;
	return true;
}

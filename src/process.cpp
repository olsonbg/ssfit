#include <vector>
#include <sstream>
#include "readranges.h"
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

bool process( const std::string ifile,
              const std::string ifileTempRanges,
              const std::string ifilePressRanges,
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
	std::vector< std::vector< double > > *Tranges = new std::vector< std::vector< double > >;

	if (ifileTempRanges.empty() )
	{
		delete Tranges;
		Tranges = NULL;
	}

	std::stringstream ofilename;
	ofilename << saveprefix << "-summary.dat";

	outlog log(ofilename.str().c_str());

	// Get valid temperature Tranges
	if( ( Tranges != NULL) &&
	    !readTempRanges(ifileTempRanges, Tranges, flags & Flags::KELVIN) )
	{
		std::cout << "Error reading " << ifileTempRanges << "\n";

		if ( Tranges != NULL ) delete Tranges;

		return(false);
	}

	if ( flags & Flags::BLOCKDATA )
	{
		if( !readPVTblock( ifile, &pts, &volumes, &var, Tranges, flags & Flags::KELVIN ) )
		{
			if ( Tranges != NULL ) delete Tranges;
			return(false);
		}
	}
	else
	{
		if( !readPVT( ifile, &pts, &volumes, &var, Tranges,  flags & Flags::KELVIN ) )
		{
			if ( Tranges != NULL ) delete Tranges;
			return(false);
		}
	}

	if ( ( flags & Flags::DATAONLY ) &&
	     ( pts.size() != 0 ) )
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
		if ( Tranges != NULL ) delete Tranges;
		return(true);
	}

	log << "Data points: " << pts.size() << "\n\n";

	minimize.Initialize( pts, volumes, var, 0 );

	// Only fit y. Typically used for temperature below the glass transition,
	// where the SS-EOS equilibrium condition does not hold.
	if ( ( flags & Flags::YONLY ) &&
	     ( pts.size() != 0 ) )
	{
		yfit( ofilename.str(), Pstar, Vstar, Tstar );
		save_PVTy( &saveprefix );

		if ( Tranges != NULL ) delete Tranges;
		return true;
	}


	double fitresults[5];

	// Do the fitting and save results.
	if ( (pts.size() != 0) &&
	     ssfit(fitresults, ofilename.str(), Pstar, Vstar, Tstar, flags) )
	{

		save_PVTVy( &saveprefix );
		save_TVV( &saveprefix );
	}

	// Generate full curves using fit values.
	if ( flags & Flags::CURVES )
	{
		// If no data read, then user just wants to generate a curve, so set
		// fitresults to use the user supplied values.
		if ( pts.size() == 0 )
		{
			fitresults[0] = Pstar;
			fitresults[1] = Vstar;
			fitresults[2] = Tstar;
			fitresults[3] = 2.0;   // Not used.
			fitresults[4] = 2.0;   // Not used.
		}

		double yVr_initial[2] = { 0.90, 0.65 };

		// Range of pressures for each temperature to use for curve generation.
		std::vector< std::vector< double > > *Pranges = new std::vector< std::vector< double > >;

		if (ifilePressRanges.empty() )
		{
			delete Pranges;
			Pranges = NULL;
		}
		// Get valid pressure ranges
		if( ( Pranges != NULL) &&
			!readPressureRanges(ifilePressRanges, Pranges, flags & Flags::KELVIN) )
		{
			std::cout << "Error reading " << ifilePressRanges << "\n";

			if ( Tranges != NULL ) delete Tranges;
			if ( Pranges != NULL ) delete Pranges;

			return false;
		}

		curves( &saveprefix, fitresults,
				Tranges, Pranges,
				yVr_initial, numpoints );

		if ( Pranges != NULL ) delete Pranges;
	}


	if ( Tranges != NULL ) delete Tranges;
	return true;
}

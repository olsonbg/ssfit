#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sortdata.h"
#include "readPVTblock.h"

bool readPVT( const std::string filename,
              std::vector< std::vector< double > > *pts,
              std::vector< double > *volumes,
              std::vector< double > *variances,
              const std::vector< std::vector< double > > *ranges,
              bool isKelvin)
{
	// P, V, T and variances in V.
	std::vector< std::vector< double > > pvtd;

	// Read in the data
	double data_p,
	       data_v,
	       data_t;

	std::ifstream ifp(filename.c_str(),std::ios::in);

	if ( ifp.is_open() )
	{
		std::string line;
		unsigned int lineNumber= 0;
		while( std::getline(ifp, line) )
		{
			lineNumber++;
			if( line[0] != '#' )
			{
				std::istringstream l(line);
				l >> data_p;
				if (!l) {
					std::cerr << "Error: Failed to parse line "
					          << lineNumber
					          << " of datafile, skipping.\n";
					continue;
				}

				l >> data_t;
				if (!l) {
					std::cerr << "Error: Failed to parse line "
					          << lineNumber
					          << " of datafile, skipping.\n";
					continue;
				}

				l >> data_v;
				if (!l) {
					std::cerr << "Error: Failed to parse line "
					          << lineNumber
					          << " of datafile, skipping.\n";
					continue;
				}

				// Temperatures must be in Kelvin
				if ( !isKelvin ) data_t += 273.15;

				if ( isValidTemperature(ranges, data_p, data_t) )
				{
					// use standard deviation of 0.0004 for volumes (volumes are
					// measured to the fourth decimal point); Works well for
					// measurements from Zoller's PVT machine.  Variance equals the
					// standard deviation squared
					std::vector< double >vals = {data_p,
				                                 data_v,
				                                 data_t,
				                                 0.0004*0.0004};
					pvtd.push_back( vals );
				}
			}
		}
		ifp.close();

		// Sort pvtd by P, sub-sorted by T.
		sortdata( pvtd, pts, volumes, variances );

		return true;
	}

	return false;
}



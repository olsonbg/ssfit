#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

bool readPVT( const std::string filename,
              std::vector< std::vector< double > > *pts,
              std::vector< double > *volumes,
              std::vector< double > *variances,
              bool isKelvin)
{
	// Read in the data
	double data_p,
	       data_v,
	       data_t;

	std::ifstream ifp(filename.c_str(),std::ios::in);
	std::string line;
	while( std::getline(ifp, line) )
	{
		if( line[0] != '#' )
		{
			std::istringstream l(line);
			l >> data_p;
			l >> data_t;
			l >> data_v;

			std::vector< double > pt;
			// Convert MPa to Bar (*10.0)
			// pressures.push_back(data_p*10.0);
			pt.push_back(data_p);

			volumes->push_back(data_v);

			// Temperatures must be in Kelvin
			if ( isKelvin )
				pt.push_back(data_t);
			else
				pt.push_back(data_t+273.13);

			pts->push_back(pt);
			// use standard deviation of 0.0004 for volumes (volumes are
			// measured to the fourth decimal point); Works well for measurements
			// from Zoller's PVT machine.  Variance equals the standard deviation
			// squared
			variances->push_back( 0.0004*0.0004);
		}
	}
	ifp.close();

	return(true);
}



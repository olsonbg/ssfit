#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sortdata.h"

bool isValidTemperature( const std::vector< std::vector< double > > *ranges,
                         const double P, const double T)
{
	if ( ranges == NULL )
		return true;

	std::vector<double>::iterator it;
	for( unsigned int i=0; i < ranges->size(); ++i)
	{
		if( ranges->at(i).at(0) == P )
			if ( ( T >= ranges->at(i).at(1) ) &&
			     ( T <= ranges->at(i).at(2) ) )
				return(true);
	}
	return(false);
}

bool readTempRanges( const std::string filename,
                     std::vector< std::vector< double > > *ranges,
                     bool isKelvin)
{
	std::ifstream ifp(filename.c_str(),std::ios::in);
	if ( ifp.is_open() )
	{
		std::string line;
		while( std::getline(ifp, line) )
		{
			if( line[0] != '#' )
			{
				std::istringstream l(line);
				std::vector<double> r;
				double v;
				if ( l >> v ) r.push_back(v);
				if ( l >> v )
				{
					if (isKelvin)
						r.push_back(v);
					else
						r.push_back(v + 273.13);
				}
				if ( l >> v )
				{
					if (isKelvin)
						r.push_back(v);
					else
						r.push_back(v + 273.13);
				}

				if ( r.size() != 3 )
				{
					std::cout << "Expected lines with 3 values in "
					          << filename
					          << ".\n";
					return(false);
				}
				else
					ranges->push_back(r);
			}
		}
		ifp.close();
		return true;
	}

	return false;
}

bool readPVTblock( const std::string filename,
                   std::vector< std::vector< double > > *pts,
                   std::vector< double > *volumes,
                   std::vector< double > *variances,
                   const std::vector< std::vector< double > > *ranges,
                   bool isKelvin )
{
	// Read in the data
	double data_p = 0.0;
	double data_t = 0.0;
	double value;

	std::vector< double > pressure;
	// P, V, T and variances in V.
	std::vector< std::vector< double > > pvtd;

	std::ifstream ifp(filename.c_str(),std::ios::in);
	if ( ifp.is_open() )
	{
		std::string line;
		while( std::getline(ifp, line) )
		{
			if( line[0] != '#' )
			{
				std::istringstream l(line);
				// The first non-commented line is the list of pressures.
				while( l >> data_p )
					pressure.push_back(data_p);

				// The following lines contain a temperature followed by a series
				// of volumes.
				while( std::getline(ifp, line) )
				{
					if( line[0] != '#' )
					{
						unsigned int n=0;
						std::istringstream v(line);
						while( v >> value )
						{
							if ( n == 0 )
							{
								// Temperatures must be in Kelvin
								data_t = isKelvin?value:value + 273.13;
							}
							else
							{
								if ( n > pressure.size() )
								{
									std::cout << "Error reading data file!\n";
									return(false);
								}
								if ( isValidTemperature(ranges, pressure[n-1], data_t) )
								{
									// use standard deviation of 0.0004 for volumes
									// (volumes are measured to the fourth decimal
									// point); Works well for measurements from
									// Zoller's PVT machine.  Variance equals the
									// standard deviation squared
									std::vector< double >vals = {pressure[n-1],
									                             value,
									                             data_t,
									                             0.0004*0.0004};

									pvtd.push_back( vals );
								}
							}
							++n;
						}
					}
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


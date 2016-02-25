#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "readranges.h"

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
				if ( l >> v ) r.push_back( isKelvin?v:v + 273.15);
				if ( l >> v ) r.push_back( isKelvin?v:v + 273.15);

				while ( l >> v ); // Check for any extra values

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

		// Sort ranges by P.
		std::sort( ranges->begin(), ranges->end(),
		           [](const std::vector< double >& a, const std::vector< double >&b)
		             { return a[0] < b[0]; } );

		return true;
	}

	return false;
}

bool readPressureRanges( const std::string filename,
                         std::vector< std::vector< double > > *ranges,
                         bool isKelvin)
{
	std::cout << "-----------------------\n";

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
				if ( l >> v ) r.push_back( isKelvin?v:v + 273.15);
				if ( l >> v ) r.push_back(v);
				if ( l >> v ) r.push_back(v);

				while ( l >> v ); // Check for any extra values

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

		// Sort ranges by P.
		std::sort( ranges->begin(), ranges->end(),
		           [](const std::vector< double >& a, const std::vector< double >&b)
		             { return a[0] < b[0]; } );

		return true;
	}

	return false;
}

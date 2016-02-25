#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "sseos_params.h"
#include "sseos_yv_finder.h"
#include "readPVTblock.h"
#include "curves.h"

bool openfile( std::ofstream& out,
               const std::string *saveprefix,
               const char* suffix )
{
	if( out.is_open() )
		return true;

	std::stringstream ofilename;

	ofilename << *saveprefix << suffix;

	out.open(ofilename.str().c_str(), std::ios::out);

	return out.is_open();
}

bool curves( const std::string *saveprefix,
             const double *params,
             const std::vector< std::vector< double > > *Tranges,
             const std::vector< std::vector< double > > *Pranges,
             const double *yVr_initial,
             const unsigned int N )
{
	std::ofstream out;

	if ( openfile( out, saveprefix, "-curves-TVy.dat" ) )
	{
		if ( !curves_TVy( out, params, Tranges, yVr_initial, N ) )
		{
			out.close();
			return false;
		}
		out.close();
	}

	if ( (Pranges != NULL) &&
	     openfile( out, saveprefix, "-curves-PVy.dat" ) )
	{
		if ( !curves_PVy( out, params, Pranges, yVr_initial, N ) )
		{
			out.close();
			return false;
		}
		out.close();
	}

	return true;
}

bool curves_PVy( std::ofstream& out,
                 const double *params,
                 const std::vector< std::vector< double > > *ranges,
                 const double *yVr_initial,
                 const unsigned int N )
{
	out << "# Pressure / Fit Volumes / Fit y\n#\n";

	struct sseos_params *p = new struct sseos_params;

	p->s  = params[4];
	p->c  = p->s/3.0; // Constraint: s = 3c

	for( unsigned int t=0; t < ranges->size(); ++t )
	{
		double T    = ranges->at(t).at(0);
		double Pmin = ranges->at(t).at(1);
		double Pmax = ranges->at(t).at(2);
		double dP = (Pmax - Pmin)/double(N-1);

		p->Tr = T/params[2];

		// Set initial guesses for y and Vr for this temperature
		p->y  = yVr_initial[0];
		p->Vr = yVr_initial[1];

		std::cout << T - 273.15 << ": " << Pmin << " - " << Pmax << "\n";

		out << "# T = " << T << "\n";

		for(unsigned int n = 0; n != N; ++n)
		{
			double P = Pmin + double(n)*dP;

			p->Pr = P/params[0];

			sseos_yv_finder( p );

			out << P << " "
			    << params[1] * p->Vr << " "
			    << p->y
			    << "\n";
		}
		out << "\n";
	}

	delete p;

	return true;
}

bool curves_TVy( std::ofstream& out,
                 const double *params,
                 const std::vector< std::vector< double > > *ranges,
                 const double *yVr_initial,
                 const unsigned int N )
{
	out << "# Temperature / Fit Volumes / Fit y\n#\n";

	struct sseos_params *p = new struct sseos_params;

	p->s  = params[4];
	p->c  = p->s/3.0; // Constraint: s = 3c

	for(unsigned int i = 0; i != ranges->size(); ++i)
	{
		out << "# P = " << ranges->at(i).at(0) << "\n";
		p->Pr = ranges->at(i).at(0) / params[0];

		// Set initial guesses for y and Vr for this pressure
		p->y  = yVr_initial[0];
		p->Vr = yVr_initial[1];

		const double dt = (ranges->at(i).at(2) - ranges->at(i).at(1))/double(N-1);
		double T;
		for(unsigned int n = 0; n != N; ++n)
		{
			T = ranges->at(i).at(1) + double(n)*dt;
			p->Tr = T/ params[2];

			sseos_yv_finder( p );

			out << T << " "
			    << params[1] * p->Vr << " "
			    << p->y
			    << "\n";
		}
		out << "\n";
	}

	delete p;

	return true;
}

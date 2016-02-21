#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sseos_params.h"
#include "sseos_yv_finder.h"

bool curves( const std::string *saveprefix,
             const double *params,
             const std::vector< std::vector< double > > *ranges,
             const double *yVr_initial,
             const unsigned int N )
{
	std::ofstream out;
	std::stringstream ofilename;

	ofilename << *saveprefix << "-curves-TVy.dat";

	out.open(ofilename.str().c_str(), std::ios::out);

	if (out.is_open() )
	{
		out << "# Temperature / Fit Volumes / Fit y\n#\n";

		struct sseos_params *p = new struct sseos_params;

		p->s  = params[4];
		p->c  = p->s/3.0; // Constraint: s = 3c

		for(unsigned int i = 0; i != ranges->size(); ++i)
		{
			out << "# " << ranges->at(i).at(0) << "\n";
			p->Pr = ranges->at(i).at(0) / params[0];

			// Set initial guesses for y and Vr for this pressure
			p->y  = yVr_initial[0];
			p->Vr = yVr_initial[1];

			const double dt = (ranges->at(i).at(2) - ranges->at(i).at(1) + 1.0)/double(N);
			double T;
			for(unsigned int n = 0; n != N; ++n)
			{
				T = ranges->at(i).at(1) + 273.13 + double(n)*dt;
				p->Tr = T/ params[2];

				sseos_yv_finder( p );

				out << T << " "
				    << params[1] * p->Vr << " "
				    << p->y
				    << "\n";
			}
			out << "\n";
		}
		out.close();
		
		delete p;

		return true;
	}
	out.close();
	return false;
}

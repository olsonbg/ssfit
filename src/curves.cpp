#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sseos_v.h"

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

		// Vr and y.
		double yVr[2];
		for(unsigned int p = 0; p != ranges->size(); ++p)
		{
			out << "# " << ranges->at(p).at(0) << "\n";

			const double dt = (ranges->at(p).at(2) - ranges->at(p).at(1) + 1.0)/double(N);
			double T;
			for(unsigned int n = 0; n != N; ++n)
			{
				// Set yVr to initial guesses.
				yVr[0] = yVr_initial[0];
				yVr[1] = yVr_initial[1];
				T = ranges->at(p).at(1) + 273.13 + double(n)*dt;
				sseos_v( yVr, ranges->at(p).at(0), T, params );
				out << T << " "
				    << params[1] * yVr[1] << " "
				    << yVr[0]
				    << "\n";
			}
			out << "\n";
		}
		out.close();
		return true;
	}
	out.close();
	return false;
}

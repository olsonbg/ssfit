#include "sseos_v.h"
#include "sseos_yv_finder.h"

double *sseos_v( double *yVr,
                 const double P, const double T,
                 const double *params )
{
	const double Pr    = P/params[0];
	const double Tr    = T/params[2];

	/* const double c  = params[3]; */
	const double s  = params[4];
	// Constraint: s = 3c
	const double c  = s/3.0;
	const double A  = 1.011;
	const double B  = 1.2045;

	return( sseos_yv_finder( yVr, c, s, A, B, Pr, Tr ) );
}

#include<math.h>

// Utracki & Simha 2001 equation (3).
double sseos_yv_f0( const double y, const double Vr, const double Tr,
                    const double c, const double s,
                    const int Constraints)
{
	const double A   = 1.011;
	const double B   = 1.2045;

	double Qsq = 1.0/(y*y*Vr*Vr);
	double eta = y*pow(Qsq/2.0,1.0/6.0);

	// Utracki, Simha 2001. Eq (3).
	double Part1a = ( eta - 1.0/3.0 )/( 1.0 - eta );
	double Part1b = y*Qsq*( 3.0*A*Qsq - 2.0*B )/6.0/Tr;

	double Part2;
	double result;

	if ( Constraints )
		Part2  = - 1.0 - log(1.0-y)/y;
	else
		Part2  =  ( (1.0 - s) - s*log(1.0-y)/y )/3.0/c;

	result = Part1a - Part1b + Part2;

	return (result);
}

// Utracki & Simha 2001 equation (2).
double sseos_yv_f1( const double y,
                    const double Pr, const double Vr, const double Tr)
{
	const double A   = 1.011;
	const double B   = 1.2045;

	double Qsq = 1.0/(y*y*Vr*Vr);
	double eta = y*pow(Qsq/2.0,1.0/6.0);

	// Utracki, Simha 2001. Eq (2).
	double Part1a = 1.0/( 1.0 - eta );
	double Part1b = 2.0*y*Qsq*( A*Qsq - B ) / Tr;

	return ( Pr*Vr/Tr - ( Part1a + Part1b ) );
}


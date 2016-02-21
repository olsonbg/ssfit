#include<math.h>
#include"sseos_yv.h"

// Utracki & Simha 2001 equation (3).
double sseos_yv_f0( const struct sseos_params *p,
                    const int Constraints)
{
	double Qsq = 1.0/( p->y * p->y * p->Vr * p->Vr);
	double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	// Utracki, Simha 2001. Eq (3).
	double Part1a = ( eta - 1.0/3.0 )/( 1.0 - eta );
	double Part1b = p->y*Qsq*( 3.0*p->A*Qsq - 2.0*p->B )/6.0/p->Tr;

	double Part2;
	double result;

	if ( Constraints )
		Part2  = - 1.0 - log(1.0-p->y)/p->y;
	else
		Part2  =  ( (1.0 - p->s) - p->s*log(1.0-p->y)/p->y )/3.0/p->c;

	result = Part1a - Part1b + Part2;

	return (result);
}

// Utracki & Simha 2001 equation (2).
double sseos_yv_f1( const struct sseos_params *p )
{
	double Qsq = 1.0/( p->y * p->y * p->Vr * p->Vr);
	double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	// Utracki, Simha 2001. Eq (2).
	double Part1a = 1.0/( 1.0 - eta );
	double Part1b = 2.0*p->y*Qsq*( p->A*Qsq - p->B ) / p->Tr;

	return ( p->Pr*p->Vr/p->Tr - ( Part1a + Part1b ) );
}

double sseos_yv_df0dy ( const struct sseos_params *p )
{
	const double Qsq = 1.0/(p->y * p->y * p->Vr * p->Vr);
	const double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	const double dQ0   = -1.0/(p->y * p->y * p->Vr);
	const double deta0 = 2.0*eta/3.0/p->y;

	return( -1.0*deta0/3.0/(1.0-eta) + (eta-1.0/3.0)/(1.0-eta)/(1.0-eta)*deta0 - Qsq*(3.0*p->A*Qsq - 2.0*p->B)/6.0/p->Tr - 2.0*(3.0*p->A*Qsq - p->B)*dQ0/3.0/p->Vr/p->Tr + ( log(1.0-p->y)/p->y/p->y + 1.0/p->y/(1.0-p->y) )*p->s/3.0/p->c );
}

double sseos_yv_df0dVr ( const struct sseos_params *p )
{
	const double Qsq = 1.0/(p->y * p->y * p->Vr * p->Vr);
	const double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	const double dQ1   = -1.0/(p->y * p->Vr * p->Vr);
	const double deta1 = -1.0*eta/3.0/p->Vr;


	return( -1.0*deta1/3.0/(1.0-eta) + (eta-1.0/3.0)/(1.0-eta)/(1.0-eta)*deta1 - 2.0*(3.0*p->A*Qsq - p->B)*dQ1/3.0/p->Vr/p->Tr );
}

double sseos_yv_df1dy ( const struct sseos_params *p)
{
	const double Qsq = 1.0/(p->y * p->y * p->Vr * p->Vr);
	const double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	const double dQ0   = -1.0/(p->y * p->y * p->Vr);
	const double deta0 = 2.0*eta/3.0/p->y;

	return( -1.0*deta0/(1.0-eta)/(1.0-eta) - 2.0*Qsq*(p->A*Qsq-p->B)/p->Tr - 2.0*(4.0*p->A*Qsq - 2.0*p->B)*dQ0/p->Vr/p->Tr );
}

double sseos_yv_df1dVr( const struct sseos_params *p )
{
	const double Qsq = 1.0/(p->y * p->y * p->Vr * p->Vr);
	const double eta = p->y * pow(Qsq/2.0,1.0/6.0);

	const double dQ1   = -1.0/(p->y * p->Vr * p->Vr);
	const double deta1 = -1.0*eta/3.0/p->Vr;


	return( p->Pr/p->Tr - deta1/(1.0-eta)/(1.0-eta) - 2.0*(4.0*p->A*Qsq - 2.0*p->B)*dQ1/p->Vr/p->Tr );
}

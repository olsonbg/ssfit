#include <math.h>
#include "sseos_params.h"
#include "sseos_approx_v.h"

void sseos_approx_v( struct sseos_params *p )
{
	// const double Pr    = P/params[0];
	// const double Tr    = T/params[2];
	const double Tr32  = pow(p->Tr, 3.0/2.0);

	// Constants for Vr
	const double a[] = { -0.10346 , 23.854 , -0.1320, -333.7, 1032.5, -1329.9 };

	// Constants for h
	const double b[] = { 1.203, -1.929, 10.039, 0.729, -218.42 };

	// Utracki-Simha 2001 equation (10).
	// For P == 0, U-S equation (10) reduces to U-S equation (6).
	double lnVr;
	lnVr = a[0] +
	       a[1]*Tr32 +
	       p->Pr*( a[2] + ( a[3] + a[4]*p->Pr + a[5]*p->Pr*p->Pr)*p->Tr*p->Tr);

	p->Vr = exp( lnVr );

	// Utracki-Simha 2001 equation (11).
	double h = b[0] +
	           b[1]/p->Vr +
	           b[2]*Tr32 +
	           b[3]/p->Vr/p->Vr +
	           b[4]*Tr32*Tr32;

	p->y = 1.0 - h;

}

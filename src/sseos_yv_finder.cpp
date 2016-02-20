#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"sseos_yv.h"
#include"sseos_yv_finder.h"

void handler ( const char * reason,
               const char * file,
               int line,
               int gsl_errno)
{
	printf("GSL error %d: %s [%s, line %d]\n", gsl_errno, reason, file, line);
}

int
sseos_yv_finder_fcn( const gsl_vector* x, void *params, gsl_vector* f)
{
	struct sseos_yv_finder_params *p = (struct sseos_yv_finder_params *) params;

	const double y  = gsl_vector_get(x, 0);
	const double Vr = gsl_vector_get(x, 1);

	gsl_vector_set( f, 0, sseos_yv_f0( y, Vr, p->Tr, p->c, p->s, true ) );
	gsl_vector_set( f, 1, sseos_yv_f1( y, p->Pr, Vr, p->Tr ) );

	return GSL_SUCCESS;
}

int
sseos_yv_finder_df( const gsl_vector* x, void *params, gsl_matrix* J)
{
	struct sseos_yv_finder_params *p = (struct sseos_yv_finder_params *) params;

	double y  = gsl_vector_get(x, 0);
	const double Vr = gsl_vector_get(x, 1);

	const double c   = p->c;
	const double s   = p->s;
	const double A   = p->A;
	const double B   = p->B;
	const double Qsq = 1.0/(y*y*Vr*Vr);
	const double eta = y*pow(Qsq/2.0,1.0/6.0);

	const double dQ0   = -1.0/(y*y*Vr);
	const double dQ1   = -1.0/(y*Vr*Vr);
	const double deta0 = 2.0*eta/3.0/y;
	const double deta1 = -1.0*eta/3.0/Vr;


	const double df00 = -1.0*deta0/3.0/(1.0-eta) + (eta-1.0/3.0)/(1.0-eta)/(1.0-eta)*deta0 - Qsq*(3.0*A*Qsq - 2.0*B)/6.0/p->Tr - 2.0*(3.0*A*Qsq - B)*dQ0/3.0/Vr/p->Tr + ( log(1.0-y)/y/y + 1.0/y/(1.0-y) )*s/3.0/c;


	const double df01 = -1.0*deta1/3.0/(1.0-eta) + (eta-1.0/3.0)/(1.0-eta)/(1.0-eta)*deta1 - 2.0*(3.0*A*Qsq - B)*dQ1/3.0/Vr/p->Tr;

	const double df10 = -1.0*deta0/(1.0-eta)/(1.0-eta) - 2.0*Qsq*(A*Qsq-B)/p->Tr - 2.0*(4.0*A*Qsq - 2.0*B)*dQ0/Vr/p->Tr;

	const double df11 = p->Pr/p->Tr - deta1/(1.0-eta)/(1.0-eta) - 2.0*(4.0*A*Qsq - 2.0*B)*dQ1/Vr/p->Tr;

	gsl_matrix_set( J, 0, 0, isnan(df00)?2.0:df00);
	gsl_matrix_set( J, 0, 1, isnan(df01)?2.0:df01);
	gsl_matrix_set( J, 1, 0, isnan(df10)?2.0:df10);
	gsl_matrix_set( J, 1, 1, isnan(df11)?2.0:df11);

	return GSL_SUCCESS;
}

int
sseos_yv_finder_fdf( const gsl_vector* x, void *params,
                    gsl_vector *f, gsl_matrix* J)
{
	sseos_yv_finder_fcn( x, params, f);
	sseos_yv_finder_df ( x, params, J);

	return GSL_SUCCESS;
}

double*
sseos_yv_finder( double *yVr,
                 const double c, const double s,
                 const double A, const double B,
                 const double Pr,const double Tr)
{
	struct sseos_yv_finder_params params = { c, s, A, B, Pr, Tr };

	const gsl_multiroot_fdfsolver_type *T;
	gsl_multiroot_fdfsolver *solver;

	int status;
	size_t iter = 0;

	const size_t n = 2;
	gsl_multiroot_function_fdf f = {&sseos_yv_finder_fcn,
	                                &sseos_yv_finder_df,
	                                &sseos_yv_finder_fdf,
	                                n, &params};


	gsl_vector *x = gsl_vector_alloc(n);

	// Initial guess
	gsl_vector_set(x, 0, yVr[0]);
	gsl_vector_set(x, 1, yVr[1]);

	T = gsl_multiroot_fdfsolver_gnewton;
	solver = gsl_multiroot_fdfsolver_alloc(T,2);
	status = gsl_multiroot_fdfsolver_set(solver, &f, x);

	if ( status ) /* check if solver is stuck */
	{
		printf("\ninvalid argument, %d.\n",status);
	}

	/* Turn off default gsl error handler */
	gsl_error_handler_t *old_handler = gsl_set_error_handler_off();
	gsl_set_error_handler( handler );

	do
	{
		iter++;
		status = gsl_multiroot_fdfsolver_iterate(solver);

		if ( status ) /* check if solver is stuck */
		{
			printf("\ninvalid argument, %d.\n",status);
			break;
		}

		status = gsl_multiroot_test_residual(solver->f, 1e-7);
	}
	while (status == GSL_CONTINUE && iter < 1000);

	/* restore original handler */
	gsl_set_error_handler(old_handler);

	yVr[0] = gsl_vector_get (solver->x, 0);
	yVr[1] = gsl_vector_get (solver->x, 1);
	gsl_multiroot_fdfsolver_free(solver);
	gsl_vector_free(x);

	if ( status == GSL_EDOM )
	{
		printf("Vr: %f\n", yVr[1]);
	}

	return yVr;
}

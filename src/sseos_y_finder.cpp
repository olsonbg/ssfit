#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"sseos_yv.h"
#include"sseos_y_finder.h"

void yhandler ( const char * reason,
               const char * file,
               int line,
               int gsl_errno)
{
	printf("GSL error %d: %s [%s, line %d]\n", gsl_errno, reason, file, line);
}

int
sseos_y_finder_fcn( const gsl_vector* x, void *params, gsl_vector* f)
{
	struct sseos_params *p = (struct sseos_params *) params;

	p->y  = gsl_vector_get(x, 0);

	gsl_vector_set( f, 0, sseos_yv_f0( p, true ) );

	return GSL_SUCCESS;
}

int
sseos_y_finder_df( const gsl_vector* x, void *params, gsl_matrix* J)
{
	struct sseos_params *p = (struct sseos_params *) params;

	p->y  = gsl_vector_get(x, 0);

	gsl_matrix_set( J, 0, 0, sseos_yv_df1dy ( p ) );

	return GSL_SUCCESS;
}

int
sseos_y_finder_fdf( const gsl_vector* x, void *params,
                    gsl_vector *f, gsl_matrix* J)
{
	sseos_y_finder_fcn( x, params, f);
	sseos_y_finder_df ( x, params, J);

	return GSL_SUCCESS;
}

void
sseos_y_finder( struct sseos_params *params )
{
	const gsl_multiroot_fdfsolver_type *T;
	gsl_multiroot_fdfsolver *solver;

	int status;
	size_t iter = 0;

	const size_t n = 1;
	gsl_multiroot_function_fdf f = {&sseos_y_finder_fcn,
	                                &sseos_y_finder_df,
	                                &sseos_y_finder_fdf,
	                                n, params};


	gsl_vector *x = gsl_vector_alloc(n);

	// Initial guess
	gsl_vector_set(x, 0, params->y);

	T = gsl_multiroot_fdfsolver_gnewton;
	solver = gsl_multiroot_fdfsolver_alloc(T,1);
	status = gsl_multiroot_fdfsolver_set(solver, &f, x);

	if ( status ) /* check if solver is stuck */
	{
		printf("\ninvalid argument, %d.\n",status);
	}

	/* Turn off default gsl error handler */
	gsl_error_handler_t *old_handler = gsl_set_error_handler_off();
	gsl_set_error_handler( yhandler );

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

	// yVr[0] = gsl_vector_get (solver->x, 0);
	// yVr[1] = gsl_vector_get (solver->x, 1);

	params->y  = gsl_vector_get( solver->x, 0);

	gsl_multiroot_fdfsolver_free(solver);
	gsl_vector_free(x);

	if ( status == GSL_EDOM )
	{
		printf("y: %f\n", params->y);
	}
}

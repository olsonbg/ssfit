/**
 * \file
 * \brief Determine y from equation \ref SS1.
 *
 * Use Newtons method for finding root.
 */
#ifndef __SSEOS_Y_FINDER_H
#define __SSEOS_Y_FINDER_H

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

/**
 * Handler for errors from GSL
 */
void yhandler ( const char * reason,
                const char * file,
                int line,
                int gsl_errno);

/**
 * Function used for root finding with GSL library.
 *
 */
int
sseos_y_finder_fcn( const gsl_vector* x, void *params, gsl_vector* f);

/**
 * Function derivatives used for root finding with GSL library.
 */
int
sseos_y_finder_df( const gsl_vector* x, void *params, gsl_matrix* J);

/**
 * Determine y from equation \ref SS1 using Newtons root finding method from
 * the GSL library (Gnu Scientific Library).
 *
 * Initial value for y is taken from \p yVr, and the value found from the root
 * finding is placed in the same variable.
 *
 * \param[in,out] p   SS-EOS parameters
 *
 */
void sseos_y_finder( struct sseos_params *p );

#endif // __SSEOS_Y_FINDER_H

/**
 * \file
 * \brief Determine y and Vr from equations \ref SS1 and \ref SS2.
 *
 * Use Newtons method for finding root of multiple simultaneous equations.
 */
#ifndef __SSEOS_YV_FINDER_H
#define __SSEOS_YV_FINDER_H

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

/**
 * Handler for errors from GSL
 */
void handler ( const char * reason,
               const char * file,
               int line,
               int gsl_errno);

/**
 * Function used for root finding with GSL library.
 *
 */
int
sseos_yv_finder_fcn( const gsl_vector* x, void *params, gsl_vector* f);

/**
 * Function derivatives used for root finding with GSL library.
 */
int
sseos_yv_finder_df( const gsl_vector* x, void *params, gsl_matrix* J);

/**
 * Determine y and Vr from equations \ref SS1 and \ref SS2 using Newtons root
 * finding method from the GSL library (Gnu Scientific Library).
 *
 * Initial values for y and Vr are taken from \p yVr, and the values found from
 * the root finding are placed in the same variable.
 *
 * \param[in,out] p   SS-EOS parameters
 *
 */
void sseos_yv_finder( struct sseos_params *p );

#endif // __SSEOS_YV_FINDER_H

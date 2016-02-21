/**
 * \file
 * \brief SS equations in terms of reduced variables \f$\widetilde{P}\f$, \f$\widetilde{V}\f$, \f$\widetilde{T}\f$:
 *
 * \anchor SS0
 * \f[
 * \widetilde{P} = \frac{P}{P^*}
 * \f]
 *
 * \f[
 * \widetilde{V} = \frac{V}{V^*} \\
 * \f]
 *
 * \f[
 * \widetilde{T} = \frac{T}{T^*}
 * \f]
 *
 * Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24
 * Equation (2):
 *
 * \anchor SS1
 * \f[
 *   \frac{\widetilde{P}\widetilde{V}}{\widetilde{T}} - \frac{1}{1 - \eta} - \frac{2yQ^2}{\widetilde{T}}\left(AQ^2 - B\right) = 0
 * \f]
 *
 * Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24
 * Equation (3):
 *
 * \anchor SS2
 * \f[
 *  3c\left[\frac{\eta - \frac{1}{3}}{1 - \eta} - \frac{yQ^2}{6\widetilde{T}}\left(3AQ^2 -2B\right)\right] + \left(2-s\right) - \frac{s}{y}\ln\left(1-y\right) = 0
 * \f]
 *
 * Where,
 * \f[
 *     Q = \frac{1}{y\widetilde{V}}
 * \f]
 *
 * \f[
 *    \eta = 2^{-1/6}yQ^{1/3}
 * \f]
 * \f[ A = 1.011 \f]
 * \f[ B = 1.2045 \f]
 *
 */
#ifndef _SSEOS_YV_H
#define _SSEOS_YV_H

#include "sseos_params.h"

/**
 * Calculate the value of the left side of equation \ref SS2. If \p Constraints
 * is \p TRUE, then use the following constraints:
 *
 * \f[
 * \frac{s}{3c}\simeq1
 * \f]
 * \f[
 * s\gg1
 * \f]
 *
 * Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24
 * Equation (3).
 *
 * \param[in] p            SS-EOS parameters
 * \param[in] Constraints  Use constraints on c and s.
 *
 * \return Value of left side of equation \ref SS2
 */
double sseos_yv_f0( const struct sseos_params *p,
                    const int Constraints);

/**
 * Calculate the value of the left side of equation \ref SS1.
 *
 * Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24
 * Equation (2).
 *
 * \param[in] p    SS-EOS parameters
 *
 * \return Value of left side of equation \ref SS1
 */
double sseos_yv_f1( const struct sseos_params *p );

/**
 * Derivative of \ref SS2 with respect to y.
 *
 * \param[in] p    SS-EOS parameters
 *
 * \return Value derivative
 */
double sseos_yv_df0dy ( const struct sseos_params *p );

/**
 * Derivative of \ref SS2 with respect to reduced specific volume.
 *
 * \param[in] p    SS-EOS parameters
 *
 * \return Value derivative
 */
double sseos_yv_df0dVr( const struct sseos_params *p );

/**
 * Derivative of \ref SS1 with respect to y.
 *
 * \param[in] p    SS-EOS parameters
 *
 * \return Value derivative
 */
double sseos_yv_df1dy ( const struct sseos_params *p );

/**
 * Derivative of \ref SS1 with respect to reduced specific volume.
 *
 * \param[in] p    SS-EOS parameters
 *
 * \return Value derivative
 */
double sseos_yv_df1dVr( const struct sseos_params *p );

#endif // _SSEOS_YV_H

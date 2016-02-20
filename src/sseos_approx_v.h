/**
 * \file
 * \brief Fit approximate equation for SS equation of state
 *
 * Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24
 * Equation (10):
 *
 * \anchor SS3
 * \f[
 * \ln \widetilde{V} = a_0 + a_1\widetilde{T}^{3/2} + \widetilde{P}\left[ a_2 + \left( a_3 + a_4\widetilde{P} + a_5\widetilde{P}^2\right)\widetilde{T}^2\right]
 * \f]
 *
 * where there reduced variables are defined in equations \ref SS0, and the
 * constants are
 *
 *  | Variable  | Value   |
 *  | --------- | -----:  |
 *  | \f$a_0\f$ |-0.10346 |
 *  | \f$a_1\f$ |  23.854 |
 *  | \f$a_2\f$ | -0.1320 |
 *  | \f$a_3\f$ |  -333.7 |
 *  | \f$a_4\f$ |  1032.5 |
 *  | \f$a_5\f$ | -1329.9 |
 */
#ifndef _SSEOS_APPROX_V_H
#define _SSEOS_APPROX_V_H

/**
 * Approximate equation for SS equation of state
 *
 * Initial values for y and Vr are taken from yVr, and the best fit values are
 * placed in the same variable.
 *
 * \param[in,out] yVr    y and Vr.
 * \param[in] P          Pressure
 * \param[in] T          Temperature
 * \param[in] params     Fitting parameters (Pstar, Vstar, Tstar, c, and s)
 *
 * \return \p yVr
 */
double *sseos_approx_v( double *yVr,
                        const double P, const double T,
                        const double *params );

#endif // __SSEOS_APPROX_V_H

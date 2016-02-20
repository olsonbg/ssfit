/**
 * \file
 * \brief Fit to exact equation of SS equation of state
 */
#ifndef _SSEOS_V_H
#define _SSEOS_V_H

/**
 * Fit to exact equation for SS equation of state
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
double *sseos_v( double *yVr,
                 const double P, const double T,
                 const double *params );

#endif // __SSEOS_V_H

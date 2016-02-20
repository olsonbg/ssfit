/**
 * \file
 * \brief Find Pstar, Vstar, and Tstar with chi squared minimization
 *
 * Use Minuit2 (CERN package) to minimize chi squared
 */
#ifndef _SSFIT_H
#define _SSFIT_H
#include<string>

/**
 * Calculates y and Vr from either equations \ref SS1 and \ref SS2, or equation
 * \ref SS3, depending on the value of \p APPROXIMATE.
 *
 * Fit values are stored in \ref FitStatistics class
 *
 * \param[in] params  Fitting parameters
 * \param[in] APPROXIMATE Boolean indicating where the exact or approximate equations are used
 */
void SSFitData( const double *params, bool APPROXIMATE );
/**
 * Wrapper to get chi squared using equations \ref SS1 and \ref SS2.
 *
 * \param[in] params  Fitting parameters
 *
 * \return chi squared
 */
double chi2_wrapper( const double *params );
/**
 * Wrapper to get chi squared using approximate equation \ref SS3.
 *
 * \param[in] params  Fitting parameters
 *
 * \return chi squared
 */
double chi2_approx_wrapper( const double *params );

/**
 * Determine fitting parameters using Minuit2 library from CERN.
 *
 * \param[out] results    Fit values
 * \param[in]  ofilename  File name prefix used for saving data
 * \param[in]  Pstar
 * \param[in]  Vstar
 * \param[in]  Tstar
 * \param[in]  flags      Flags as specified on the command line
 * 
 * \return \p TRUE on success, \p FALSE otherwise.
 */
bool ssfit( double *results, const std::string ofilename,
            const double Pstar, const double Vstar, const double Tstar,
            const unsigned int flags );

#endif // _SSFIT_H

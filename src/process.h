/**
 * \file
 * \brief Main caller for program.
 *
 * Calls the fitting, saving, and curves routines.
 */
#ifndef _SSFIT_H
#define _SSFIT_H
#include "fitstatistics.h"

FitStatistics minimize;

/**
 * Main caller for program. Calls the fitting routine, and save data.
 *
 * \param[in] ifile       Input file containing PVT data
 * \param[in] saveprefix  Prefix used for saving outfile files
 * \param[in] Pstar       Initial guess for Pstar
 * \param[in] Vstar       Initial guess for Vstar
 * \param[in] Tstar       Initial guess for Tstar
 *
 * \return \p TRUE if no errors, \p FALSE otherwise.
 */
bool process( const std::string ifile, const std::string ifileRanges,
              const std::string saveprefix,
              const double Pstar, const double Vstar, const double Tstar,
              const unsigned int numpoints,
              const unsigned int flags );

#endif //_SSFIT_H

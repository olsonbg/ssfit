/**
 * \file
 * \brief Generate curves for specific volume (V) and occupied fraction (y).
 */
#ifndef _CURVES_H
#define _CURVES_H

/**
 * Generate curves containing \p numpoints data points for all pressures and temperatures specified in \p ranges.
 *
 * \param[in] saveprefix  Filename prefix used for saving data
 * \param[in] params      Fitting parameters (Pstar, Vstar, Tstar, c, and s)
 * \param[in] ranges      Temperature ranges, for each pressure
 * \param[in] yVr_initial Initial guess for y and Vr (reduced specific volumes)
 * \param[in] numpoints   Number of points to generate for each curve
 *
 * return \p TRUE on success, \p FALSE otherwise
 */
bool curves( const std::string *saveprefix,
             const double *params,
             const std::vector< std::vector< double > > *ranges,
             const double *yVr_initial,
             const unsigned int numpoints);

#endif // _CURVES_H

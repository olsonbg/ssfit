/**
 * \file
 * \brief Read PVT data
 */
#ifndef _READPVT_H
#define _READPVT_H

/**
 * Read PVT data that is in three columns format.
 *
 * - Columns
 *   -# Measured pressure
 *   -# Measured temperature
 *   -# Measured specific volume
 *
 * \param[in] filename Name of the data file
 * \param[out] pts       Contains pressure and temperature values from the data file
 * \param[out] volumes   Specific volumes from the data file
 * \param[out] variances Variances of the specific volumes
 * \param[in]  isKelvin  Boolean specifying that the data temperatures are in Kelvin
 *
 * \return \p TRUE on success, \p FALSE otherwise.
 */
bool readPVT( const std::string filename,
              std::vector< std::vector< double > > *pts,
              std::vector< double > *volumes,
              std::vector< double > *variances,
              bool isKelvin);
#endif // _READPVT_H

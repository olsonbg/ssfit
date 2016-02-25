/**
 * \file
 * \brief Read Ranges file for valid temperatures and pressures
 */
#ifndef _READRANGES_H
#define _READRANGES_H
/**
 * Read temperature ranges
 *
 * Data is in three column format, with each column separated by whitespace.
 * - Columns
 *   -# Pressure
 *   -# Minimum temperature
 *   -# Maximum temperature
 *
 * \param[in]  filename  Name of the ranges data file
 * \param[in]  ranges    Temperature ranges, for each pressure, to import data
 * \param[in]  isKelvin  Boolean specifying that the data temperatures are in Kelvin
 *
 * \return \p TRUE on success, \p FALSE otherwise.
 */
bool readTempRanges( const std::string filename,
                     std::vector< std::vector< double > > *ranges,
                     bool isKelvin );
#endif // _READRANGES_H


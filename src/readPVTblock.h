/**
 * \file
 * \brief Read PVT data, and ranges file
 */
#ifndef _READPVTBLOCK_H
#define _READPVTBLOCK_H

/**
 * Read PVT data that is in block format, with columns separated by whitespace.
 *
 *  | Column 1 | Column 2 | Column 3 | .... | Column n |
 *  |   ----   |   ---    |   ----   | ---- |   ----   |
 *  |          |    P1    |    P2    |  ... |    Pn    |
 *  |    T1    |    V11   |    V12   |  ... |    V1n   |
 *  |    T2    |    V21   |    V22   |  ... |    V2n   |
 *  |    ...   |    ...   |    ...   | ...  |    V2n   |
 *  |    Tm    |    Vm1   |    Vm2   | ...  |    Vmn   |
 *
 * \param[in]  filename  Name of the data file
 * \param[out] pts       Contains pressure and temperature values from the data file
 * \param[out] volumes   Specific volumes from the data file
 * \param[out] variances Variances of the specific volumes
 * \param[in]  ranges    Temperature ranges, for each pressure, to import data
 * \param[in]  isKelvin  Boolean specifying that the data temperatures are in Kelvin
 *
 * \return \p TRUE on success, \p FALSE otherwise.
 */
bool readPVTblock( const std::string filename,
                   std::vector< std::vector< double > > *pts,
                   std::vector< double > *volumes,
                   std::vector< double > *variances,
                   const std::vector< std::vector< double > > *ranges,
                   bool isKelvin );

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

/**
 * Check if a data point is valid, as specified by \p ranges
 *
 * \param[in]  ranges    Temperature ranges, for each pressure, to import data
 * \param[in]  P         Pressure of this data point
 * \param[in]  T         Temperature of this data point
 *
 * \return \p TRUE if valid, \p FALSE otherwise
 */
bool isValidTemperature( const std::vector< std::vector< double > > *ranges,
                         const double P, const double T);
#endif // _READPVTBLOCK_H

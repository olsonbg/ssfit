/**
 * \file
 * \brief Sort data by P, sub-sorted by T.
 */
#ifndef _SORTDATA_H
#define _SORTDATA_H

/**
 * Sort data by P, sub-sorted by T.
 *
 * \param[in]  pvtd      Contains pressure, volume, temperature and variances values from the data file
 * \param[out] pts       Contains pressure and temperature values from the data file
 * \param[out] volumes   Specific volumes from the data file
 * \param[out] variances Variances of the specific volumes
 */
void sortdata( std::vector< std::vector< double > > pvtd,
               std::vector< std::vector< double > > *pts,
               std::vector< double > *volumes,
               std::vector< double > *variances);
#endif // _SORTDATA_H

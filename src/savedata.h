/**
 * \file
 * \brief Saves TVV, and PVTVy data
 */
#ifndef _SAVEDATA_H
#define _SAVEDATA_H

/**
 * Save three column data file, with '-TVV.dat' suffix.
 *
 *  - Columns
 *   -# Measured temperature
 *   -# Measured specific volume
 *   -# Fit specific volume
 *
 * The saved data is grouped by pressure, with each group separated by a blank
 * line. The Pressure is indicated for each group on a line beginning with the
 * '#' character (a comment).
 *
 * \param[in] saveprefix File name prefix to save data
 *
 * \return \p TRUE on success, \p FALSE otherwise
 */
bool save_TVV(const std::string *saveprefix);

/**
 * Save five column data file, with '-PVTVy.dat' suffix.
 *
 *  - Columns
 *   -# Measured pressure
 *   -# Measured specific volume
 *   -# Measured temperature
 *   -# Fit specific volume
 *   -# Fit occupied volume fraction
 *
 * \param[in] saveprefix  File name prefix to save data
 *
 * \return \p TRUE on success, \p FALSE otherwise
 */
bool save_PVTVy(const std::string *saveprefix);

/**
 * Save four column data file, with '-PVTy.dat' suffix. Used with \p YONLY
 * flag.
 *
 *  - Columns
 *   -# Measured pressure
 *   -# Measured specific volume
 *   -# Measured temperature
 *   -# Fit occupied volume fraction
 *
 * \param[in] saveprefix  File name prefix to save data
 *
 * \return \p TRUE on success, \p FALSE otherwise
 */
bool save_PVTy(const std::string *saveprefix);
#endif // _SAVEDATA_H

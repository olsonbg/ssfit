/**
 * \file
 * \brief   Flags for command line
 * \author  Brian G. Olson (olsonbg@gmail.com)
 * \date    14 Feburary 2015
 */
#ifndef _flags_h
#define _flags_h

/**
 * Flags for command line options
 */
enum class Flags : unsigned int {
	ZERO          = 0,
	ONE           = 1 << 0,
	VERBOSE       = 1 << 1, /**< Be verbose                                */
	BLOCKDATA     = 1 << 2, /**< Datafile is in block format               */
	FIXED_P       = 1 << 3, /**< Fix Pressure during fitting               */
	FIXED_V       = 1 << 4, /**< Fix Volume during fitting                 */
	FIXED_T       = 1 << 5, /**< Fix Temperature during fitting            */
	DATAONLY      = 1 << 6, /**< Dump data in two columns, T and V         */
	SCAN          = 1 << 7, /**< Scan P,V, and T around their current vals */
	CURVES        = 1 << 8, /**< Generate curves of P, V, T, and y         */
	APPROXIMATE   = 1 << 9, /**< Generate curves of P, V, T, and y         */
	KELVIN        = 1 <<10, /**< Data temperatures are in Kelvin           */
	YONLY         = 1 <<11, /**< Fit y values only, all others fixed       */
	COUNT         = 13      /**< Number of flags in enum                   */
};

unsigned int operator& (unsigned int l, Flags r);
unsigned int operator| (unsigned int l, Flags r);

Flags operator& (Flags l, Flags r);
Flags operator| (Flags l, Flags r);
#endif // _flags_h

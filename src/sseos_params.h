/**
 * \file
 * \brief Structure holding SS-EOS parameters
 */
#ifndef _SSOES_PARAMS_H
#define _SSOES_PARAMS_H
/**
 * \brief Store SS-EOS parameters
 */
struct sseos_params
{
	double c;  /**< Related to number of external degrees of freedom per chain*/
	double s;                 /**< number of segments per chain */
	double Pr;                /**< Reduced pressude    */
	double Vr;                /**< Reduced specific volume */
	double Tr;                /**< Reduced temperature */
	double y;                 /**< Occupied fraction of lattice sites */
	const double A = 1.011;   /**< Constant            */
	const double B = 1.2045;  /**< Constant            */
};

#endif // _SSOES_PARAMS_H

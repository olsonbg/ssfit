#include <cassert>
#include <iostream>
#include <math.h>
#include "fitstatistics.h"
#include "sseos_v.h"


void FitStatistics::SetFitValues( const double *fitvals, const double *yfitvals ) {
	double sum = 0.0;
	for(unsigned int n = 0; n < Fit.size(); n++)
	{
		Fit[n] = fitvals[n];
		yFit[n] = yfitvals[n];

		sum += Fit[n];
	}

	StatisticsCalculated = false;
}

double FitStatistics::GetSSE( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return SSE;
}

double FitStatistics::GetSSR( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return SSR;
}

double FitStatistics::GetSST( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return SST;
}

double FitStatistics::GetRMSE( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return RMSE;
}

double FitStatistics::GetAdjRsquared( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return AdjRsquared;
}

double FitStatistics::GetRsquared( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return Rsquared;
}

double FitStatistics::GetRsquaredMicromath( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return RsquaredMicromath;
}

double FitStatistics::GetCVRMSE( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return CVRMSE;
}

void FitStatistics::CalcStatistics( void ) {
	// The sum of squares of residuals, also called the residual sum of
	// squares: Sum of Squares Due to Error.  Summed square of residuals
	SSE = 0.0;

	// The regression sum of squares, also called the explained sum of squares.
	SSR = 0.0;

	Chi2 = 0.0;
	double mf;// Temporary variable used to store a calculation.
	for(unsigned int n = 0; n < Inputs.size(); n++)
	{
		mf = (Measured[n] - Fit[n])*(Measured[n] - Fit[n]);

		SSE += mf;
		Chi2 += mf/MeasuredVariances[n];

		SSR += (Fit[n] - MeasuredAverage)*(Fit[n] - MeasuredAverage);
	}

	Chi2perDOF = Chi2/double(DOF);

	// Root-Mean-Square Error (RMSE) also known as: the root-mean-square
	// deviation (RMSD), the fit standard error, and the standard error of the
	// regression. It is an estimate of the standard deviation of the random
	// component in the data
	RMSE = sqrt( SSE/GetDOF() );

	// Coefficient of variation of the RMSE.
	CVRMSE = RMSE/MeasuredAverage;

	Rsquared = 1.0 - SSE/SST;

	AdjRsquared = 1.0 - ( 1.0 - Rsquared )*(Inputs.size()-1)/GetDOF() ;

	RsquaredMicromath = fabs( SSM - SSE )/SSM;

	StatisticsCalculated = true;
}

double FitStatistics::GetChiSquared( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return( Chi2 );
}

double FitStatistics::GetChiSquaredDOF( void ) {
	if ( !StatisticsCalculated )
		CalcStatistics();

	return( Chi2perDOF );
}

unsigned int FitStatistics::GetDOF( void ) {
	return (DOF);
}


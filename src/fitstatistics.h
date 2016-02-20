/**
 * \file
 * \brief Statistics on measured and fit data
 */
#ifndef _CHISQUARED_H
#define _CHISQUARED_H

#include <vector>
#include <numeric>
#include <Minuit2/ParametricFunction.h>

/**
 * \brief Statistics on measured and fit data
 */
class FitStatistics {
	public:
		/**
		 * Constructor
		 */
		FitStatistics(void) :
			DOF( 0 ), MeasuredSum( 0.0 ), MeasuredAverage( 0.0 ),
			SSE( 0.0), SSR( 0.0 ), SST( 0.0 ), RMSE( 0.0 ), CVRMSE( 0.0 ),
			Rsquared( 0.0 ), AdjRsquared( 0.0 ),
			RsquaredMicromath( 0.0 ), SSM( 0.0 ),
			Chi2( 0.0 ), Chi2perDOF( 0.0 ),
			StatisticsCalculated( false ) {}

		/**
		 * Constructor
		 *
		 * \param[in] inputs           Input variables
		 * \param[in] measured         Measured values
		 * \param[in] variances        Variances of measured values
		 * \param[in] nfreeparamaters  Number of free parameters used in fitting
		 */
		FitStatistics( std::vector< std::vector< double > >inputs,
		                  std::vector< double > measured,
		                  std::vector< double > variances,
		                  int nfreeparameters )
		{
			FitStatistics();
			Initialize( inputs, measured, variances, nfreeparameters );
		}

		/**
		 * Initialize parameters
		 *
		 * \param[in] inputs           Input variables
		 * \param[in] measured         Measured values
		 * \param[in] variances        Variances of measured values
		 */
		void Initialize( std::vector< std::vector< double > >inputs,
		                 std::vector< double > measured,
		                 std::vector< double > variances,
		                 int numfreeparameters )
		{
			FitStatistics();
			Inputs             = inputs;
			Measured           = measured;
			MeasuredVariances  = variances;
			NumFreeParameters  = numfreeparameters;
			MeasuredSum        = std::accumulate( Measured.begin(),
			                                      Measured.end(),
			                                      0.0 );
			MeasuredAverage    = MeasuredSum/Measured.size();
			DOF                = Measured.size() - NumFreeParameters - 1;
			// Assign Fit as measured values to start.
			Fit                = measured;
			yFit.assign( Fit.size(), 0.0 );
			StatisticsCalculated = false;

			// sum of squares about the mean.  Total sum of squares
			// (proportional to the variance of the data)
			SST = 0.0;

			SSM = 0.0;

			for(unsigned int n = 0; n < Inputs.size(); n++)
			{
				SST += (Measured[n] - MeasuredAverage)*(Measured[n] - MeasuredAverage);
				SSM += Measured[n] * Measured[n];
			}
		}
		/**
		 * Calculate Statistics
		 */
		void CalcStatistics( void );
		/**
		 * Get SSE
		 * \return \ref SSE
		 */
		double GetSSE( void );
		/**
		 * Get SSR
		 * \return \ref SSR
		 */
		double GetSSR( void );
		/**
		 * Get SST
		 * \return \ref SST
		 */
		double GetSST( void );
		/**
		 * Get RMSE
		 * \return \ref RMSE
		 */
		double GetRMSE( void );
		/**
		 * Get CVRMSE
		 * \return \ref CVRMSE
		 */
		double GetCVRMSE( void );
		/**
		 * Get Adjusted R squared
		 * \return \ref AdjRsquared
		 */
		double GetAdjRsquared( void );
		/**
		 * Get R squared
		 * \return \ref Rsquared
		 */
		double GetRsquared( void );
		/**
		 * Get R squared as calculated by Micromath
		 * \return \ref RsquaredMicromath
		 */
		double GetRsquaredMicromath( void );
		/**
		 * Get Chi squared
		 *
		 * \return \ref Chi2
		 */
		double GetChiSquared( void );
		/**
		 * Get Reduced Chi squared
		 *
		 * \return \ref Chi2perDOF
		 */
		double GetChiSquaredDOF( void );
		/**
		 * Set number of free parameters used for fitting
		 *
		 * \param[in] n  Number of free fitting parameters
		 */
		void SetNumFreeParameters( const unsigned int n ) {
			NumFreeParameters = n;
			DOF = Measured.size() - NumFreeParameters - 1;
		}
		/**
		 * Set the fit values
		 *
		 * \param[in] vals  Fit values for specific volume (V)
		 * \param[in] yvals Fit values for y
		 */
		void SetFitValues( const double *vals, const double *yvals );
		/**
		 * Get the fit values
		 *
		 * \param[out] fitvals  Fit values for specific volume (V)
		 * \param[out] yfitvals Fit values for y
		 */
		void GetFitValues( std::vector< double > *fitvals,
		                   std::vector< double > *yfitvals ) {
			for(unsigned int n = 0; n < Fit.size(); n++)
			{
				fitvals->push_back(Fit[n]);
				yfitvals->push_back(yFit[n]);
			}
		}

		/**
		 * Get the measured values
		 *
		 * \return Reference to \ref Measured
		 */
		const std::vector< double >& GetMeasuredValues() const {
			return Measured;
		}

		/**
		 * Get input variables
		 *
		 * \return Reference to \ref Inputs
		 */
		const std::vector< std::vector< double > >& GetInputValues() const {
			return Inputs;
		}

		/**
		 * Set degrees of freedom
		 *
		 * \param[in] dof Degrees of freedom
		 */
		void SetDOF( int dof ) { DOF =  dof; }
		/**
		 * Get degrees of freedom
		 *
		 * \return \ref DOF
		 */
		unsigned int  GetDOF( void );
	protected:
		std::vector< std::vector< double > > Inputs; /**< Input values */
		std::vector< double > Fit;                   /**< V fit values */
		std::vector< double > yFit;                  /**< y fit values */
		double FitAverage;
	private:
		std::vector< double > Measured;           /**< Measured values */
		std::vector< double > MeasuredVariances;  /**< Variance of measured values */
		int DOF; /**< Degrees of freedom */
		double MeasuredSum;
		double MeasuredAverage; /**< Average of measured values */
		int NumFreeParameters;
		/**
		 * The sum of squares of residuals, also called the residual sum of
		 * squares: Sum of Squares Due to Error.  Summed square of residuals
		 *
		 * sum of:
		 * (\ref Measured - \ref Fit)*(\ref Measured - \ref Fit)
		 */
		double SSE;
		/**
		 * The regression sum of squares, also called the explained sum of
		 * squares.
		 *
		 * sum of:
		 * (\ref Fit - \ref MeasuredAverage)*(\ref Fit - \ref MeasuredAverage)
		 */
		double SSR;
		/**
		 * sum of squares about the mean.  Total sum of squares
		 * (proportional to the variance of the data)
		 *
		 * sum of:
		 * (\ref Measured - \ref MeasuredAverage)*(\ref Measured - \ref MeasuredAverage)
		 */
		double SST;
		/** 
		 * Root-Mean-Square Error (RMSE) also known as: the root-mean-square
		 * deviation (RMSD), the fit standard error, and the standard error of
		 * the regression.
		 * This is an estimate of the standard deviation of the random
		 * component in the data
		 *
		 * sqrt( \ref SSE/\ref DOF )
		 */
		double RMSE;
		/**
		 * Coefficient of variation of the RMSE.
		 *
		 * \ref RMSE/\ref MeasuredAverage
		 */
		double CVRMSE;
		/**
		 * R squared, also know as the Coefficient of Determination.
		 *
		 * 1 - \ref SSE/\ref SST
		 */
		double Rsquared;
		/**
		 * 1 - (1 - \ref Rsquared)*(n-1)/\ref DOF
		 *
		 * where n is size of \ref Inputs
		 */
		double AdjRsquared;
		/**
		 * R squared as calculated from Micromath software
		 *
		 * |\ref SSM - \ref SSE|/\ref SSM
		 */
		double RsquaredMicromath;
		/**
		 * Sum of squared measurements
		 *
		 * Sum of: \ref Measured*\ref Measured
		 */
		double SSM;
		/**
		 * Chi squared
		 *
		 * sum of:
		 * (\ref Measured - \ref Fit)*(\ref Measured - \ref Fit)/\ref MeasuredVariances
		 */
		double Chi2;
		/**
		 * Chi squared per degree of freedom (reduced chi squared)
		 *
		 * \ref Chi2/\ref DOF
		 */
		double Chi2perDOF;
		bool StatisticsCalculated;
};
#endif // _CHISQUARED_H_


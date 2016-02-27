#include <Minuit2/Minuit2Minimizer.h>
#include <Minuit2/MnPlot.h>
#include <Math/Functor.h>
#include <sstream>
#include "sseos_params.h"
#include "sseos_yv_finder.h"
#include "sseos_approx_v.h"
#include "fitstatistics.h"
#include "OutputFormat.h"
#include "flags.h"
#include "outlog.h"

extern FitStatistics minimize;

void SSFitData( const double *params, bool APPROXIMATE ) {
	// Initial Guess for Vr and y.
	double yVr_initial[2] = { 0.90, 0.65 };

	struct sseos_params *p = new struct sseos_params;

	p->y  = yVr_initial[0];
	p->Vr = yVr_initial[1];
	p->s  = params[4];
	p->c  = p->s/3.0; // Constraint: s = 3c

	const std::vector< std::vector< double > >& Inputs = minimize.GetInputValues();

	double  Fit[ Inputs.size() ];
	double yFit[ Inputs.size() ];

	double Pprev = Inputs[0][0] / params[0];

	for(unsigned int n = 0; n < Inputs.size(); n++) {
		p->Pr = Inputs[n][0] / params[0];
		p->Tr = Inputs[n][1] / params[2];
		if ( p->Pr != Pprev )
		{
			// Reset initial guesses for y and Vr for a new pressure sequence.
			p->y  = yVr_initial[0];
			p->Vr = yVr_initial[1];
		}
		if ( APPROXIMATE )
			sseos_approx_v( p );
		else
			sseos_yv_finder( p );

		yFit[n] = p->y;
		Fit[n] = params[1] * p->Vr;

		Pprev = p->Pr;

	}

	delete p;

	minimize.SetFitValues( Fit, yFit );
}

double chi2_wrapper( const double *params )
{
	SSFitData( params, false );

	return( minimize.GetChiSquared() );
}

double chi2_approx_wrapper( const double *params )
{
	SSFitData( params, true );

	return( minimize.GetChiSquared() );
}


bool ssfit( double *results, const std::string ofilename,
            const double Pstar, const double Vstar, const double Tstar,
            const unsigned int flags )
{

	ROOT::Minuit2::Minuit2Minimizer min( ROOT::Minuit2::kMigrad );

	min.SetStrategy(2);
	min.SetMaxFunctionCalls(100000);
	min.SetMaxIterations(100000);
	min.SetTolerance(1.0e-10);
	min.SetErrorDef(1.0);
	min.SetPrintLevel(0);


	ROOT::Math::Functor f;


	outlog log(ofilename.c_str());

	if ( flags & Flags::APPROXIMATE )
	{
		log << "Using approximate fitting.\n";
		log << "  * Utracki & Simha 2001 equation (10) for V.\n";
		log << "  * Utracki & Simha 2001 equation (11) for y.\n\n";
		ROOT::Math::Functor fapprox( &chi2_approx_wrapper, 5 );

		f = fapprox;
	}
	else
	{
		log << "Using full SS-EOS theory.\n";
		log << "  * Utracki & Simha 2001 equations (2) - (3).\n\n";
		ROOT::Math::Functor ffull( &chi2_wrapper, 5 );

		f = ffull;
	}

	min.SetFunction(f);

	log << "-- Initial Parameters --\n\n";
	log << "Pstar: " << Pstar << "\n";
	log << "Vstar: " << Vstar << "\n";
	log << "Tstar: " << Tstar << "\n\n";

	// Free parameters.
	if ( flags & Flags::FIXED_P )
		min.SetFixedVariable(0, "Pstar", Pstar);
	else
		min.SetVariable     (0, "Pstar", Pstar, 10.0 );

	if ( flags & Flags::FIXED_V )
		min.SetFixedVariable(1, "Vstar", Vstar );
	else
		min.SetVariable     (1, "Vstar", Vstar,  0.0004 );

	if ( flags & Flags::FIXED_T )
		min.SetFixedVariable(2, "Tstar", Tstar );
	else
		min.SetVariable     (2, "Tstar", Tstar, 10.0 );

	// c and s are not used for fitting (3c/s=1, and s>>1). I leave these here
	// for possible use in the future.
	min.SetFixedVariable(3, "c"    , 2.0);
	min.SetFixedVariable(4, "s"    , 2.0);

	minimize.SetNumFreeParameters( min.NFree() );

	// Do a calculation with the initial parameters.
	SSFitData( min.X(), flags&Flags::APPROXIMATE );

	if ( min.NFree() != 0 )
	{
		min.Minimize();
		min.Hesse(); // Run Hesse to get good error estimates
	}


	if ( flags & Flags::SCAN )
	{
		ROOT::Minuit2::MnPlot plot;
		unsigned int npoints=20;
		std::vector<double> x(npoints);
		std::vector<double> y(npoints);

		for(unsigned int p=0; p < 3; ++p )
		{
			min.Scan(p, npoints, &x[0], &y[0] );
			std::pair<double,double> xypair;
			std::vector< std::pair<double,double> > xy;
			for(unsigned int i=0; i < npoints; ++i)
			{
				xypair.first  = x[i];
				xypair.second = y[i];
				xy.push_back(xypair);
			}
			std::cout << min.VariableName(p) << ":\n";
			plot(xy);
		}

		// Do another Minimize in case the Scans found a new minimum (they will
		// be used as starting points for the minimization).
		if ( min.NFree() != 0 )
		{
			min.Minimize();
			min.Hesse();     // Update the errors
		}
	}


	log << "Minimizer - ";
	switch( min.Status() )
	{
		case 0:
			log << "Valid Minimum";
			break;
		case 1:
			log << "Valid Minimum (Covariance was made pos defined)";
			break;
		case 2:
			log << "Valid Minimum (Hesse is invalid)";
			break;
		case 3:
			log << "Valid Minimum (Edm is above max)";
			break;
		case 4:
			log << "Invalid Minimum (Reached call limit)";
			break;
		default:
			log << "Invalid Minimum";
			break;
	}
	log << " - status = " << min.Status() << "\n\n";

	log << "-- Fit Parameters --\n";

	const double *xs = min.X();
	const double *xe = min.Errors();
	results[0] = xs[0];
	results[1] = xs[1];
	results[2] = xs[2];
	results[3] = xs[3];
	results[4] = xs[4];

	log << "\n";
	for( unsigned int i=0; i < min.NDim(); ++i )
	{
		double errLow=0.0;
		double errUp=0.0;

		if ( (min.VariableName(i) == "s") ||
		     (min.VariableName(i) == "c") )
			continue;

		log << min.VariableName(i) << ": " << xs[i];
		if ( min.CovMatrix(i,i) != 0.0 )
		{
			log << " +/- " << xe[i];

			// Try to get more accurate errors using Minos (Asymmetric errors)
			if ( min.GetMinosError( i, errLow, errUp ) )
				log << " [" << errLow << ", +" <<errUp << "]";
		}
		log << "\n";
	}

	// min.PrintResults();

	log << "\n";


	OFmt rs(12,7);
	OFmt chi(9,4);
	log << "NCalls  : " << min.NCalls() << "\n";
	log << "Edm     : " << min.Edm() << "\n";
	log << "\n";
	log << "-- Goodness-of-Fit Statistics --\n\n";
	log << "R2      : " << rs << minimize.GetRsquared()     << " (Coefficient of Determination; R squared)\n";
	log << "adj. R2 : " << rs << minimize.GetAdjRsquared()  << " (Adjusted R Squared)\n";
	log << "r2      : " << rs << minimize.GetRsquaredMicromath() << " (Correlation Coefficient; R Squared in Micromath)\n";
	log << "SSE     : " << rs << minimize.GetSSE()          << " (Sum of Square Error)\n";
	log << "RMSE    : " << rs << minimize.GetRMSE()         << " (Root-Mean-Square Error; Standard Deviation)\n";
	log << "CV(RMSE): " << rs << minimize.GetCVRMSE()       << " (Coefficient of variation of the RMSE)\n";
	log << "Chi2    : " << chi << minimize.GetChiSquared()    << "\n";
	log << "Chi2/dof: " << chi << minimize.GetChiSquaredDOF() << "\n";


	return(true);
}

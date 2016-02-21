#include "sseos_params.h"
#include "sseos_y_finder.h"
#include "fitstatistics.h"
#include "OutputFormat.h"
#include "flags.h"
#include "outlog.h"

extern FitStatistics minimize;

void yfit( std::string ofile,
           const double Pstar, const double Vstar, const double Tstar )
{
	// Initial Guess for y.
	double y_initial =  0.65;

	struct sseos_params *p = new struct sseos_params;

	p->y  = y_initial;

	p->s  = 2.0;      // Same as used in ssfit()
	p->c  = p->s/3.0; // Constraint: s = 3c

	const std::vector< std::vector< double > >& Inputs = minimize.GetInputValues();
	const std::vector< double >& V = minimize.GetMeasuredValues();

	double yFit[ Inputs.size() ];
	double VFit[ Inputs.size() ];

	double Pprev = Inputs[0][0] / Pstar;

	for(unsigned int n = 0; n < Inputs.size(); n++) {
		p->Pr = Inputs[n][0] / Pstar;
		p->Vr = V[n] / Vstar;
		p->Tr = Inputs[n][1] / Tstar;

		// Reset initial guess for y for a new pressure sequence.
		if ( p->Pr != Pprev )
			p->y  = y_initial;

		sseos_y_finder( p );

		yFit[n] = p->y;
		VFit[n] = V[n];

		Pprev = p->Pr;

	}

	delete p;

	minimize.SetFitValues( VFit, yFit );

	outlog log(ofile.c_str());
	
	log << "Fitting only y.\n";
	log << "  * Utracki & Simha 2001 equation (2).\n\n";

	log << "--  Parameters --\n\n";
	log << "Pstar: " << Pstar << "\n";
	log << "Vstar: " << Vstar << "\n";
	log << "Tstar: " << Tstar << "\n\n";
}


#include<sstream>
#include<fstream>
#include<vector>
#include"fitstatistics.h"
#include"savedata.h"

extern FitStatistics minimize;

bool save_PVTVy(const std::string *saveprefix)
{
	std::ofstream out;
	std::stringstream ofilename;
	ofilename << *saveprefix << "-PVTVy.dat";

	out.open(ofilename.str().c_str(), std::ios::out);


	if ( out.is_open() )
	{
		std::vector< double > vfitvals;
		std::vector< double > yfitvals;
		minimize.GetFitValues( &vfitvals, &yfitvals );

		const std::vector< std::vector< double > >& Inputs = minimize.GetInputValues();
		const std::vector< double >& Measured = minimize.GetMeasuredValues();

		out << "# Pressure / Volume / Temperature / Fit Volume / Fit y\n";
		for(unsigned int n = 0; n < Inputs.size(); n++)
			out << Inputs[n][0]   << " "
			    << Measured[n]  << " "
			    << Inputs[n][1]   << " "
			    << vfitvals[n] << " "
			    << yfitvals[n] << "\n";
	}
	out.close();

	return true;
}

bool save_PVTy(const std::string *saveprefix)
{
	std::ofstream out;
	std::stringstream ofilename;
	ofilename << *saveprefix << "-PVTy.dat";

	out.open(ofilename.str().c_str(), std::ios::out);


	if ( out.is_open() )
	{
		std::vector< double > vfitvals;
		std::vector< double > yfitvals;
		minimize.GetFitValues( &vfitvals, &yfitvals );

		const std::vector< std::vector< double > >& Inputs = minimize.GetInputValues();
		const std::vector< double >& Measured = minimize.GetMeasuredValues();

		out << "# Pressure / Volume / Temperature / Fit y\n";
		for(unsigned int n = 0; n < Inputs.size(); n++)
			out << Inputs[n][0]   << " "
			    << Measured[n]  << " "
			    << Inputs[n][1]   << " "
			    << yfitvals[n] << "\n";
	}
	out.close();

	return true;
}

bool save_TVV(const std::string *saveprefix)
{
	std::ofstream out;
	std::stringstream ofilename;
	ofilename << *saveprefix << "-TVV.dat";

	out.open(ofilename.str().c_str(), std::ios::out);

	if ( out.is_open() )
	{
		std::vector< double > vfitvals;
		std::vector< double > yfitvals;
		minimize.GetFitValues( &vfitvals, &yfitvals );

		const std::vector< std::vector< double > >& Inputs = minimize.GetInputValues();
		const std::vector< double >& Measured = minimize.GetMeasuredValues();

		double Pprev = Inputs[0][0];
		out << "# Temperature / Volume / Fit Volumes\n#\n";
		out << "# " << Inputs[0][0] << "\n";
		for(unsigned int i=0; i < Inputs.size(); ++i)
		{
			// Add a blank line between groups of pressures
			if ( Inputs[i][0] != Pprev )
			{
				out << "\n";
				out << "# " << Inputs[i][0] << "\n";
			}

			out << Inputs[i][1] << " "
			    << Measured[i] << " "
			    << vfitvals[i] << "\n";

			Pprev = Inputs[i][0];
		}
		out.close();
	}

	return true;
}


#include <iostream>
#include <string>
#include <string.h>
#include "help.h"

char * word_wrap (char* string, const int line_width) {
	int i = 0;
	int k, counter;

	while( (i+line_width-1) < (int)strlen( string ) )
	{
		counter = i+line_width-1;

		// check for nearest whitespace back in string
		for ( k = counter; k > i; k--)
		{
			if ( isspace( string[k] ) )
			{
				string[k] = '\n';
				i = k + 1;
				break;
			}
		}
		if ( k == i ) // No white space found, then search forward.
		{
			for ( k = counter; k < (int)strlen(string); k++)
			{
				if ( isspace( string[k] ) )
				{
					string[k] = '\n';
					i = k+1;
					break;
				}
			}
			if ( k >= (int)strlen(string) )
				return(string);
		}
	}

	return(string);
}

void HelpIndented(const char *text, const unsigned int indent, const unsigned int wrap)
{
	char wrapped_text[strlen(text)+1];
	strcpy(wrapped_text,text);

	word_wrap(wrapped_text,wrap-indent);

	for( unsigned int i = 0; i < indent; i++)
		std::cerr << " ";

	for(unsigned int i=0; i < strlen(wrapped_text); i++)
	{
		std::cerr << wrapped_text[i];
		if ( wrapped_text[i] == '\n')
		{
			for( unsigned int ii = 0; ii < indent; ii++)
				std::cerr << " ";
		}
	}
	std::cerr << "\n";
}

void HelpOption(const char *v1, const char *v2, const char *text)
{
	int INDENT=8;
	int WRAP=76;

	if (v1 != NULL) HelpIndented(v1, INDENT, WRAP);
	if (v2 != NULL) HelpIndented(v2, INDENT, WRAP);
	if (text != NULL) HelpIndented(text, 2*INDENT, WRAP);

	std::cerr << "\n";
}

void Help(const char *name)
{
	std::cerr << "\n" << name << " Version ";
	std::cerr << ssfit_VERSION_MAJOR << ".";
	std::cerr << ssfit_VERSION_MINOR;
	std::cerr << "\n";
	std::cerr << "\n";

	std::cerr << "USAGE: " << "\n";
	const char *usage = "-i <input filename> -p <number> -v <number> -t <number> [-r <ranges filename>] [-R <pressure ranges filename>] [-s <save filename prefix>] [-n <number>] [--kelvin] [--curves] [--scan] [--data] [--approximate] [--fixp] [--fixv] [--fixt] [--blockdata]";
	std::string USAGE = name;
	USAGE += " ";
	USAGE += usage;
	HelpOption(USAGE.c_str(),
	           NULL,
	           NULL);
	std::cerr << "OPTIONS:" << "\n";
	HelpOption("--blockdata",
	           "-b",
	           "The data file is in block format.");
	HelpOption("--fixp",
	           NULL,
	           "Fix Pstar to the value specified on the command line.");
	HelpOption("--fixv",
	           NULL,
	           "Fix Vstar to the value specified on the command line.");
	HelpOption("--fixt",
	           NULL,
	           "Fix Tstar to the value specified on the command line.");
	HelpOption("--dataonly",
	           "--data, -d",
	           "Save the data in easy to plot files. This will not do any fitting.");
	HelpOption("--scan",
	           NULL,
	           "Scan the fitting parameters around the minimum after and initial fitting, following by a second round of fitting.");
	HelpOption("--curves",
	           NULL,
	           "Generate curves for nice plotting (see -n option).");
	HelpOption("--approximate",
	           "--approx",
	           "Use an approximate equation for fitting (See documentation for more details).");
	HelpOption("--kelvin",
	           NULL,
	           "The input temperatures are in Kelvin. The default is Celsius. All output temperatures are, however, in Kelvin.");
	HelpOption("--input <filename>",
	           "-i <filename>",
	           "Input file containing PVT data.");
	HelpOption("--ranges <filename>",
	           "-r <filename>",
	           "File specifying the temperature ranges, for each pressure, to use for fitting and curve generating.");
	HelpOption("--pranges <filename>",
	           "-R <filename>",
	           "File specifying the pressure ranges, for each temperature, to use for  curve generating.");
	HelpOption("--pstar <number>",
	           "-p <number>",
	           "Initial Pstar value to use for fitting.");
	HelpOption("--vstar <number>",
	           "-v <number>",
	           "Initial Vstar value to use for fitting.");
	HelpOption("--tstar <number>",
	           "-t <number>",
	           "Initial Tstar value to use for fitting.");
	HelpOption("--numpoints <number>",
	           "-n <number>",
	           "Number of points to use for curve generation.");
	HelpOption("--yonly",
	           "-y",
	           "Only calculate y. Used to T < Tg. pstar, vstar, and tstar are fixed.");
	HelpOption("--save <filename>",
	           "-s <filename>",
	           "Name use as prefix for saving data. If not specified then 'default' will be used. The type of data will be appended to this, for example: using '--save Polystyrene' will save data as 'Polystyrene-PVTVy.dat'.");
	HelpOption("--help",
	           "-h",
	           "Show this help.");

	std::cerr << "\n";
	std::cerr << "Compiled on " << __DATE__;
	std::cerr << " at " << __TIME__ << ".\n";
	std::cerr << "Author: Brian G. Olson (olsonbg@gmail.com)\n";
	std::cerr << "https://github.com/olsonbg/ssfit\n";
}


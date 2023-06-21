#include <iostream>
#include <fstream>
#include <getopt.h>
#include <stdlib.h>
#include "flags.h"
#include "process.h"
#include "help.h"

int main(int argc, char *argv[]) {
	// char ifile[4097] = "input.dat";
	std::string ifile;
	std::string ifileTRanges;
	std::string ifilePRanges;
	std::string saveprefix = "default";

	double pstar = 0.0;
	double vstar = 0.0;
	double tstar = 0.0;

	bool pset = false;
	bool vset = false;
	bool tset = false;

	// Number of points to calculate for curves.
	unsigned int numpoints = 100;

	int  flag[(unsigned int)Flags::COUNT] = {}; // Initialize all elements of flag to zero.
	unsigned int flags = 0;

	// Read command line arguments.
	int c;
	while(1)
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose"   , no_argument, &flag[0], (unsigned int)Flags::VERBOSE   },
			{"blockdata" , no_argument, &flag[1], (unsigned int)Flags::BLOCKDATA },
			{"fixp"      , no_argument, &flag[2], (unsigned int)Flags::FIXED_P   },
			{"fixv"      , no_argument, &flag[3], (unsigned int)Flags::FIXED_V   },
			{"fixt"      , no_argument, &flag[4], (unsigned int)Flags::FIXED_T   },
			{"dataonly"  , no_argument, &flag[5], (unsigned int)Flags::DATAONLY  },
			{"scan"      , no_argument, &flag[6], (unsigned int)Flags::SCAN      },
			{"curves"    , no_argument, &flag[7], (unsigned int)Flags::CURVES    },
			{"approximate",no_argument, &flag[8], (unsigned int)Flags::APPROXIMATE},
			{"approx"    , no_argument, &flag[8], (unsigned int)Flags::APPROXIMATE},
			{"kelvin"    , no_argument, &flag[9], (unsigned int)Flags::KELVIN    },
			/* These options don’t set a flag.
			   We distinguish them by their indices. */
			{"input",       required_argument, 0, 'i'},
			{"tranges",     required_argument, 0, 'r'},
			{"pranges",     required_argument, 0, 'R'},
			{"save",        required_argument, 0, 's'},
			{"pstar",       required_argument, 0, 'p'},
			{"vstar",       required_argument, 0, 'v'},
			{"tstar",       required_argument, 0, 't'},
			{"numpoints",   required_argument, 0, 'n'},
			{"blockdata"  , no_argument,       0, 'b'},
			{"data"       , no_argument,       0, 'd'},
			{"yonly"      , no_argument,       0, 'y'},
			{"help",        no_argument,       0, 'h'},
			{0, 0, 0, 0}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "i:r:R:s:p:v:t:n:bdyh",
		                 long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				// std::cout << "#Option: " << long_options[option_index].name;
				// if (optarg)
				//     std::cout << " with arg " <<  optarg;
				// std::cout << "\n";
				break;
			case 'i':
				ifile = optarg;
				break;
			case 'r':
				ifileTRanges = optarg;
				break;
			case 'R':
				ifilePRanges = optarg;
				break;
			case 's':
				saveprefix = optarg;
				break;
			case 'p':
				pset = true;
				pstar = strtod( optarg, NULL );
				break;
			case 'v':
				vset = true;
				vstar = strtod( optarg, NULL );
				break;
			case 't':
				tset = true;
				tstar = strtod( optarg, NULL );
				break;
			case 'n':
				numpoints = atoi( optarg );
				break;
			case 'b':
				flags |= (unsigned int)Flags::BLOCKDATA;
				break;
			case 'd':
				flags |= (unsigned int)Flags::DATAONLY;
				break;
			case 'y':
				flags |= (unsigned int)Flags::YONLY;
				flags |= (unsigned int)Flags::FIXED_P|Flags::FIXED_V|Flags::FIXED_T;
				break;
			case 'h':
				Help( argv[0] );
				return EXIT_SUCCESS;
			case '?':
				std::cerr << "Use the '-h' or '--help' options for help.\n";
				return EXIT_FAILURE;
			default:
				return EXIT_FAILURE;
		}
	}
	// Done reading command line arguments

	// Set the flags;
	for ( unsigned int i=0; i < (unsigned int)Flags::COUNT; i++ ) {
		flags |= flag[i];
	}

	if ( (flags & Flags::YONLY) && (flags & Flags::CURVES) )
	{
		std::cout << "Can not use 'curves' and 'yonly' flags together.\n";
		return EXIT_FAILURE;
	}
	if ( !(flags & Flags::DATAONLY) && !(pset&vset&tset) )
	{
		std::cout << "Must specify values for pstar, vstar, and tstar\n";
		return EXIT_FAILURE;
	}
	if ( (flags & Flags::BLOCKDATA) && ( !(flags & Flags::DATAONLY) && ifileTRanges.empty() ) )
	{
		std::cout << "Must specify a temperature ranges file when using blockdata\n";
		return EXIT_FAILURE;
	}

	if ( (flags & Flags::CURVES) && ifileTRanges.empty() )
	{
		std::cout << "A ranges file is needed to generate curves.\n";
		return EXIT_FAILURE;
	}

	process(ifile, ifileTRanges, ifilePRanges, saveprefix,
	        pstar, vstar, tstar, numpoints,flags);

	return EXIT_SUCCESS;
}

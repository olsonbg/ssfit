/**
 * \file
 * \brief Class to log data to screen and a file
 */
#ifndef _OUTLOG_H
#define _OUTLOG_H

#include <iostream>
#include <fstream>

/**
 * \brief Log data to screen and a file
 */
class outlog {
	private:
		std::ofstream logfile;
	public:
		outlog(const char* file)
		{
			logfile.open(file);

			if (!(logfile.is_open())) {
				std::cerr << "[]: Couldn't open file \"" << file << "\" for logging.\n";
			}
		}

		~outlog()
		{
			if (logfile.is_open())
				logfile.close();
		}

		template <class T>
			outlog& operator<<(const T& out)
			{
				std::cout << out;
				if (logfile.is_open() )
					logfile << out;

				return *this;
			}
};

#endif // _OUTLOG_H

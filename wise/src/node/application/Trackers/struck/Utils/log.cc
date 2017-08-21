// Simple log class

#include "log.h"

using namespace std;
	
// Generic log method
ostream& Log::log(ostream& str, bool print_frame_num)
{
	if(print_frame_num)
	{
		return str << current_frame << ": ";
	}
	else
	{
		return str;
	}
}

/*// Set output file paths
void Log::setInfoLogFile(const char* path)
{
	// Delete previous log - DON'T, GIVES PROBLEMS IF log == cout!
	//if(info_log != NULL)
	//{
	//	delete info_log;
	//}
	// Create new log
	info_log = new ofstream(path);
}

void Log::setWarningLogFile(const char* path)
{
	// Delete previous log
	//if(warning_log != NULL)
	//{
	//	delete warning_log;
	//}
	// Create new log
	warning_log = new ofstream(path);
}

void Log::setErrorLogFile(const char* path)
{
	// Delete previous log
	//if(error_log != NULL)
	//{
	//	delete error_log;
	//}
	// Create new log
	error_log = new ofstream(path);
}

void Log::setDebugLogFile(const char* path)
{
	// Delete previous log
	//if(debug_log != NULL)
	//{
	//	delete debug_log;
	//}
	// Create new log
	debug_log = new ofstream(path);
}*/

//void Log::closeLogs() // DON'T!
//{
	//if(info_log != NULL)	delete info_log;
	//if(warning_log != NULL)	delete warning_log;
	//if(error_log != NULL)	delete error_log;
	//if(debug_log != NULL)	delete debug_log;
//}

// Initialize frame number
int Log::current_frame = 0;
// Initialize default outputs
ostream* Log::info_log = new ostream(0);
ostream* Log::warning_log = new ostream(0);
ostream* Log::error_log = new ostream(0);
ostream* Log::debug_log = new ostream(0);

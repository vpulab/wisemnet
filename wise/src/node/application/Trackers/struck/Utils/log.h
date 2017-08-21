// Simple log class

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

/** \brief Logging class.
 *
 * Allows to set four verbosity levels for log messages (debug, info, warning and error) and to specific an output stream for each of them (thus allowing to disable the output for a specific level)
 */ 
class Log
{
	private:

	// Current frame number
	static int current_frame;

	/*// Log output paths
	static string info_path;
	static string warning_path;
	static string error_path;
	static string debug_path;*/

	// Log output files
	static std::ostream* info_log;
	static std::ostream* warning_log;
	static std::ostream* error_log;
	static std::ostream* debug_log;

	// Generic log method
	static std::ostream& log(std::ostream& str, bool print_frame_num = true);

	public:

	// Frees streams
	//static void closeLogs();

	/** \brief Sets the current frame number.
	 *
	 * It will be output at the beginning of the log message.
	 * \param frame Current frame number
	 */
	static inline void setFrameNumber(int frame) { current_frame = frame; }

	// Set output file paths
	/*static void setInfoLogFile(const char* path);
	static void setWarningLogFile(const char* path);
	static void setErrorLogFile(const char* path);
	static void setDebugLogFile(const char* path);*/
	
	/** \name Output stream setters
	 *
	 * Set the output stream for the specified log level.
	 * \param out Output stream
	 */
	/**@{*/
	static inline void setInfoLogStream(std::ostream& out) { info_log = &out; }
	static inline void setWarningLogStream(std::ostream& out) { warning_log = &out; }
	static inline void setErrorLogStream(std::ostream& out) { error_log = &out; }
	static inline void setDebugLogStream(std::ostream& out) { debug_log = &out; }
	/**@}*/

	/** \name Log methods.
	 *
	 * \param print_frame_num If true, prepend the current frame number to the log message.
	 */
	/**@{*/
	static inline std::ostream& info(bool print_frame_num = true) { return log(*info_log, print_frame_num); }
	static inline std::ostream& warning(bool print_frame_num = true) { return log(*warning_log, print_frame_num); }
	static inline std::ostream& error(bool print_frame_num = true) { return log(*error_log, print_frame_num); }
	static inline std::ostream& debug(bool print_frame_num = true) { return log(*debug_log, print_frame_num); }
	/**@}*/

	/** \name Short versions of log methods.
	 *
	 * These do not allow to print the current frame number.
	 */
	/**@{*/
	static inline std::ostream& i() { return info(0); }
	static inline std::ostream& w() { return warning(0); }
	static inline std::ostream& e() { return error(0); }
	static inline std::ostream& d() { return debug(0); }
	/**@}*/


};

#endif

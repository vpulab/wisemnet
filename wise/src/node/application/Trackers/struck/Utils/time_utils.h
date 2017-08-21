// Class for some time-related stuff...

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <ctime>

//using namespace std;

/*class TimeUtils
{
	static long tic_time;

	public:

	// Set the initial time for the stopwatch
	static void tic();

	// Set the final time for the stopwatch and display the time interval
	static void toc();

	static long datetimeToLong(string datetime);
};*/

/** Simple timer class.
 */
class TimeInterval
{
	bool use_monotonic;
	struct timespec start, stop;

	public:

	/** Constructor.
	 *
	 * Checks for the availability of CLOCK_MONOTONIC and CLOCK_REALTIME.
	 */
	TimeInterval();

	/** Set the initial time for the stopwatch.
	 */
	void tic();

	/** Set the final time for the stopwatch.
	 * \returns Elapsed time interval since \c tic().
	 */
	double toc();
};

#endif

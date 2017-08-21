// Class for some time-related stuff...

#include "time_utils.h"
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

//long TimeUtils::tic_time = 0;

// Set the initial time for the stopwatch
/*void TimeUtils::tic()
{
	tic_time = clock();
}

// Set the final time for the stopwatch and display the time interval
void TimeUtils::toc()
{
	long stop_time = clock();
	long diff = stop_time - tic_time;
	cout << "Elapsed time: " << ((double) diff)/CLOCKS_PER_SEC << " seconds." << endl;
}
	
long TimeUtils::datetimeToLong(string datetime)
{
	return 0;
}*/
	
// Constructor; checks for the availability of CLOCK_MONOTONIC and CLOCK_REALTIME
TimeInterval::TimeInterval()
{
	if(sysconf(_SC_MONOTONIC_CLOCK) > 0)
	{
		use_monotonic = true;
	}
	else
	{
		use_monotonic = false;
	}
}

// Set the initial time for the stopwatch
void TimeInterval::tic()
{
	clock_gettime(use_monotonic ? CLOCK_MONOTONIC : CLOCK_REALTIME, &start);
}

// Set the final time for the stopwatch and display the time interval
double TimeInterval::toc()
{
	clock_gettime(use_monotonic ? CLOCK_MONOTONIC : CLOCK_REALTIME, &stop);
	double elapsed = stop.tv_sec - start.tv_sec;
	elapsed += (stop.tv_nsec - start.tv_nsec)/1000000000.0;
	return elapsed;
}

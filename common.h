#pragma once

#include <sched.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

inline double GetTime()
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (double)t.tv_sec + (double)t.tv_nsec/(1000000000L);
}

inline void BusySleepUs(uint64_t us)
{
	struct timespec tv;
	clock_gettime(CLOCK_MONOTONIC, &tv);
	uint64_t ts = tv.tv_nsec;
	while(true)
	{
		clock_gettime(CLOCK_MONOTONIC, &tv);
		uint64_t tc = tv.tv_nsec;
		if (tc - ts >= us * 1000)
		{
			break;
		}
	}
}

inline void SleepUs(uint64_t us)
{
    usleep(us);
}

inline void SetMaxPriority(void) 
{
    // set current process to max priority to avoid context switch
    struct sched_param sched;
    memset(&sched, 0, sizeof(sched));
    sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &sched);
}

inline void SetDefaultPriority(void) 
{
    // set priority back to default
    struct sched_param sched;
    memset(&sched, 0, sizeof(sched));
    sched.sched_priority = 0;
    sched_setscheduler(0, SCHED_OTHER, &sched);
}



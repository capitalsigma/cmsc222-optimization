
/* these are needed for RUSAGE_THREAD and timersub to work */
#define _GNU_SOURCE
#define _BSD_SOURCE


#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>

#include "perf.h"
#include "error.h"
#include "util.h"

typedef struct rusage rusage;
typedef struct timeval timeval;
typedef struct timespec timespec;

typedef struct _monitor {
	timespec wall_start;
	timespec wall_end;
	

	/* rusage structs have a huge amount of info, we'll use this file */
	/* to provide an interface to the parts that we care about */
	rusage start;
	rusage end;

	/* enum lets us specify what we want to keep track of --  */
	/* whole process, child processes, or current thread */
	int who;

} monitor;

typedef enum {START, END} action;

monitor *monitor_init(monitor_target who) 
{
	/* we use an assertion here because... */
	/*    a) these are preconditions for init  */
	/*    b) we can optimize them away later in life */
	assert(who == SELF || 
		   who == CHILDREN ||
		   who == THREAD);

	int who_vals[] = {RUSAGE_SELF, RUSAGE_CHILDREN, RUSAGE_THREAD};

	monitor *m = malloc(sizeof(monitor));

	/* m->start = NULL; */
	/* m->end = NULL; */
	m->who = who_vals[who];
	
	return m;
}

void do_action(monitor *m, action a)
{
	rusage *to_set = a == START ?  &m->start : &m->end;
	timespec *to_set_wall = a == START ? &m->wall_start : &m->wall_end;

	/* assert(!(*to_set)); */
	HANDLE(getrusage(m->who, to_set) != 0);
	HANDLE(clock_gettime(CLOCK_MONOTONIC, to_set_wall));
}

void monitor_start(monitor *m)
{
	LOGGER();

	do_action(m, START);
}

void monitor_end(monitor *m)
{
	LOGGER();

	do_action(m, END);
}

void monitor_free(monitor *m)
{
	free(m);
}

void print_time(timeval t, bool newline)
{
	printf("%li s, %li us", t.tv_sec, t.tv_usec);
	if(newline){
		printf("\n");
	}
}

/* we follow the signature of timersub here as an example */
/* this just subtracts each of the structs values element-wise, see  */
/* man 2 getrusage for more details */
void rusage_sub(rusage *a, rusage *b, rusage *res)
{
	timeval diff_user, diff_sys;

	timersub(&b->ru_utime, &a->ru_utime, &diff_user);
	timersub(&b->ru_stime, &a->ru_stime, &diff_sys);

	res->ru_utime = diff_user;
	res->ru_stime = diff_sys;

	res->ru_maxrss = b->ru_maxrss - a->ru_maxrss;
	res->ru_minflt = b->ru_minflt - a->ru_minflt;
	res->ru_majflt = b->ru_majflt - a->ru_majflt;
	res->ru_inblock = b->ru_inblock - a->ru_inblock;
	res->ru_oublock = b->ru_oublock - b->ru_oublock;
	res->ru_nvcsw = b->ru_nvcsw - a->ru_nvcsw;
	res->ru_nivcsw = b->ru_nivcsw - a->ru_nivcsw;
}

void timespec_sub(timespec *a, timespec *b, timespec *res)
{
	timespec diff;

	diff.tv_nsec = 0;

	diff.tv_sec = difftime(b->tv_sec, a->tv_sec);

	if(a->tv_nsec > b->tv_nsec){
		diff.tv_sec -= 1;
		diff.tv_nsec = a->tv_nsec - b->tv_nsec;
	}
		

	*res = diff;
}

/* verbosity = SILENT, QUET, VERBOSE */
/* 0: just print user CPU time */
/* 1: print user CPU time + system CPU time */
/* 2: print everything */
/*    ie user, system CPU time, pagefaults, input, output, context switches */
void monitor_print_stats(monitor *m, verbosity v)
{
	rusage diff;
	timespec wall_diff;

	rusage_sub(&m->start, &m->end, &diff);
	timespec_sub(&m->wall_start, &m->wall_end, &wall_diff);
	
	if(v != SILENT){
		printf("User CPU time: ");
	}

	print_time(diff.ru_utime, true);
	
	if(v > SILENT){
		printf("System CPU time: ");
		print_time(diff.ru_stime, true);
	}

	if(v == VERBOSE){
		printf("Maximum resident size (KB): %li\n", diff.ru_maxrss);
		printf("Page faults serviced without IO: %li\n", diff.ru_minflt);
		printf("Page faults erviced with IO: %li\n", diff.ru_majflt);
		printf("Instances of input: %li\n", diff.ru_inblock);
		printf("Instnaces of output: %li\n", diff.ru_oublock);

		/* NB: these are usually caused by threads waiting for resources */
		/* if its high, it might indicate that threads should be pushed up */
		printf("Voluntary context switches: %li\n", diff.ru_nvcsw);

		printf("Involuntary context switches: %li\n", diff.ru_nivcsw);
	}

	printf("Wall time: %li s, %li ns\n", (long)wall_diff.tv_sec, wall_diff.tv_nsec);
}

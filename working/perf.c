#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "perf.h"

typedef enum {START, STOP} action;

typedef struct {
	/* rusage structs have a huge amount of info, we'll use this file */
	/* to provide an interface to the parts that we care about */
	rusage start;
	rusage end;

	/* enum lets us specify what we want to keep track of --  */
	/* whole process, child processes, or current thread */
	int who;

} monitor;

monitor *init(int who) 
{
	/* we use an assertion here because... */
	/*    a) these are preconditions for init  */
	/*    b) we can optimize them away later in life */
	assert(who == RUSAGE_SELF || 
		   who == RUSAGE_CHILDREN ||
		   who == RUSAGE_THREAD)

	monitor *m = malloc(sizeof(monitor));

	m->start = NULL;
	m->end = NULL;
	m->who = who;
	
	return m;
}

void action(monitor *m, action a)
{
	rusage *to_set = a == START ?  &m->start : &m->end;

	assert(!(*to_set));

	if(getrusage(m->who, to_set) < 0){
		/* error handle */
	}

	
}
		

/* TODO: error handling in here */
/* void start(monitor *m) */
/* { */
/* 	/\* we should only ever start unstarted timers *\/ */
/* 	assert(!m->start); */

/* 	if(getrusage(m->who, &m->start) */

		

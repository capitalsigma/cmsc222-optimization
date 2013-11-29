#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"

/* NOTE: LOOKS LIKE THIS IS A REALLY BAD IDEA, 
   APPARENTLY IT MEASURES WALL TIME, CHANGE THIS  */
typedef struct {
	timeval start;
	timeval end;
} timer;

timer *init() 
{
	timer *t = malloc(sizeof(timer));

	t->start = NULL;
	t->end = NULL;
}

init start(*timer t)
{
	/* we should only ever start unstarted timers */
	assert(!t->start);

	t->start 

		

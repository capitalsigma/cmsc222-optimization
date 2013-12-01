/* Bubble sort code */
/* we have to define this before we import anything */
#include <assert.h>
#include <stdio.h>

#include "util.h"
#include "perf.h"
#include "array_size.h"


/* note: see http://en.cppreference.com/w/c/atomic */
static inline void bsort(int (*array)[], int n)
{
	int c, d, swap;
  for (c = 0 ; c < ( n - 1 ); c++)
  {
	  for (d = 0 ; d < n - c - 1; d++)
	  {
		  if ((*array)[d] > (*array)[d+1]) /* For decreasing order use < */
		  {
			  swap       = (*array)[d];
			  (*array)[d]   = (*array)[d+1];
			  (*array)[d+1] = swap;
		  }
	  }
  }
}
	

int main(int argc, char* argv[])
{
  int n = ARRAY_SIZE;
  int array[ARRAY_SIZE];
  monitor *m;
  
  make_array(&array, n, ARRAY_ALGO); 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  m = monitor_init(SELF);
  monitor_start(m);

  bsort(&array, n);
  
  monitor_end(m);
 
  assert(verify(&array, n));
  /* print_array(&array, n, OUT_LINE_SIZE); */
  
  monitor_print_stats(m, VERBOSE);

  return 0;
}

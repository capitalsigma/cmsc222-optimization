/* Bubble sort code */
/* we have to define this before we import anything */
#include <assert.h>
#include <stdio.h>

#include "util.h"
#include "perf.h"

#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M

#define OUT_LINE_SIZE 80
#define ARRAY_ALGO SHIFT_MOD

/* note: see http://en.cppreference.com/w/c/atomic */

int main(int argc, char* argv[])
{
  int n = SMALL;
  int array[SMALL], c, d, swap;
  monitor *m;
  
  make_array(&array, n, ARRAY_ALGO); 
  print_array(&array, n, OUT_LINE_SIZE);

  m = monitor_init(SELF);
  monitor_start(m);

  for (c = 0 ; c < ( n - 1 ); c++)
  {
	  for (d = 0 ; d < n - c - 1; d++)
	  {
		  if (array[d] > array[d+1]) /* For decreasing order use < */
		  {
			  swap       = array[d];
			  array[d]   = array[d+1];
			  array[d+1] = swap;
		  }
	  }
  }
  
  monitor_end(m);
 
  assert(verify(&array, n));
  print_array(&array, n, OUT_LINE_SIZE);
  
  monitor_print_stats(m, VV

  return 0;
}

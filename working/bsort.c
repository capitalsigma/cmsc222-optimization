/* Bubble sort code */
#include <stdio.h>
#include <assert.h>
#include "util.h"

#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M

int main(char* argv[], int argc)
{
  int n = SMALL;
  int array[SMALL], c, d, swap;
  
  make_array(array, n);
 
  printf("Sorting %d integers\n You should try to time this part. \n", n);
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
 
  assert(verify(array, n));
  print_list(array, n, 80);
  

  return 0;
}

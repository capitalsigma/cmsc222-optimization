/* Bubble sort code */
 
#include <stdio.h>

#define SMALL 1000         // 1K
#define MEDIUM  10000      // 10K
#define LARGE  100000    // 100k
#define XLARGE  1000000  // 1M
 
int main()
{
  int n = SMALL;
  int array[SMALL], c, d, swap;
 
  printf("Generating %d integers\n", n);
 
  for (c = 0; c < n; c++){
    array[c] = (c << 6) % (17*17); 
  }
 
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
 
  printf("Verifying Sorted list in ascending order:\n");
 
  for ( c = 0 ; c < n-1 ; c++ )
    if (array[c] > array[c+1])   printf("Whoops: error at position %d\n", c);
 
  return 0;
}

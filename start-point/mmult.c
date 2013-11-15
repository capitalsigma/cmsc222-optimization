#include <stdio.h>


#define TINY 10         // 10x10
#define SMALL  100      // 100x100
#define MEDIUM 1000    // 1000x1000
#define LARGE 5000    // 5000x5000
#define YOURSIZE 100    // define your own
 
int main()
{
  int c, d, k, sum = 0;

  int size = MEDIUM;
  int first[size][size], multiply[size][size];

  printf("Generating the matrix\n");
 
  for (  c = 0 ; c < size ; c++ )
    for ( d = 0 ; d < size ; d++ )
      first[c][d] = ((c+d) % 2) - 1;
 
  printf("multiplying the matrices\n  You should try to time this part.\n");

      for ( c = 0 ; c < size ; c++ )
	{
	  for ( d = 0 ; d < size ; d++ )
	    {
	      for ( k = 0 ; k < size ; k++ )
		{
		  sum += first[c][k]*first[k][d];
		}
 
	      multiply[c][d] = sum;
	      sum = 0;
	    }
	}
 
  return 0;
}

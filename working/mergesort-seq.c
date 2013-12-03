/* Bubble sort code */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "array_size.h"


int tmp[ARRAY_SIZE] = {}; 

void merge(int **array, int lo, int mid, int hi)
{
	LOGGER();
	
	/* i is our index for the left half */
	/* j is for the right half */
	/* k is for the temporary sorting (*array) */
	int i = lo, j = mid + 1, k = lo;
	while (i <= mid && j <= hi) {
		tmp[k++] = (*array)[i] < (*array)[j] ? (*array)[i++] : (*array)[j++];
	}
	
	while(i <= mid) {		
		tmp[k++] = (*array)[i++];
	}
	while(j <= hi) {
		tmp[k++] = (*array)[j++];
	}

	/* copy back */
	for(int n = lo; n < k; n++){
		(*array)[n] = tmp[n];
	}
}

void mergesort(int **array, int lo, int hi)
{
	/* LOGGER(); */
	if (lo < hi){
		int mid = (hi + lo) / 2;
		mergesort(array, lo, mid);
		mergesort(array, mid + 1, hi);
		merge(array, lo, mid, hi);
	}
}

void msort(int **array, int size)
{
	LOGGER();
	mergesort(array, 0, size - 1);
}


int main(int argc, char *argv[])
{
  int n = ARRAY_SIZE;
  int *array;
  HANDLE(!(array = malloc(n * sizeof(int)))); 
  monitor *m;
  
  make_array(&array, n, ARRAY_ALGO, 17 * 17); 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  m = monitor_init(SELF);
  monitor_start(m);

  msort(&array, n);
  
  monitor_end(m);
 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  assert(verify(&array, n));

  free(array);
  
  monitor_print_stats(m, VERBOSE);
  monitor_free(m);

  return 0;
}

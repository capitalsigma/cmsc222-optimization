/* Bubble sort code */
/* we have to define this before we import anything */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC

#include "util.h"
#include "error.h"
#include "perf.h"
#include "array_size.h"
#include "worker_pool.h"

void merge(int *array, int lo, int mid, int hi)
{
	LOGGER();
	int *tmp;
	HANDLE((tmp = malloc(sizeof(int) * (hi - lo))));
	assert(tmp);

	NOTIFY(PV(lo);PV(hi);PV(mid));

	/* i is our index for the left half */
	/* j is for the right half */
	/* k is for the temporary sorting array */
	int i = lo, j = mid, k = 0;
	NOTIFY(PV(i);PV(j););
	while (i <= mid && j < hi) {
		NOTIFY(PV(i);PV(j););
		tmp[k++] = array[i] < array[j] ? array[i++] : array[j++];
	}

	/* NOTIFY(PV(tmp[0]);PV(tmp[k]);PV(array[lo]);PV(&array);); */
	/* copy back */
	memcpy((array + lo), tmp, k * sizeof(int));
	free(tmp);
}

void mergesort(int *array, int lo, int hi)
{
	LOGGER();
	if (lo < hi){
		int mid = (hi + lo) / 2;
		mergesort(array, lo, mid);
		mergesort(array, mid + 1, hi);
		merge(array, lo, mid, hi);
	}
}

void msort(int *array, int size)
{
	LOGGER();
	mergesort(array, 0, size);
}


int main(int argc, char *argv[])
{
  int n = ARRAY_SIZE;
  int *array;
  HANDLE(array = malloc(n * sizeof(int))); 
  NOTIFY(PV(array));
  monitor *m;
  
  make_array(array, n, ARRAY_ALGO); 
  NOTIFY(print_array(array, n, OUT_LINE_SIZE));
  NOTIFY(PV(array));

  m = monitor_init(SELF);
  monitor_start(m);

  NOTIFY(PV(array));

  msort(array, n);
  
  monitor_end(m);
 
  assert(verify(array, n));
  /* print_array(&array, n, OUT_LINE_SIZE); */
  
  monitor_print_stats(m, VERBOSE);

  return 0;
}

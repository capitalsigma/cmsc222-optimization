/* Bubble sort code */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "array_size.h"
#include "atomic_int.h"

#define RANGE 289

/* int tmp[RANGE] = {};  */


void populate_tmp(int *array, atomic_int *tmp[], int end)
{
#pragma omp parallel for
	for(int i = 0; i < end; i++){
		atomic_increment(tmp[array[i]], true);
	}
}

void unroll_tmp(int *array, atomic_int *tmp[], int range)
{
	int counter = 0;
	{
		for(int i = 0; i < range; i++){
			while(nonatomic_decrement(tmp[i], false)){
				array[counter++] = i;
			}
		}
	}
}


void csort(int *array, int size)
{
	atomic_int *tmp[RANGE + 1];
	int i;
	
	#pragma omp parallel for
	for(i = 0; i < RANGE; i++){
		tmp[i] = initialize_atomic_int(0);
	}

	populate_tmp(array, tmp, size);

	/* writeback, sequentially */
	unroll_tmp(array, tmp, RANGE);

	/* free everything */
	#pragma omp parallel for
	for(i = 0; i < RANGE; i++){
		free_atomic_int(tmp[i]);
	}

}


int main(int argc, char *argv[])
{
  int n = ARRAY_SIZE;
  int *array;
  HANDLE(!(array = malloc(n * sizeof(int)))); 
  monitor *m;
  
  make_array(&array, n, ARRAY_ALGO); 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  m = monitor_init(SELF);
  monitor_start(m);

  csort(array, n);
  
  monitor_end(m);
 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  assert(verify(&array, n));

  free(array);
  
  monitor_print_stats(m, VERBOSE);
  monitor_free(m);

  return 0;
}

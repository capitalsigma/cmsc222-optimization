/* Bubble sort code */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "array_size.h"

#define RANGE 290

int tmp[RANGE] = {0}; 



void populate_tmp(int *array, int n)
{
	for(int i = 0; i < n; i++){

		__sync_add_and_fetch(&tmp[array[i]], 1);
	}
}

void unroll_tmp(int *array, int range)
{
	int counter = 0;
	for(int i = 0; i < range; i++){
		while(tmp[i]--){
			array[counter++] = i;
		}
	}
}

void csort(int *array, int size)
{
	populate_tmp(array, size);
	
	unroll_tmp(array, RANGE);
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

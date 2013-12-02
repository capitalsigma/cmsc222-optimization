/* Bubble sort code */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "array_size.h"
#include "worker_pool.h"

#define WORKER_THREADS 12

typedef struct {
	int **array;
	int lo;
	int hi;
	worker_pool *wp;
} args_t;
	
void *mergesort_p(void *args);

int tmp[ARRAY_SIZE] = {}; 

args_t *make_args(int **array, int lo, int hi, worker_pool *wp)
{
	/* LOGGER(); */
	args_t *ret = malloc(sizeof(args_t));
	ret->array = array;
	ret->lo = lo;
	ret->hi = hi;
	ret->wp = wp;
	
	return ret;
}


void print_args(args_t *args)
{
	printf("array addr: %p, lo = %i, hi = %i, &wp = %p", 
	       args->array, args->lo, args->hi, args->wp);
}

void free_args(args_t *ags)
{
	free(ags);	
}

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


pthread_t *start_worker(int **array, int lo, int hi, worker_pool *wp)
{
	pthread_t *th = NULL;
	args_t *args = NULL;

	if(request_worker(wp)){
		HANDLE(!(th = malloc(sizeof(pthread_t))));
		args = make_args(array, lo, hi, wp);
		HANDLE(pthread_create(th, NULL, mergesort_p, args));
	}

	return th;
}

void mergesort(int **array, int lo, int hi, worker_pool *wp)
{
	LOGGER();
	int mid = (hi + lo) / 2;
	pthread_t *th1, *th2;


	if (lo < hi){
		/* spin up a new thread to handle it if we can, if not, continue */
		/* in the current thread */

		if(!(th1 = start_worker(array, lo, mid, wp))){
			mergesort(array, lo, mid, wp);
		}

		if(!(th2 = start_worker(array, mid + 1, hi, wp))){
			mergesort(array, mid + 1, hi, wp);
		}

		/* block until as many threads return as necessary */
		if(th1){
			return_worker(wp, th1);
		}
		if(th2){
			return_worker(wp, th2);
		}
		
		merge(array, lo, mid, hi);
	}
}


void *mergesort_p(void *args)
{
	LOGGER();

	args_t *ags = (args_t *)args;
	/* print_args(ags); */

	mergesort(ags->array, ags->lo, ags->hi, ags->wp);

	free_args(ags);
	pthread_exit((void *)NULL);
}

void msort(int **array, int size)
{
	LOGGER();
	/* we pass around a counter of how many threads there are available */
	/* to do work */
	worker_pool *wp = initialize_pool(WORKER_THREADS);
	mergesort(array, 0, size - 1, wp);	
	free_pool(wp);
}


int main(int argc, char *argv[])
{
  int n = ARRAY_SIZE;
  int *array;
  monitor *m;

  HANDLE(!(array = malloc(n * sizeof(int)))); 

  make_array(&array, n, ARRAY_ALGO); 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));

  m = monitor_init(SELF);
  monitor_start(m);

  msort(&array, n);
  
  monitor_end(m);
 
  NOTIFY(print_array(&array, n, OUT_LINE_SIZE));
  assert(verify(&array, n));
  
  monitor_print_stats(m, VERBOSE);

  monitor_free(m);
  free(array);

  return 0;
}

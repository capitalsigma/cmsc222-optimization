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

#define RANGE 289

int tmp[RANGE + 1] = {};

typedef struct {
	int **array;
	int start;
	int end;
} args_t;

args_t *make_args(int **array, int start, int end)
{
	args_t *ret;
	HANDLE(!(ret = malloc(sizeof(args_t))));

	ret->array = array;
	ret->start = start;
	ret->end = end;

	return ret;
}

void free_args(args_t *args)
{
	free(args);
}

void populate_tmp(int **array, int start, int end)
{
	for(int i = start; i < end; i++){
		__sync_fetch_and_add(&tmp[(*array)[i]], 1);
	}
}

void unroll_tmp(int **array, int range)
{
	int counter = 0;
	for(int i = 0; i < range; i++){
		while(tmp[i]--){
			(*array)[counter++] = i;
		}
	}
}


void *populate_tmp_p(void *args_p)
{
	LOGGER();
	args_t *args = (args_t *)args_p;

	populate_tmp(args->array, args->start, args->end);
	
	free_args(args);
	pthread_exit((void *)NULL);
}


void csort(int *array, int size)
{
	/* int tmp[RANGE + 1] = {0}; */
	pthread_t *workers[WORKER_THREADS];
	args_t *args[WORKER_THREADS];
	int chunk_size = size / WORKER_THREADS;
	int end = 0;
	int i;
	

	/* partition the work */
	for(i = 0; i < WORKER_THREADS; i ++){
		end = i == WORKER_THREADS - 1 ? size : (i + 1) * chunk_size;
		args[i] = make_args(&array, i * chunk_size, end);
		workers[i] = malloc(sizeof(pthread_t));
		HANDLE(pthread_create(workers[i], NULL, populate_tmp_p, args[i]));
	}

	/* wait for everything to finish */
	for(i = 0; i < WORKER_THREADS; i++){
		pthread_join(*workers[i], NULL);
	}

	/* writeback, sequentially */
	unroll_tmp(&array, RANGE);

	/* free everything */
//	for(i = 0; i < WORKER_THREADS; i++){
//		free_args(args[i]);
		/* pthread_destroy(workers[i]); */
//	}

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

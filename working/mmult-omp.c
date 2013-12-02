#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "error.h"
#include "perf.h"

#define TINY 10         // 10x10
#define SMALL  100      // 100x100
#define MEDIUM 1000    // 1000x1000
#define LARGE 5000    // 5000x5000
#define YOURSIZE 100    // define your own
 

int **make_square_matrix(int n)
{
	int **ret;
	HANDLE(!(ret = malloc(sizeof(int *) * n)));
	
	for(int i = 0; i < n; i++){
		HANDLE(!(ret[i] = malloc(sizeof(int) * n)));
	}

	return ret;
}
	

void initialize_matrix(int **first, int size)
{
	NOTIFY(printf("Generating the matrix\n"));
	for (int c = 0 ; c < size ; c++ ){
		for (int  d = 0 ; d < size ; d++ ){
			first[c][d] = ((c+d) % 2) - 1;
		}
	}
}	


void multiply_matrix(int **first, int **result, int size)
{
	int sum = 0, c, d, k;
#pragma omp parallel for
	for ( c = 0 ; c < size ; c++ )
	{
#pragma omp parallel for
		for ( d = 0 ; d < size ; d++ )
		{
			sum = 0;
#pragma omp parallel for default(shared) private(k) reduction(+:sum)
			for ( k = 0 ; k < size ; k++ )
			{
				sum += first[c][k]*first[k][d];
			}
 
			result[c][d] = sum;

		}
	}
}


void verify_matrix(int **first, int **result, int size)
{
	int sum = 0, c, d, k;

	for ( c = 0 ; c < size ; c++ )
	{
		for ( d = 0 ; d < size ; d++ )
		{
			for ( k = 0 ; k < size ; k++ )
			{
				sum += first[c][k]*first[k][d];
			}
 
			assert(result[c][d] == sum);
			sum = 0;
		}
	}
}


int main()
{
	int size = LARGE;
	int **first, **result;
	monitor *m;

	first = make_square_matrix(size);
	result = make_square_matrix(size);
	initialize_matrix(first, size);

 
	m = monitor_init(SELF);
	monitor_start(m);

	multiply_matrix(first, result, size);
 
	monitor_end(m);
	monitor_print_stats(m, VERBOSE);
	monitor_free(m);

	return 0;
}

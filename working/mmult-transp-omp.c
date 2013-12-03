#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "matrix_util.h"

#define TINY 10         // 10x10
#define SMALL  100      // 100x100
#define MEDIUM 1000    // 1000x1000
#define LARGE 5000    // 5000x5000
#define YOURSIZE 100    // define your own


void multiply_matrix_transp(int *first, int *second, int *result, int size)
{
	int sum = 0, c, d, k;
#pragma omp parallel for shared(c, d, first, second)
	for ( c = 0 ; c < size ; c++ )
	{
#pragma omp parallel for
		for ( d = 0 ; d < size ; d++ )
		{
			sum = 0;
#pragma omp parallel for default(shared) private(k) reduction(+:sum)
			for ( k = 0 ; k < size ; k++ )
			{
				sum += *get_cell(first, c, k, size) * *get_cell(second, d, k, size);
			}
 
			*get_cell(result, c, d, size) = sum;

		}
	}
}

void multiply_matrix_symm_transp(int *first, int *result, int size)
{
	int sum = 0, c, d, k;
#pragma omp parallel for shared(c, d, first)
	for ( c = 0 ; c < size ; c++ )
	{
#pragma omp parallel for
		for ( d = 0 ; d < size ; d++ )
		{
			sum = 0;
#pragma omp parallel for default(shared) private(k) reduction(+:sum)
			for ( k = 0 ; k < size ; k++ )
			{
				sum += *get_cell(first, c, k, size) * *get_cell(first, d, k, size);
			}
 
			*get_cell(result, c, d, size) = sum;

		}
	}
}


int main()
{
	int size = 12;
	int *first, *result, *second, *result2;
	monitor *m;

	first = make_square_matrix(size);
	second = make_square_matrix(size);
	result = make_square_matrix(size);
	result2 = make_square_matrix(size);

	initialize_matrix(first, size);
	transpose_matrix(first, second, size);
	/* transpose_matrix(second, result, size); */

	NOTIFY(print_matrix(first, size, size));
	NOTIFY(print_matrix(second, size, size));
 
	m = monitor_init(SELF);
	monitor_start(m);

	multiply_matrix_symm_transp(first, second, result, size);
	
	/* assert(check_equal(first, result, size)); */

	monitor_end(m);
	monitor_print_stats(m, VERBOSE);
	
	multiply_matrix(first, result2, size);
	NOTIFY(print_matrix(result, size, size));
	NOTIFY(print_matrix(result2, size, size));

	/* NOTIFY(print_matrix(result, size, 10)); */
	/* we check agaisnt the multiplication with the non-transposed one to  */
	/* make sure that we didnt break anything */
	verify_matrix(first, result, size);

	
	monitor_free(m);

	return 0;
}

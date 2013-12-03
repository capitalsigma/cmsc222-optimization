#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "util.h"
#include "error.h"
#include "perf.h"
#include "matrix_util.h"


void multiply_matrix_symm_transp(int *first, int *result, int size)
{
	register int c, d, k;
	int *arow, *brow, *ans;
#pragma omp parallel for  shared(first, result, ans) private(c, d, k, arow, brow)
	for ( c = 0 ; c < size ; c++ )
	{
		for ( d = 0 ; d < size ; d++ )
		{
			arow = get_cell(first, c, 0, size);
			brow = get_cell(first, d, 0, size);
			ans = get_cell(result, c, d, size);
			for ( k = 0 ; k < size; k++ )
			{
				*ans += *(arow + k) * *(brow + k);
			}
		}
	}
}


int main()
{
	int size = SIZE;
	int *first, *result;
	monitor *m;

	first = make_square_matrix(size);
	result = make_square_matrix(size);

	initialize_matrix(first, size);

	NOTIFY(print_matrix(first, size, size));
 
	m = monitor_init(SELF);
	monitor_start(m);

	multiply_matrix_symm_transp(first, result, size);

	monitor_end(m);
	monitor_print_stats(m, VERBOSE);
	
	NOTIFY(print_matrix(result, size, size));
	NOTIFY(verify_matrix(first, result, size));
	
	monitor_free(m);

	return 0;
}

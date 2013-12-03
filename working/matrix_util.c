#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "error.h"


extern inline int *get_cell(int *m, int c, int d, int size)
{
	return m + (c * size + d);
}

int *make_square_matrix(int n)
{
	LOGGER();
	int *ret;
	HANDLE(!(ret = malloc(sizeof(int) * n * n)));
	

	return ret;
}
 
void initialize_matrix(int *first, int size)
{
	NOTIFY(printf("Generating the matrix\n"));
	for (int c = 0 ; c < size ; c++ ){
		for (int  d = 0 ; d < size ; d++ ){
			*get_cell(first, c, d, size) = ((c+d) % 5);
		}
	}
}	

void transpose_matrix(int *m, int *ret, int size)
{
	LOGGER();
	for(int c = 0; c < size; c++){
		for(int d = 0; d < size; d++){
			*get_cell(ret, d, c, size) = *get_cell(m, d, c, size);
		}
	}
}

void print_matrix(int *m, int size, int per_line){
	LOGGER();
	int counter = per_line;
	for(int c = 0; c < size; c++){
		for(int d = 0; d < size; d++){
			printf("%i, ", *get_cell(m, c, d, size));
			if(!--counter){
				printf("\n");
				counter = per_line;
			}
		}
	}
	printf("\n");
}

void verify_matrix(int *first, int *result, int size)
{
	int sum = 0, c, d, k;

	for ( c = 0 ; c < size ; c++ )
	{
		for ( d = 0 ; d < size ; d++ )
		{
			for ( k = 0 ; k < size ; k++ )
			{
				sum += *get_cell(first, c, k, size) * *get_cell(first, k, d, size);
			}
			
			/* NOTIFY(PV(*get_cell(result, c, d, size)); PV(sum)); */
			/* PV(c); PV(d); */
			assert(*get_cell(result, c, d, size) == sum);
			sum = 0;
		}
	}
}


bool check_equal(int *first, int *second, int size)
{
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(*get_cell(first, i, j, size) != *get_cell(second, i, j, size)){
				return false;
			}
		}
	}
	return true;
}
 

void multiply_matrix(int *first, int *result, int size)
{
	int sum = 0, c, d, k;
	for ( c = 0 ; c < size ; c++ )
	{
		for ( d = 0 ; d < size ; d++ )
		{
			sum = 0;
			for ( k = 0 ; k < size ; k++ )
			{
				sum += *get_cell(first, c, k, size) * *get_cell(first, k, d, size);
			}
 
			*get_cell(result, c, d, size) = sum;

		}
	}
}

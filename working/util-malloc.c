#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "util-malloc.h"

#define MAX_INT_LEN 15


void make_shift_mod_array(int *array, int size)
{
	for (int i = 0; i < size; i++){ 
		array[i] = (i << 6) % (17*17);		
	}
}

void make_array(int *array, int size, algo_t algo) 
{
	NOTIFY(printf("Generating %d integers\n", size));

	/* array of function pointers makes our life easier */
	void (*f[1]) (int *a, int s) =
		{
			make_shift_mod_array
		};
	
	f[algo](array, size);	
}


bool verify(int *array, int size)
{
	NOTIFY(printf("Verifying Sorted list in ascending order:\n"));
 
	for (int c = 0 ; c < size-1 ; c++ ) {
		if (array[c] > array[c+1]) {
			printf("Whoops: error at position %d\n", c);
			return false;
		}
	}
	NOTIFY(printf("Array correctly sorted.\n"));
	return true;
}

void print_array(int *array, int size, int line_length)
{
	char to_print[MAX_INT_LEN];
	int new_word, current_line = 0;

	for(int i = 0; i < size; i++){
		new_word = sprintf(to_print, "%i", array[i]);

		if((current_line += ++new_word) >= line_length){
			printf("\n");
			current_line = 0;
		}
		printf("%s ", to_print);
	}
	printf("\n");
}

#include <stdio.h>

#include "util.h"

void make_array(int array[], int size) 
{
	printf("Generating %d integers\n", size); 
	for (int i = 0; i < size; i++){ 
		array[i] = (i << 6) % (17*17);		
	}
}

#include <stdio.h>
#include <stdbool.h>

#include "util.h"



void make_array(int array[], int size) 
{
	printf("Generating %d integers\n", size); 
	for (int i = 0; i < size; i++){ 
		array[i] = (i << 6) % (17*17);		
	}
}

bool verify(int array[], int size)
{
  printf("Verifying Sorted list in ascending order:\n");
 
  for (int c = 0 ; c < size-1 ; c++ ) {
	  if (array[c] > array[c+1]) {
		  printf("Whoops: error at position %d\n", c);
		  return false;
	  }
  }
  return true;
}

void print_list(int array[], int size, int line_length)
{
	char* to_print;
	int new_word, current_line = 0;

	for(int i = 0; i < size; i++){
		new_word = sprintf(to_print, "%i", array[i]);

		if(current_line += ++new_word >= line_length){
			printf("\n");
			current_line = 0;
		}
		printf("%s ", to_print);
	}

}

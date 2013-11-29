#include <assert.h>
#include "testing.h"
#include "../util.h"
		
int test_shift_mod_array(int (*array)[], int size)	
{
	make_array(array, size, SHIFT_MOD);
	
	for (int i = 0; i < size; i++){
		assert((*array)[i] == (i << 6) % (17*17));
	}
	return true;
}

void test_make_array(int (*array)[], int size)
{
	make_array(array, size, SHIFT_MOD);
	ASSERT(test_shift_mod_array(array, size));
}

int main(int argc, char* argv[]) 
{
	int arr[50];

	test_make_array(&arr, 50);

	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {1, 2, 3, 5, 4};
	int arr3[] = {1, 2, 2, 3, 4};
	int arr4[] = {0, 0, 0, 0, 0};
	int arr5[] = {5, 4, 3, 2, 1};
	int arr6[] = {1, 2, 3, 5, 4};

	ASSERT(verify(&arr1, 5));
	ASSERT(verify(&arr3, 5));
	ASSERT(verify(&arr4, 5));

	ASSERT(!verify(&arr2, 5));
	ASSERT(!verify(&arr5, 5));
	ASSERT(!verify(&arr6, 5));


	print_array(&arr1, 5, 10);
	printf("Shoud read:\n1 2 3 4\n5\n");

	DONE;
	return 0;
}

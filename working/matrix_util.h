#pragma once


#define TINY 10         // 10x10
#define SMALL  100      // 100x100
#define SMALLER_MEDIUM 500
#define SMALL_MEDIUM 750
#define MEDIUM 1000    // 1000x1000
#define LARGE_MEDIUM 2000
#define LARGER_MEDIUM 3000
#define SMALL_LARGE 4000
#define LARGE 5000    // 5000x5000
#define LARGER 6000
#define XLARGE 7500
#define XXLARGE 10000

#ifdef OVERRIDE_SIZE
#define SIZE OVERRIDE_SIZE
#else
#error You need to define a size!
#endif

int *get_cell(int *m, int c, int d, int size);
int *make_square_matrix(int n); 
void initialize_matrix(int *first, int size);
void transpose_matrix(int *m, int *ret, int size);
void print_matrix(int *m, int size, int per_line);
void verify_matrix(int *first, int *result, int size);
bool check_equal(int *first, int *second, int size);
void multiply_matrix(int *first, int *result, int size);

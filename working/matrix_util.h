#pragma once

int *get_cell(int *m, int c, int d, int size);
int *make_square_matrix(int n); 
void initialize_matrix(int *first, int size);
void transpose_matrix(int *m, int *ret, int size);
void print_matrix(int *m, int size, int per_line);
void verify_matrix(int *first, int *result, int size);
bool check_equal(int *first, int *second, int size);
void multiply_matrix(int *first, int *result, int size);

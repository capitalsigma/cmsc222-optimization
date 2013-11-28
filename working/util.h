/* Utilities for making life easier -- mostly macros */
#pragma once
#include <stdbool.h>

#define MACRO_WRAP(exn) do { exn } while(0)

void make_array(int array[], int size);

bool verify(int array[], int size);

void print_list(int array[], int size, int line_length);

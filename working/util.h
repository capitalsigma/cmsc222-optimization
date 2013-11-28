/* Utilities for making life easier -- mostly macros */
#pragma once

#define MACRO_WRAP(exn) do { exn } while(0)

void make_array(int size, int array[]);

/* Utilities for making life easier */
#pragma once
#include <stdbool.h>

#define MACRO_WRAP(exp) do { exp; } while(0)

/* debugging */
#define PV(exp) MACRO_WRAP(printf(#exp": %i\n", exp))

/* logging */
#ifdef DEBUG
#define LOGGER() MACRO_WRAP(printf("Entering %s\n", __func__))
#else
#define LOGGER() MACRO_WRAP()
#endif


typedef enum {SHIFT_MOD} algo_t;

void make_array(int (*array)[], int size, algo_t algo);

bool verify(int (*array)[], int size);

void print_array(int (*array)[], int size, int line_length);

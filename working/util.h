/* Utilities for making life easier */
#pragma once
#include <stdbool.h>

#define MACRO_WRAP(exp) do { exp; } while(0)

/* debugging */
#define PV(exp) MACRO_WRAP(printf(#exp": %i\n", exp))

#ifdef VERBOSE_DEBUG
#define DEBUG
#define NOTIFY(exp) MACRO_WRAP(exp)
#else 
#define NOTIFY(exp) MACRO_WRAP()
#endif

/* logging */
#ifdef DEBUG
#define LOGGER() MACRO_WRAP(printf("Entering %s\n", __func__))
#else
#define LOGGER() MACRO_WRAP()
#endif

#define OUT_LINE_SIZE 80
#define ARRAY_ALGO SHIFT_MOD
#define RANGE 17 * 17

typedef enum {SHIFT_MOD} algo_t;


void make_array(int **array, int size, algo_t algo, int range);

bool verify(int **array, int size);

void print_array(int **array, int size, int line_length);

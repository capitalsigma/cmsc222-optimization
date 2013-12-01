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

#define VERYSMALL 1000 			/* testing purposes only */
#define SMALL 16384 			/* 2^14 */
#define MEDIUM  262144			/* 2^18 */
#define LARGE  4194304			/* 2^22 */
#define XLARGE   67108864		  /* 2^26 */

typedef enum {SHIFT_MOD} algo_t;

#define OUT_LINE_SIZE 80
#define ARRAY_ALGO SHIFT_MOD

#define ARRAY_SIZE 0

/* now we can compile bsort-small, bsort-large, etc by passing arguments */
/* to gcc */
/* #ifdef SMALL_SIZE */
/* #define ARRAY_SIZE SMALL */
/* #endif */
/* #ifdef MEDIUM_SIZE */
/* #define ARRAY_SIZE MEDIUM */
/* #endif */
/* #ifdef LARGE_SIZE  */
/* #define ARRAY_SIZE LARGE */
/* #endif */
/* #ifdef XLARGE_SIZE  */
/* #define ARRAY_SIZE XLARGE */
/* #endif */

/* #if !ARRAY_SIZE */
/* #error You need to pass an array size to the compiler */
/* #endif */


void make_array(int **array, int size, algo_t algo);

bool verify(int **array, int size);

void print_array(int **array, int size, int line_length);

#pragma once

#include <stdbool.h>
/* #include <semaphore.h> */

/* typedef struct { */
/* 	sem_t mutex; */
/* 	int val; */
/* } atomic_int; */

typedef struct atomic_int atomic_int;

atomic_int *initialize_atomic_int(int val);
void free_atomic_int(atomic_int *ai);
int atomic_increment(atomic_int *ai, bool ispre);
int atomic_getval(atomic_int *ai);
int nonatomic_getval(atomic_int *ai);
int nonatomic_decrement(atomic_int *ai, bool ispre);

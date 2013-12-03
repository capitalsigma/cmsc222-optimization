# CHK_SOURCES=bsort.c $(DEPS) $(DEPS_HEADERS)
DEPS=util.c perf.c
M_DEPS = util.c perf.c matrix_util.c
PAR_DEPS = util.c perf.c worker_pool.c atomic_int.c
MALLOC_DEPS=util-malloc.c perf.c
# DEPS_HEADERS=worker_pool.h util.h perf.h
CFLAGS=-ggdb -pthread -Wall -O3 -std=c11
CC=gcc 

size_macro = $(lastword $(subst -, ,$(1)))_SIZE

check-syntax:
	$(CC) -o nul.out  $(CFLAGS) -fopenmp -S $(CHK_SOURCES)

mmult-seq:
	$(CC) -o $@-$(1).out $(CFLAGS) -fopenmp -DOVERRIDE_SIZE=$1  $@.c $(DEPS) 

mmult-sym-omp:
	$(CC) -o $@-$(1).out $(CFLAGS) -fopenmp -DOVERRIDE_SIZE=$1  $@.c $(M_DEPS) 

mmult-%:
	$(CC) -o $@-$(1)-$(3).out $(CFLAGS) -fopenmp -D$(1)_SIZE  $@.c $(M_DEPS) 

%-omp:
	$(CC) -o $@-$(1)-$(3).out $(CFLAGS) -fopenmp -D$(1)_SIZE  $@.c $(PAR_DEPS)

%-seq:
	$(CC) -o $@-$(1).out $@.c $(DEPS) $(CFLAGS) -D$(1)_SIZE 

%-par:
	$(CC) -o $@-$(1)-$(2).out $(CFLAGS) -D$(1)_SIZE -DWORKER_THREADS=$(2) $@.c $(PAR_DEPS) 

# mergesort-% : 
# 	$(CC) -o $@-$(1).out $@.c $(DEPS) $(CFLAGS) -D$(1)_SIZE 

# bsort-% : 
# 	$(CC) -o $@-$(1).out $@.c $(DEPS) $(CFLAGS) -D$(1)_SIZE

# bsort-global-% : bsort-global.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-global-,,$@_SIZE)

# bsort-malloc-% : bsort-malloc.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-malloc-,,$@_SIZE) 

# bsort-% : bsort.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-,,$@_SIZE)


.PHONY: clean

clean: 
	rm *.out

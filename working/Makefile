# CHK_SOURCES=bsort.c $(DEPS) $(DEPS_HEADERS)
DEPS=util.c perf.c
PAR_DEPS = util.c perf.c worker_pool.c
MALLOC_DEPS=util-malloc.c perf.c
# DEPS_HEADERS=worker_pool.h util.h perf.h
CFLAGS=-ggdb -std=c11 -pthread -Wall -O3
CC=gcc 

size_macro = $(lastword $(subst -, ,$(1)))_SIZE

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

%-par:
	$(CC) -o $@-$(1).out $@.c $(PAR_DEPS) $(CFLAGS) -D$(1)_SIZE 

mergesort-% : 
	$(CC) -o $@-$(1).out $@.c $(DEPS) $(CFLAGS) -D$(1)_SIZE 

bsort-% : 
	$(CC) -o $@-$(1).out $@.c $(DEPS) $(CFLAGS) -D$(1)_SIZE

# bsort-global-% : bsort-global.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-global-,,$@_SIZE)

# bsort-malloc-% : bsort-malloc.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-malloc-,,$@_SIZE) 

# bsort-% : bsort.c $(DEPS) $(DEPS_HEADERS)
# 	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-,,$@_SIZE)


.PHONY: clean

clean: 
	rm *.out

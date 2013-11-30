CHK_SOURCES=bsort.c $(DEPS) $(DEPS_HEADERS)
DEPS=worker_pool.c util.c perf.c
DEPS_HEADERS=worker_pool.h util.h perf.h
CFLAGS=-ggdb -std=c11 -pthread -Wall
DEBUG_FLAGS =
CC=gcc 

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

bsort-% : bsort.c $(DEPS) $(DEPS_HEADERS)
	$(CC) -o $@.out $< $(DEPS) $(CFLAGS) -D$(subst bsort-,,$@_SIZE)


.PHONY: clean

clean: 
	rm *.out

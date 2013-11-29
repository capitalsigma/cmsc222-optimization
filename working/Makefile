CHK_SOURCES=bsort.c  $(DEPS) $(DEPS_HEADERS)
DEPS=worker_pool.c util.c
DEPS_HEADERS=worker_pool.h util.h
CFLAGS=-std=c11 -pthread -Wall
CC=gcc 

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

worker_pool bsort : $(DEPS) $(DEPS_HEADERS)
	$(CC) -o $@.out $@.c $(DEPS) $(CFLAGS) -ggdb

.PHONY: clean

clean: 
	rm *.out

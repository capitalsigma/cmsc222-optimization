CHK_SOURCES:=$(wildcard *.c)
#SRCS=../worker_pool.c ../util.c
SRCS=$(wildcard ../*.c)
#HEADERS= ../worker_pool.h ../util.h 
HEADERS:=$(wildcard ../*.h)
CFLAGS=-std=c99 -pthread
CC=gcc 

check-syntax:
	$(CC) $(CHK_SOURCES) $(CFLAGS) -fsyntax-only 

# check_worker_pool: check_worker_pool.c  $(DEPS)
# 	$(CC) -o $@ $@.c $(DEPS)  $(CFLAGS) -ggdb

monitor util perf worker_pool : $(SRCS) $(HEADERS)
	$(CC) -o $@_tests.out $@_tests.c ../$@.c $(CFLAGS)

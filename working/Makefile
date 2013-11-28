CHK_SOURCES=worker_pool.c 
CFLAGS=-std=c99 -pthread
CC=gcc 

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

worker_pool: worker_pool.c worker_pool.h
	$(CC) -o $@.out $@.c $(CFLAGS) -ggdb

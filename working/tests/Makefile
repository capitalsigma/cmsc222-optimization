CHK_SOURCES=worker_pool_tests.c
SRCS=../worker_pool.c ../util.c
HEADERS= ../worker_pool.h ../util.h 
CFLAGS=-std=c99 -pthread
CC=gcc 

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

# check_worker_pool: check_worker_pool.c  $(DEPS)
# 	$(CC) -o $@ $@.c $(DEPS)  $(CFLAGS) -ggdb


% : %.c $(SRCS) $(HEADERS)
	$(CC) -o $@.out $@.c $(SRCS) $(CFLAGS)

CHK_SOURCES=worker_pool_tests.c
DEPS=../worker_pool.c ../worker_pool.h
CFLAGS=-std=c99 -pthread
CC=gcc 

check-syntax:
	$(CC) -o nul.out -S $(CHK_SOURCES) $(CFLAGS)

# check_worker_pool: check_worker_pool.c  $(DEPS)
# 	$(CC) -o $@ $@.c $(DEPS)  $(CFLAGS) -ggdb


worker_pool_tests: worker_pool_tests.c $(DEPS)
	$(CC) -o $@.out $@.c $(DEPS) $(CFLAGS)

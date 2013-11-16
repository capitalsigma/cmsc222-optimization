CHK_SOURCES= worker_pool.c worker_pool.h

check-syntax:
	gcc -o nul -S $(CHK_SOURCES)

worker_pool: $@.c $@.h
	gcc -o $@ $@.c -ggdb

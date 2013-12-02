#pragma once
#include <stdbool.h>

/* opaque struct */
typedef struct worker_pool worker_pool;

worker_pool* initialize_pool(int pool_size);

void free_pool(worker_pool *pool);

bool request_worker(worker_pool *pool);

void return_worker(worker_pool *pool, pthread_t *thread);



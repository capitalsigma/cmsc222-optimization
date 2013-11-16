#ifdef WORKER_POOL_H
#def WORKER_POOL_H


worker_pool* initialize_pool(int pool_size);

bool request_worker(worker_pool *pool);

void return_worker(worker_pool *pool);



#endif

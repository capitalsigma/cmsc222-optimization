#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


#include "worker_pool.h"
#include "error.h"
#include "util.h"


/* note: add in error handling later in life */

struct worker_pool {
	sem_t mutex;
	int count;
};

worker_pool* initialize_pool(int pool_size) 
{
	/* add error handling */
	worker_pool *ret;
	HANDLE(!(ret = malloc(sizeof(worker_pool))));
	
	/* need to check this return value */
	/* initialize the lock with a value of 1 as local to the process */
	sem_init(&ret->mutex, 0, 1);
	ret->count = pool_size;

	return ret;
}

void free_pool(worker_pool *pool)
{
	HANDLE(sem_destroy(&pool->mutex));
	
	free(pool);
}
	


bool request_worker(worker_pool *pool)
{
	assert(pool);

	bool ret = false;

	/* acquire a lock so we can safely check the number of free workers */
	sem_wait(&pool->mutex);
	
	
	if(pool->count){
		pool->count--;
		ret = true;
	}
	
	/* the check is done, release the lock */
	sem_post(&pool->mutex);
	
	return ret;
}




void return_worker(worker_pool *pool, pthread_t *thread)
{
	assert(pool);
	assert(thread);


	HANDLE(pthread_join(*thread, NULL));

	sem_wait(&pool->mutex);
	pool->count++;
	sem_post(&pool->mutex);
	
	free(thread);
}


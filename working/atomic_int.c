#include <stdlib.h>
#include <semaphore.h>

#include "error.h"
#include "atomic_int.h"


struct atomic_int {
	sem_t mutex;
	int val; 
} ;


atomic_int *initialize_atomic_int(int val)
{
	atomic_int *ret = malloc(sizeof(atomic_int));
	
	ret->val = val;
	HANDLE(sem_init(&ret->mutex, 0, 1) == -1);
 
	return ret;
}


void free_atomic_int(atomic_int *ai)
{
	HANDLE(sem_destroy(&ai->mutex));
	free(ai);
}

int atomic_increment(atomic_int *ai, bool ispre)
{
	int ret;
	sem_wait(&ai->mutex);
	if(ispre){
		ret = ++ai->val;
	} else {
		ret = ai->val++;
	}
	sem_post(&ai->mutex);

	return ret;
}

int atomic_getval(atomic_int *ai)
{
	int ret;
	sem_wait(&ai->mutex);
	ret = ai->val;
	sem_post(&ai->mutex);
	return ret;
}

int nonatomic_getval(atomic_int *ai)
{
	return ai->val;
}

int nonatomic_decrement(atomic_int *ai, bool ispre)
{
	if(ispre){
		return --ai->val;
	} else {
		return ai->val--;
	}
}

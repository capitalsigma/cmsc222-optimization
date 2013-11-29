#include <stdlib.h>
#include "testing.h"
#include "../worker_pool.h"

void test_worker_pool(void)
{
	worker_pool *pool;
	ASSERT(pool = initialize_pool(5));

	for(int i = 0; i < 5; i++){
		ASSERT(request_worker(pool));
	}

	ASSERT(!request_worker(pool));

	for(int i = 0; i < 2; i++){
		return_worker(pool);
	}

	for(int i = 0; i < 2; i++){
		ASSERT(request_worker(pool));
	}

}


int main(void)
{
	test_worker_pool();
}

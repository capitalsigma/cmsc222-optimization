#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../worker_pool.h"
#define ASSERT(exn) assert(exn); printf("%s (%i): PASS\n", #exn, __LINE__)


/* tests are all macros */
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

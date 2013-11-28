#include <check.h> 
#include <stdlib.h>
#include <stdio.h>
#include "../worker_pool.h"

/* tests are all macros */
START_TEST (test_worker_pool)
{
	worker_pool *pool;
	chk_assert(pool = initialize_pool(5));

	for(int i = 0; i < 5; i++){
		chk_assert(request_worker(pool));
	}

	chk_assert(!request_worker(pool));

	for(int i = 0; i < 2; i++){
		return_worker(pool);
	}

	for(int i = 0; i < 2; i++){
		chk_assert(request_worker(pool));
	}

}
END_TEST	
	
Suite *worker_pool_suite(void)
{
	Suite *s = suite_create("worker_pool");
	
	/* test cases */
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_worker_pool);
	suite_add_tcase(s, tc_core);
	   
	return s;
}

int main(void)
{
	int failed;

	Suite *s = worker_pool_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return failed ? EXIT_FAILURE : EXIT_SUCCESS;

}

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "../perf.h"
#include "testing.h"


void busy_loop()
{
	/* do some stuff to not get optimized away */
	for(int i = 0; i < 2000000; i++){
		if(i == rand()) {
			break;
		}
	}
}

void *busy(void *no_args)
{
	busy_loop();
	pthread_exit(NULL);
}

void busy_threads()
{
	pthread_t a, b, c;

	pthread_create(&a, NULL, busy, NULL);
	pthread_create(&b, NULL, busy, NULL);
	pthread_create(&c, NULL, busy, NULL);
	
	pthread_join(a, NULL);
	pthread_join(b, NULL);
	pthread_join(c, NULL);
}

void test_monitor(monitor_target who, bool all_verbosities, bool threaded)
{
	monitor *m = monitor_init(who);

	monitor_start(m);

	if(threaded){
		busy_threads();
	} else {
		busy_loop();
	}

	monitor_end(m);

	if(all_verbosities){
		monitor_print_stats(m, 0);
		SMALL_SEP();
		monitor_print_stats(m, 1);
		SMALL_SEP();
	}

	monitor_print_stats(m, 2);
	
	monitor_free(m);
}

/* we can't test precise outputs here, so we'll just run a small test */
/* for each of the different `who` values and make sure nothing segfaults */
int main(int argc, char* argv[])
{
	test_monitor(SELF, true, false);
	BIG_SEP();
	test_monitor(SELF, true, true);
	BIG_SEP();
	test_monitor(CHILDREN, false, true); /* should be 0 */
	BIG_SEP();
	test_monitor(THREAD, false, true);
	
	BIG_SEP();
	DONE();
	return 0;
}

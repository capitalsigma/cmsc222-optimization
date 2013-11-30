#pragma once

/* we need to include these here so that the values of 'who' */
/* will be defined by files that include this one */
/* #include <sys/time.h> */
/* #include <sys/resource.h> */


/* opaque struct */
typedef struct _monitor monitor;

typedef enum {SELF, CHILDREN, THREAD} monitor_target;
typedef enum {SILENT = 0, QUIET, VERBOSE} verbosity;

/* note that valid values of who are... */
/*   RUSAGE_SELF, */
/*   RUSAGE_CHILDREN, */
/*   and RUSAGE_THREAD */

monitor *monitor_init(monitor_target who);
void monitor_start(monitor *m);
void monitor_end(monitor *m);
void monitor_free(monitor *m);
void monitor_print_stats(monitor *m, verbosity v);

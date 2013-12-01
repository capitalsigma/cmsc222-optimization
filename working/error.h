#include <errno.h>

#include "util.h"

/* TODO: get this to print line numbers */
#ifdef VERBOSE_DEBUG
#define HANDLE(exp) MACRO_WRAP(if(exp || 1) perror(#exp);)
#else
#define HANDLE(exp) MACRO_WRAP(if(exp) perror(#exp);)
#endif

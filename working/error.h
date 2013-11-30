#include <errno.h>

#include "util.h"

/* TODO: get this to print line numbers */
#define HANDLE(exp) MACRO_WRAP(if(exp) perror(#exp);)

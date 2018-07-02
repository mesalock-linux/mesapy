#include "common_header.h"
#include <src/support.h>
#include <src/exception.h>

/************************************************************/
/***  C header subsection: support functions              ***/

#include <stdio.h>
#include <stdlib.h>

/*** misc ***/

RPY_EXTERN
void RPyAssertFailed(const char* filename, long lineno,
                     const char* function, const char *msg) {
  abort();
}

RPY_EXTERN
void RPyAbort(void) {
  abort();
}

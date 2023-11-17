#ifndef SOURCE_H
#define SOURCE_H

#include "util.h"

/* Interpret any command line arguments to get the source. */
char* source_get(char* arg);
/* Get the source from stdin. */
char* source_get_from_stdin();
/* Get the source from a file path. */
char* source_get_from_fpath(char* path);

#endif

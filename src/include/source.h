#ifndef SOURCE_H
#define SOURCE_H

#include "util.h"

char* source_get(char* arg);
char* source_get_from_stdin();
char* source_get_from_fpath(char* path);

#endif

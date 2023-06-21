#ifndef SOURCE_H
#define SOURCE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* source_get(char* arg);
char* source_get_from_stdin();
char* source_get_from_fpath(char* path);

#endif

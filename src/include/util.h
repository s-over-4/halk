#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/* log some debug information */
void log_dbg(const char*, ...);
/* log some information */
void log_inf(const char*, ...);
/* log something with no formatting */
void log_raw(const char*, ...);
/* log a warning */
void log_war(const char*, ...);
/* log an error */
void log_err(const char*, ...);
/* die and leave message */
void die(const char*, ...);

/* if calloc() returns null, die */
void* ecalloc(size_t, size_t);
/* if malloc() returns null, die */
void* emalloc(size_t);
/* if realloc() returns null, die */
void* erealloc(void*, size_t);

#endif

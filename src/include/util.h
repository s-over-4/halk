#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/* Log some debug information. */
void log_dbg(const char*, ...);
/* Log some congratulatory information. */
void log_yay(const char*, ...);
/* Log some information. */
void log_inf(const char*, ...);
/* Log something with no formatting. */
void log_raw(const char*, ...);
/* Log a warning. */
void log_war(const char*, ...);
/* Log an error. */
void log_err(const char*, ...);
/* Die and leave message. */
void die(const char*, ...);

/* If `calloc()` returns null, die. */
void* ecalloc(size_t, size_t);
/* If `malloc()` returns null, die. */
void* emalloc(size_t);
/* If `realloc()` returns null, die. */
void* erealloc(void*, size_t);

#endif

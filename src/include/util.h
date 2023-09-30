#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* die and leave message */
void die(const char*, ...);
/* log an error */
void log_err(const char*, ...);
/* log some information */
void log_inf(const char*, ...);
/* log something with no formatting */
void log_raw(const char*, ...);
/* log a warning */
void log_war(const char*, ...);

/* does c appear in s? */
int appears_in_str(char*, char*);

#endif

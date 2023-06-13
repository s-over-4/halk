#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void die(const char* fmt, ...);
void log_inf(const char* fmt, ...);
void log_raw(const char* fmt, ...);
void log_war(const char* fmt, ...);

#endif

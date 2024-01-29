#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/* Welcome to macro hell. */

#define HIDE(x) do {x} while (0)

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

/* Log some file info (mostly for use in other LOG_* macros.) */
#define LOG_FINF HIDE( \
   fprintf(stderr, "%s:%s:%d: ", __FILE__, __func__, __LINE__); \
)

/* Log some debug information. */
void log_dbg(const char*, ...);
#define LOG_DBG(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[95;1m==\x1b[0m\x1b[37m]\x1b[0m\x1b[35m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* c: */
void log_yay(const char*, ...);
#define LOG_YAY(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[92;1m==\x1b[0m\x1b[37m]\x1b[32m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log some information. */
void log_inf(const char*, ...);
#define LOG_INF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[94;1m==\x1b[0m\x1b[37m]\x1b[0m "); \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log something with no formatting. */
void log_raw(const char*, ...);
#define LOG_RAW(fmt, ...) HIDE( \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
)

/* Log a warning. */
void log_war(const char*, ...);
#define LOG_WAR(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[93;1m==\x1b[0m\x1b[37m]\x1b[93;1m WARNING:\x1b[0m\x1b[33m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log an error. */
void log_err(const char*, ...);
#define LOG_ERR(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m ERROR:\x1b[0m\x1b[31m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Warn of soon™-to-be-removed functions. */
#define WFDEPRECATED LOG_WAR("Use of this function is deprecated.")

/* Die and leave message. */
void die(const char*, ...);
#define DIE(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m CAUSE OF DEATH:\x1b[0m\x1b[31m "); \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m Exiting...\x1b[0m\n"); \
   exit(1); \
)

/* If `calloc()` returns null, die. */
void* ecalloc(size_t, size_t);
/* If `malloc()` returns null, die. */
void* emalloc(size_t);
/* If `realloc()` returns null, die. */
void* erealloc(void*, size_t);

#endif

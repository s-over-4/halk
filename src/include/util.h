#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/* Welcome to macro Hell. */

#define HIDE(x) do {x} while (0)

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

/* Log some file info (mostly for use in other LOG_* macros.) */
#define LOG_FINF HIDE( \
   fprintf(stderr, "%s:%s:%d: ", __FILE__, __func__, __LINE__); \
)

/* Call `f` on `x` if `x` exists. */
#define EDO(f, x) HIDE(if (x) {f(x);})

#ifdef DBG

/* Log some debug information. */
#define LOG_DBGF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[95;1m==\x1b[0m\x1b[37m]\x1b[0m\x1b[35m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#define LOG_DBG(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[95;1m==\x1b[0m\x1b[37m]\x1b[0m\x1b[35m "); \
   LOG_FINF; \
   fprintf(stderr, body); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#else    // ifdef DBG

#define LOG_DBGF(fmt, ...);
#define LOG_DBG(body);

#endif   // ifdef DBG

/* c: */
#define LOG_YAYF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[92;1m==\x1b[0m\x1b[37m]\x1b[32m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#define LOG_YAY(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[92;1m==\x1b[0m\x1b[37m]\x1b[32m "); \
   LOG_FINF; \
   fprintf(stderr, body); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log some information. */
#define LOG_INFF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[94;1m==\x1b[0m\x1b[37m]\x1b[0m "); \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#define LOG_INF(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[94;1m==\x1b[0m\x1b[37m]\x1b[0m "); \
   fprintf(stderr, body); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log something with no formatting. */
#define LOG_RAWF(fmt, ...) HIDE( \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
)

#define LOG_RAW(body) HIDE( \
   fprintf(stderr, body); \
)

/* Log a warning. */
#define LOG_WARF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[93;1m==\x1b[0m\x1b[37m]\x1b[93;1m WARNING:\x1b[0m\x1b[33m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#define LOG_WAR(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[93;1m==\x1b[0m\x1b[37m]\x1b[93;1m WARNING:\x1b[0m\x1b[33m "); \
   LOG_FINF; \
   fprintf(stderr, body); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Log an error. */
#define LOG_ERRF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m ERROR:\x1b[0m\x1b[31m "); \
   LOG_FINF; \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
)

#define LOG_ERR(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m ERROR:\x1b[0m\x1b[31m "); \
   LOG_FINF; \
   fprintf(stderr, body); \
   fprintf(stderr, "\x1b[0m\n"); \
)

/* Die and leave message. */
void die(const char*, ...);
#define DIEF(fmt, ...) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m CAUSE OF DEATH:\x1b[0m\x1b[31m "); \
   fprintf(stderr, fmt, ##__VA_ARGS__); \
   fprintf(stderr, "\x1b[0m\n"); \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m Exiting...\x1b[0m\n"); \
   exit(1); \
)

#define DIE(body) HIDE( \
   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m CAUSE OF DEATH:\x1b[0m\x1b[31m "); \
   fprintf(stderr, body); \
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

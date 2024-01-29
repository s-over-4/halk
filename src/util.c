#include "include/util.h"

void log_dbg(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stdout, "");
   fprintf(stderr, "\x1b[37m[\x1b[95;1m==\x1b[0m\x1b[37m]\x1b[0m\x1b[35m ");

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);

   fprintf(stdout, "\e[0m\n");
}

void log_yay(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stdout, "\x1b[37m[\x1b[92;1m==\x1b[0m\x1b[37m]\x1b[32m ");

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);

   fprintf(stdout, "\x1b[0m\n");
}

void log_inf(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stderr, "\x1b[37m[\x1b[94;1m==\x1b[0m\x1b[37m]\x1b[0m ");

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);

   fprintf(stdout, "\n");
}

void log_raw(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);
}

void log_war(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stderr, "\x1b[37m[\x1b[93;1m==\x1b[0m\x1b[37m]\x1b[93;1m WARNING:\x1b[0m\x1b[33m ");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

void log_err(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m ERROR:\x1b[0m\x1b[31m ");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\x1b[0m\n");
}

void die(const char* fmt, ...) {
   WFDEPRECATED;
   va_list ap;

   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m CAUSE OF DEATH:\x1b[0m\x1b[31m ");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);
   fprintf(stderr, "\x1b[0m\n");

   fprintf(stderr, "\x1b[37m[\x1b[91;1m==\x1b[0m\x1b[37m]\x1b[91;1m Exiting...\x1b[0m\n");

   exit(1);
}

void* ecalloc(size_t nmemb, size_t size) {
   void* p;

   if (! (p = calloc(nmemb, size))) { die("failed to calloc:"); }

   return p;
}

void* emalloc(size_t size) {
   void* p;

   if (! (p = malloc(size))) { die("failed to malloc:"); }

   return p;
}

void* erealloc(void* dest, size_t size) {
   void* p;

   if (! (p = realloc(dest, size))) { die("failed to realloc:"); }

   return p;
}

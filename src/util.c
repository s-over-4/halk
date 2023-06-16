#include "include/util.h"

void die(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "[\e[31m==\e[0m] ERROR ");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);
   fprintf(stderr, "\n");

   exit(1);
}

void log_inf(const char* fmt, ...) {
   va_list ap;

   fprintf(stdout, "[\e[34m==\e[0m] ");

   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);

   fprintf(stdout, "\n");
}

void log_raw(const char* fmt, ...) {
   va_list ap;
   va_start(ap, fmt);
   vfprintf(stdout, fmt, ap);
   va_end(ap);
}

void log_war(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "[\e[33m==\e[0m] WARNING");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

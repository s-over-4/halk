#include "include/util.h"

void die(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "== ERROR ==\n");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
      fputc(' ', stderr);
      perror(NULL);
   } else {
      fputc('\n', stderr);
   }

   fprintf(stderr, "\n");

   exit(1);
}

void log_inf(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "== ");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

void log_raw(const char* fmt, ...) {
   va_list ap;

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   fprintf(stderr, "\n");
}

void log_war(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "== WARNING ==\n");

   va_start(ap, fmt);
   vfprintf(stderr, fmt, ap);
   va_end(ap);

   if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
      fputc(' ', stderr);
      perror(NULL);
   } else {
      fputc('\n', stderr);
   }

   fprintf(stderr, "\n");
}

#include "include/util.h"

void die(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "== FATAL ERROR ==\n");

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

   fprintf(stderr, "== INFO ==\n");

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

void log_err(const char* fmt, ...) {
   va_list ap;

   fprintf(stderr, "== ERROR ==");

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

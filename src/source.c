#include "include/source.h"
#include "include/util.h"
#include <stdio.h>

char* source_get(char* arg) {
   return arg? 
      source_get_from_fpath(arg):
      source_get_from_stdin();
}

char* source_get_from_fpath(char* path) {
   FILE* f;
   long f_size;
   char* src;

   f = fopen(path, "rb");
   if (!f) { die("source file not found: %s", path); }

   fseek(f, 0L, SEEK_END);
   f_size = ftell(f);
   rewind(f);

   src = ecalloc(1, f_size + 1);

   if ((fread(src, f_size, 1, f) != 1) || !src) {
      fclose(f);
      free(src);
      die("could not read source file: %s", path);
   }

   return src;
}

char* source_get_from_stdin() {
   char* src;

   src = ecalloc(256, sizeof(char));

   src = fgets(src, 256, stdin);

   return src;
}

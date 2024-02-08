#include "include/source.h"

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
   if (!f) { DIEF("source file not found: %s", path); }

   fseek(f, 0L, SEEK_END);
   f_size = ftell(f);
   rewind(f);

   src = ecalloc(1, f_size + 1);

   if ((fread(src, f_size, 1, f) != 1) || !src) {
      fclose(f);
      free(src);
      DIEF("could not read source file: %s", path);
   }

   return src;
}

char* source_get_from_stdin() {
   char* s;
   char* src;
   size_t l;

#if 0
      l = 0;

      src = ecalloc(16, sizeof(char));

      while ((s = fgets(src + l, 20, stdin))) {
         l = MIN(15, l + strlen(src + l));
      }

      /* This works, I guess. */
      s && src[l - 1] == '\n' && (src[l - 1] = '\0');
#endif

   src = ecalloc(256, sizeof(char));
   fgets(src, 256, stdin);

   return src; 
}

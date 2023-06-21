#include "include/source.h"
#include "include/util.h"
#include <stdio.h>

char* source_get(char* arg) {
   return arg? 
      source_get_from_fpath(arg):
      source_get_from_stdin();

}

char* source_get_from_fpath(char* path) {
   FILE* f;       // the file to read from
   long f_size;   // the size of the file
   char* src;     // the source code to return

   f = fopen(path, "rb");
   if (!f) { die("source file not found: %s", path); }

   fseek(f, 0L, SEEK_END);
   f_size = ftell(f);
   rewind(f);

   src = calloc(1, f_size + 1);

   if ((fread(src, f_size, 1, f) != 1) || !src) {
      fclose(f);
      free(src);
      die("could not read source file: %s", path);
   }

   return src;
}

char* source_get_from_stdin() {
   size_t len; // the length of the given source
   char* src;  // the source code to return

   len = 0;
   src = calloc(len, sizeof(char));

   printf("> ");

   while (src[len - 1] != EOF) {
      char c;  // the character being read

      if (src[len - 1] == '\n') { printf("> "); }

      c = getchar();
      src = realloc(src, (len + sizeof(char)));
      memcpy(src + len, &c, sizeof(char));
      len += sizeof(char);
   }

   src[len - 1] = '\0'; // null terminate

   putchar('\n');

   return src;
}

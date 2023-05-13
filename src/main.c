#include <stdio.h>


#include "include/lexer.h"
#include "include/tree.h"


int main(int argc, char* argv[]) {
   FILE *fsource;
   long fsource_size;
   char *source;

   fsource = fopen ("examples/hello.halk", "rb");
   if (!fsource) { 
      fputs("Source file not found.", stderr); 
      exit(1); 
   };

   fseek(fsource, 0L, SEEK_END);
   fsource_size = ftell(fsource);
   rewind(fsource);

   source = calloc(1, fsource_size + 1);

   if (!source) { 
      fclose(fsource); 
      fputs("Memory allocation failed.", stderr);
      exit(1); 
   }

   if (1 != fread(source, fsource_size, 1, fsource)) {
      fclose(fsource); 
      free(source);
      fputs("Could not read source file.", stderr); 
      exit(1);
   }

   fclose(fsource);

   lexer_t* lexer = lexer_init( source );

   printf("\n=== INPUT =======\n%s\n=== END INPUT ===\n", lexer->content);

   token_t* token = NULL;

   while ((token = lexer_get_next_token(lexer)) != NULL) {
      printf("===\ntoken type: %d\ntoken value: %s\n===\n", token->type, token->value);
   }

   lexer_destroy(lexer);

   return 0;
}

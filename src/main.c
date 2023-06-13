#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"


int main(int argc, char* argv[]) {
   FILE* fsource;
   long fsource_size;
   char* source;

   fsource = fopen(argv[1], "rb");
   if (!fsource) { 
      die("source file not found");
   };

   fseek(fsource, 0L, SEEK_END);
   fsource_size = ftell(fsource);
   rewind(fsource);

   source = calloc(1, fsource_size + 1);

   if (!source) { 
      fclose(fsource); 
      die("calloc failed");
   }

   if (1 != fread(source, fsource_size, 1, fsource)) {
      fclose(fsource); 
      free(source);
      die("could not read source");
   }

   log_inf("source file loaded");

   lexer_t* lexer = lexer_init(source);
   log_inf("lexer created");

   log_inf("BEGIN INPUT");
   log_raw(lexer->content);
   log_inf("END INPUT");

   token_t* token = NULL;

   while ((token = lexer_get_next_token(lexer)) != NULL) {
      log_inf("token type: [%s]\ttoken value: [%s]", token_get_type(token->type), token->value);
      free(token);
   }

   fclose(fsource);
   free(source);

   log_inf("source file closed");

   return 0;
}

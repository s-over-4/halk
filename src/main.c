#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"

int main(int argc, char* argv[]) {
   FILE*    fsource;
   long     fsource_size;
   char*    source;
   lexer_t* lexer;
   int      in_file;


   fsource = fopen(argv[1], "rb");
   if (!fsource)                                      { free(fsource); die("source file not found"); };
   fseek(fsource, 0L, SEEK_END);
   fsource_size = ftell(fsource);
   rewind(fsource);
   source = calloc(1, fsource_size + 1);
   if (!source)                                       { fclose(fsource); free(source); die("calloc failed"); }
   if (1 != fread(source, fsource_size, 1, fsource))  { fclose(fsource); free(source); die("could not read source"); }
   log_inf("source file loaded");

   lexer = lexer_init(source);
   log_inf("lexer created");

   log_inf("BEGIN INPUT");
   log_raw(lexer->content);
   log_inf("END INPUT");

   in_file = 1;

   while (in_file) {
      token_t* token;
      char* type;

      token = lexer_get_next_token(lexer);
      type = token_get_type(token->type);
      
      log_inf("token type: [%s]\t\ttoken value: [%s]", type, token->value);
      (token->type == TOKEN_EOF) && (in_file = 0);

      token_destroy(token);
   }

   // clean up
   lexer_destroy(lexer);
   fclose(fsource);
   free(source);

   log_inf("source file closed");

   return 0;
}

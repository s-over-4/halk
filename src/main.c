#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/source.h"
#include "include/hlkt.h"

int main(int argc, char* argv[]) {
   char*    source;
   lexer_t* lexer;
   int      in_file;

   source = source_get(argv[1]); 

   lexer = lexer_init(source);
   HLKT_ASS(lexer);
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
   free(source);

   HLKT_LOG();

   return 0;
}

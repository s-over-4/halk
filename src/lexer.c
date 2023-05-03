#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>

lexer_T* lexer_init(char* content) {
   lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUC));

   lexer->content = content;
   lexer->i = 0;
   lexer->c = content[lexer->i];

   return lexer;
}

void lexer_next(lexer_T* lexer) {
   // if not at end of line or file
   if (lexer->c != '\0' && lexer->i < strlen(lexer->content)) {
      lexer->i += 1;                                  // advance index 1 character
      lexer->c = lexer->content[lexer->i];            // set character w/ index
   }
}

void lexer_pass(lexer_T* lexer) {
   while (lexer->c == ' ' ||
         lexer->c == '\t' ||
         lexer->c == '\n') {
      lexer_next(lexer);
   }
}

token_T* lexer_get_next_token(lexer_T* lexer) {
   while (lexer->c != '\0' && lexer->i < strlen(lexer->content)) {
      if (lexer->c == ' ' ||
            lexer->c == '\t' ||
            lexer->c == '\n') {

      }
   }
}

token_T* lexer_get_string(lexer_T* lexer) {

}
token_T* lexer_get_id(lexer_T* lexer) {

}
token_T* lexer_next_token(lexer_T* lexer, token_T* token) {

}
char* lexer_get_c_as_string(lexer_T* lexer) {

}

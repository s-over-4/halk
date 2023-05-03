#include "include/lexer.h"
#include "include/token.h"
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
        lexer_pass(lexer); 
      }

      switch (lexer->c) {
         case '"': return lexer_get_string(lexer); break;
         case '=': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_EQ,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '/': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_LORD,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '\\': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_RORD,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '&': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_AMP,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '[': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_LBRAK,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case ']': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_RBRAK,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '#': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_POUND,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
         case '~': return lexer_next_token(
                         lexer,
                         token_init(
                            TOKEN_TILDE,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
      }
   }

   return token_init(TOKEN_EOF, "\0");
}

token_T* lexer_get_string(lexer_T* lexer) {
  // while c not ", add c to token value 
}

token_T* lexer_get_id(lexer_T* lexer) {
   // 
}

token_T* lexer_next_token(lexer_T* lexer, token_T* token) {
   lexer_next(lexer);

   return token;

}

char* lexer_get_c_as_string(lexer_T* lexer) {
   char* str = calloc(1, sizeof(char));
   str[0] = lexer->c;
   str[1] = '\0';

   return str;
}

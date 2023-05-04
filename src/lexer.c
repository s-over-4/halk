#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_t* lexer_init(char* content) {
   lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUC));

   lexer->content = content;
   lexer->i = 0;
   lexer->c = content[lexer->i];

   return lexer;
}

void lexer_next(lexer_t* lexer) {
   // if not at end of line or file
   if (lexer->c != '\0' && lexer->i < strlen(lexer->content)) {
      lexer->i += 1;                                  // advance index 1 character
      lexer->c = lexer->content[lexer->i];            // set character w/ index
   }
}

void lexer_pass(lexer_t* lexer) {
   while (lexer->c == ' ' ||
         lexer->c == '\t' ||
         lexer->c == '\n') {
      lexer_next(lexer);
   }
}

token_t* lexer_get_next_token(lexer_t* lexer) {
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
                            TOKEN_tILDE,
                            lexer_get_c_as_string(lexer)
                            )
                         ); break;
      }
   }

   return token_init(TOKEN_EOF, "\0");
}

token_t* lexer_get_string(lexer_t* lexer) {
   lexer_next(lexer);
   
   char* str_so_far = calloc(2, sizeof(char));
   str_so_far[0] = '\0';

   while (lexer->c != '"') {
      char* current = lexer_get_c_as_string(lexer);
      str_so_far = realloc(str_so_far, (strlen(str_so_far) + strlen(current) * sizeof(char)));  // give str so far some more memory
      strcat(str_so_far, current);  // add current to str so far

      lexer_next(lexer);
   }

   lexer_next(lexer);
   return token_init(TOKEN_QUOTE, str_so_far);
}

token_t* lexer_get_id(lexer_t* lexer) {
   char* str_so_far = calloc(1, sizeof(char));
   str_so_far[0] = '\0';

   while (isalnum(lexer->c)) {
      char* current = lexer_get_c_as_string(lexer);
      str_so_far = realloc(str_so_far, (strlen(str_so_far) + strlen(current) * sizeof(char)));
      strcat(str_so_far, current);

      lexer_next(lexer);
   }

   return token_init(TOKEN_ID, str_so_far);
}

token_t* lexer_next_token(lexer_t* lexer, token_t* token) {
   lexer_next(lexer);

   return token;
}

char* lexer_get_c_as_string(lexer_t* lexer) {
   char* str = calloc(1, sizeof(char));
   str[0] = lexer->c;
   str[1] = '\0';

   return str;
}

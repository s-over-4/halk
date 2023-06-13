#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/log.h"
#include "include/lexer.h" 


lexer_t* lexer_init(char* content) {
   lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUC));

   lexer->content = content;
   lexer->i = 0;
   lexer->c = content[lexer->i];

   return lexer;
}

void lexer_destroy(lexer_t* lexer) {
   free(lexer->content);
   free(lexer);
}

void lexer_next(lexer_t* lexer) {
   if (LEXER_VALID) {
      lexer->i += 1;
      lexer->c = lexer->content[lexer->i]; 
   }
}

void lexer_pass(lexer_t* lexer) {
   while (char_can_ignore(&lexer->c)) {
      lexer_next(lexer);
   }
}

token_t* lexer_get_next_token(lexer_t* lexer) {
   while (LEXER_VALID) {

      if (char_can_ignore(&lexer->c)) { lexer_pass(lexer); }
      if (char_could_start_int(&lexer->c)) {
         return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_PRIM_INT,
                  lexer_get_c_as_string(lexer)
                  )
               );
      }
      if (char_could_start_keyword(&lexer->c)) {  return lexer_get_keyword(lexer); }

      switch (lexer->c) {
         case '\'':
            return lexer_collect(lexer, '\'', 1, 1, TOKEN_PRIM_STR);
            break;
         case '`': 
            return lexer_collect(lexer, '`', 1, 1, TOKEN_COMM);
            break;
         case ';':
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_EXPR_END,
                  lexer_get_c_as_string(lexer)
               )
            );
            break;
         case '=':
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_DEF_SET,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '(': return lexer_next_token(
            lexer,
            token_init(
               TOKEN_LGROUP,
               lexer_get_c_as_string(lexer)
            )
         ); break;
         case ')': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_RGROUP,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '#':
            return lexer_collect(lexer, '#', 1, 1, TOKEN_DIRECTIVE);
            break;
         case '.': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_FN_APPLY,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case ',': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_LIST_DELIM,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case ':': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_DEF_TAGS_DELIM,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '/': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_NAMESPACE_DELIM,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '{': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_BLOCK_DELIM_START,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '}': 
            return lexer_next_token(
               lexer,
               token_init(
                  TOKEN_BLOCK_DELIM_END,
                  lexer_get_c_as_string(lexer)
               )
            ); 
            break;
         case '[':
            return lexer_collect(lexer, ']', 1, 1, TOKEN_PRIM_STR);
            break;
         case '\0': 
            return token_init(TOKEN_EOF, lexer_get_c_as_string(lexer)); 
            break;
         default:
            return token_init(TOKEN_UNKNOWN, lexer_get_c_as_string(lexer));
      }
   }

   return NULL;
}

token_t* lexer_next_token(lexer_t* lexer, token_t* token) {
   lexer_next(lexer);
   return token;
}

char* lexer_get_c_as_string(lexer_t* lexer) {
   char* str = calloc(2, 1 * sizeof(char));
   str[0] = lexer->c;
   str[1] = '\0';
   
   return str;
}

// fskip: skip first char?
// lskip: skip last char?
token_t* lexer_collect(lexer_t* lexer, char end_char, int fskip, int lskip, int type) {
   if (fskip) { lexer_next(lexer); }

   size_t len = 1;            // length of collected token so far
   char* token = calloc(len, sizeof(char));
   token[0] = '\0';

   while (lexer->c != end_char) {
      char* current = lexer_get_c_as_string(lexer);
      token = realloc(
         token,
         (len + strlen(current) * sizeof(char))
      );

      memcpy(token + len, current, strlen(current) * sizeof(char));
      len += strlen(current) * sizeof(char);
      lexer_next(lexer);
   }

   if (lskip) { lexer_next(lexer); }
   token[len] = '\0';         // null terminate

   return token_init(type, token);
}

token_t* lexer_get_keyword(lexer_t* lexer) {
   char* keyword_so_far = calloc(1, sizeof(char));
   keyword_so_far[0] = '\0';
   while (char_could_split_keyword(&lexer->c)) {
      char* current = lexer_get_c_as_string(lexer);
      keyword_so_far = realloc(
         keyword_so_far,
         (strlen(keyword_so_far) + strlen(current) * sizeof(char))
      );

      strcat(keyword_so_far, current);
      lexer_next(lexer);
   }

   return token_init(TOKEN_KEYWORD, keyword_so_far);
}

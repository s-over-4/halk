#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/util.h"
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

      if (char_can_ignore(&lexer->c))           { lexer_pass(lexer); }
      if (char_could_start_int(&lexer->c))      { return lexer_next_token(lexer, TOKEN_PRIM_INT); }
      if (char_could_start_keyword(&lexer->c))  { return lexer_collect(lexer, token_char_kywrd, 0, 1, TOKEN_KEYWORD); }

      switch (lexer->c) {
         case '\'':
            return lexer_collect(lexer, token_char_quote, 1, 1, TOKEN_PRIM_STR);
            break;
         case '`': 
            return lexer_collect(lexer, token_char_grave, 1, 1, TOKEN_COMM);
            break;
         case ';':
            return lexer_next_token(lexer, TOKEN_EXPR_END);
            break;
         case '=':
            return lexer_next_token(lexer, TOKEN_DEF_SET); 
            break;
         case '(': 
            return lexer_next_token(lexer, TOKEN_LGROUP); 
            break;
         case ')': 
            return lexer_next_token(lexer, TOKEN_RGROUP); 
            break;
         case '#':
            return lexer_collect(lexer, token_char_pound, 1, 1, TOKEN_DIRECTIVE);
            break;
         case '.': 
            return lexer_next_token(lexer, TOKEN_FN_APPLY); 
            break;
         case ',': 
            return lexer_next_token(lexer, TOKEN_LIST_DELIM); 
            break;
         case ':': 
            return lexer_collect(lexer, token_char_colon, 1, 1, TOKEN_DEF_TAG); 
            break;
         case '/': 
            return lexer_next_token(lexer, TOKEN_NAMESPACE_DELIM); 
            break;
         case '{': 
            return lexer_next_token(lexer, TOKEN_BLOCK_START); 
            break;
         case '}': 
            return lexer_next_token(lexer, TOKEN_BLOCK_END); 
            break;
         case '[':
            return lexer_next_token(lexer, TOKEN_ARRAY_START);
            break;
         case ']':
            return lexer_next_token(lexer, TOKEN_ARRAY_END);
            break;
         case '\0': 
            return token_init(TOKEN_EOF, lexer_get_c_as_string(lexer)); 
            break;
         default:
            return lexer_next_token(lexer, TOKEN_UNKNOWN);
      }
   }

   return NULL;
}

token_t* lexer_next_token(lexer_t* lexer, int token_type) {
   token_t* token = token_init(token_type, lexer_get_c_as_string(lexer));
   lexer_next(lexer);
   return token;
}

char* lexer_get_c_as_string(lexer_t* lexer) {
   char* str = calloc(2, sizeof(char));
   str[0] = lexer->c;
   str[1] = '\0';
   
   return str;
}

// fskip: skip first char?
// lskip: skip last char?
token_t* lexer_collect(lexer_t* lexer, int (*end_char)(char), int fskip, int lskip, int type) {
   if (fskip) { lexer_next(lexer); }

   size_t len = 0;            // length of collected token so far
   char* token = calloc(len, sizeof(char));
   token[0] = '\0';

   while (end_char(lexer->c)) {
      char* current = lexer_get_c_as_string(lexer);
      token = realloc(
         token,
         (len + strlen(current) * sizeof(char))
      );

      memcpy(token + len, current, strlen(current) * sizeof(char));
      len += strlen(current) * sizeof(char);
      free(current);
      lexer_next(lexer);
   }

   if (lskip) { lexer_next(lexer); }
   token[len] = '\0';         // null terminate

   return token_init(type, token);
}

token_t* lexer_get_keyword(lexer_t* lexer) {
   size_t len = 0;
   char* keyword = calloc(len, sizeof(char));
   keyword[0] = '\0';
   while (char_could_split_keyword(&lexer->c)) {
      char* current = lexer_get_c_as_string(lexer);
      keyword = realloc(
         keyword,
         (len + strlen(current) * sizeof(char))
      );

      memcpy(keyword + len, current, strlen(current) * sizeof(char));
      len += strlen(current) * sizeof(char);
      free(current);
      lexer_next(lexer);
   }

   return token_init(TOKEN_KEYWORD, keyword);
}

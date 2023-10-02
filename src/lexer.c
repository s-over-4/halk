#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/lexer.h" 

lexer_t* lexer_init(char* content) {
   lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUC));

   lexer->content = content;
   lexer->i = 0;
   lexer->c = content[lexer->i];

   return lexer;
}

void lexer_destroy(lexer_t* lexer) {
   free(lexer);
}

void lexer_next(lexer_t* lexer) {
   if (LEXER_VALID) {
      lexer->i ++;
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
      if (char_could_start_keyword(&lexer->c))  { return lexer_collect(lexer, token_char_kywrd, 0, 0, TOKEN_KEYWORD); }

      switch (lexer->c) {
         case SYNTAX_STR_DELIM:
            return lexer_collect(lexer, token_char_quote, 1, 1, TOKEN_PRIM_STR);
            break;
         case SYNTAX_EXPR_END: 
            return lexer_next_token(lexer, TOKEN_STMNT_END);
            break;
         case SYNTAX_SET:
            return lexer_next_token(lexer, TOKEN_DEF_SET); 
            break;
         case SYNTAX_LGROUP: 
            return lexer_next_token(lexer, TOKEN_LGROUP); 
            break;
         case SYNTAX_RGROUP: 
            return lexer_next_token(lexer, TOKEN_RGROUP); 
            break;
         case SYNTAX_APPLY: 
            return lexer_next_token(lexer, TOKEN_FN_APPLY); 
            break;
         case SYNTAX_LIST_DELIM: 
            return lexer_next_token(lexer, TOKEN_LIST_DELIM); 
            break;
         case SYNTAX_TAG_DELIM:
            return lexer_collect(lexer, token_char_kywrd, 1, 0, TOKEN_DEF_TAG);
            break;
         case SYNTAX_NAMESPACE_DELIM: 
            return lexer_next_token(lexer, TOKEN_NAMESPACE_DELIM); 
            break;
         case SYNTAX_LBLOCK: 
            return lexer_next_token(lexer, TOKEN_BLOCK_START); 
            break;
         case SYNTAX_RBLOCK: 
            return lexer_next_token(lexer, TOKEN_BLOCK_END); 
            break;
         case SYNTAX_LLIST:
            return lexer_next_token(lexer, TOKEN_ARRAY_START);
            break;
         case SYNTAX_RLIST:
            return lexer_next_token(lexer, TOKEN_ARRAY_END);
            break;
         case '\0': 
         case EOF:
            return token_init(TOKEN_EOF, lexer_get_c_as_string(lexer)); 
            break;
         default:
            return lexer_next_token(lexer, TOKEN_UNKNOWN);
            break;
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
   char* str;  /* the string to return */

   str = malloc(2);
   str[0] = lexer->c;
   str[1] = '\0';
   
   return str;
}

token_t* lexer_collect(lexer_t* lexer, int (*end_char)(char), int fskip, int lskip, int type) {
   size_t   len;     /* length of collected token so far */
   char*    token;   /* collected token so far */

   len = 0;
   token = calloc(len, sizeof(char));

   if (fskip) { lexer_next(lexer); }

   while (end_char(lexer->c)) {
      char* current;

      current = lexer_get_c_as_string(lexer);
      token = realloc(
         token,
         (len + sizeof(current))
      );

      memcpy(token + len, current, sizeof(char) * strlen(current));
      len += strlen(current) * sizeof(char);
      lexer_next(lexer);

      free(current);
   }

   if (lskip) { lexer_next(lexer); }

   token[len] = '\0';   /* terminate */

   return token_init(type, token);
}

lexer_t* lexer_run(lexer_t* lexer) {
   while (1) {
      token_t* token;
      char* type;

      token = lexer_get_next_token(lexer);
      type = token_get_type(token->type);

      log_inf("type: %s\t\tval:%s", type, token->value);

      if (token->type == TOKEN_EOF) {
         token_destroy(token);
         break;
      } 

      token_destroy(token);
   }

   return lexer;
}

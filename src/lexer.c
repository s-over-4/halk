#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/lexer.h" 

lexer_t* lexer_init(char* src) {
   lexer_t* lexer;

   lexer = emalloc(sizeof(struct LEXER_STRUC));

   lexer->src = src;
   lexer->state = LEXER_STATE_REG;
   lexer->tokenl = NULL;
   lexer->tokenc = 0;

   return lexer;
}

void lexer_destroy(lexer_t* lexer) {
   free(lexer);
}

void lexer_add_token(lexer_t* lexer, token_t* token) {
   token_t* t;

   t = token_last(lexer->tokenl)->nxt;
   t = token;

   log_inf("token/v:%s\t/t:%d", token->val, token->type);

   lexer->tokenc ++;
}

void lexer_add_current_char(lexer_t* lexer, int type) {
   char* c;    /* get the current character as a string */
   token_t* t; /* the token to be added */

   c = ecalloc(2, sizeof(char));
   c[0] = *lexer->src;
   c[1] = '\0';

   t = token_init(type, c);

   lexer_add_token(lexer, t);
}

void lexer_do_reg(lexer_t* lexer) {
   switch (*lexer->src) {
      case SYNTAX_APPLY:
         lexer_add_current_char(lexer, TOKEN_APPLY);
         break;
      default:
         lexer_add_current_char(lexer, TOKEN_UNKNOWN);
         
   }
}

void lexer_run(lexer_t* lexer) {
   while (*lexer->src) {
      if (lexer->state == LEXER_STATE_REG) { lexer_do_reg(lexer); }
      lexer->src ++;
   }
}

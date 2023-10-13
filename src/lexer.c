#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/lexer.h" 
#include "include/syntax.h"
#include "include/token.h"

lexer_t* lexer_init(char* src) {
   lexer_t* lexer;

   lexer = emalloc(sizeof(struct LEXER_STRUC));

   lexer->src = src;
   lexer->state = LEXER_STATE_REG;
   lexer->tokenl = NULL;
   lexer->tokenl_last = NULL;
   lexer->tokenc = 0;

   return lexer;
}

void lexer_destroy(lexer_t* lexer) {
   free(lexer);
}

void lexer_add_token(lexer_t* lexer, token_t* token) {
   token_t* t;

   if (lexer->tokenl) {
      lexer->tokenl_last->nxt = token;
      lexer->tokenl_last = token;
   } else {
      lexer->tokenl = token;
      lexer->tokenl_last = token;
   }

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
      case SYNTAX_TAG_DELIM:
         lexer_add_current_char(lexer, TOKEN_TAG_DELIM);
         break;
      case SYNTAX_NAMESPACE_DELIM:
         lexer_add_current_char(lexer, TOKEN_NAMESPACE_DELIM);
         break;
      case SYNTAX_SET:
         lexer_add_current_char(lexer, TOKEN_SET);
         break;
      case SYNTAX_LLIST:
         lexer_add_current_char(lexer, TOKEN_LLIST);
         break;
      case SYNTAX_RLIST:
         lexer_add_current_char(lexer, TOKEN_RLIST);
         break;
      case SYNTAX_LGROUP:
         lexer_add_current_char(lexer, TOKEN_LGROUP);
         break;
      case SYNTAX_RGROUP:
         lexer_add_current_char(lexer, TOKEN_RGROUP);
         break;
      case SYNTAX_EXPR_END:
         lexer_add_current_char(lexer, TOKEN_EXPR_END);
         break;
      case SYNTAX_STR_DELIM:
         lexer_add_current_char(lexer, TOKEN_STR_DELIM);
         break;
      case SYNTAX_CHAR_DELIM:
         lexer_add_current_char(lexer, TOKEN_CHAR_DELIM);
         break;
      case SYNTAX_LIST_DELIM:
         lexer_add_current_char(lexer, TOKEN_LIST_DELIM);
         break;
      default:
         lexer_add_current_char(lexer, TOKEN_UNKNOWN);
   }
}

void lexer_do_chr(lexer_t* lexer) {
   if (*lexer->src == '\'') {
      lexer->state = LEXER_STATE_REG;
   } else {
      token_t* t;

      t = token_init(TOKEN_CHAR, *lexer->src);

      lexer_add_token(lexer, t);
   }
}

void lexer_do_str(lexer_t* lexer) {

}

void lexer_run(lexer_t* lexer) {
   while (*lexer->src) {
      if (lexer->state == LEXER_STATE_REG) { lexer_do_reg(lexer); }
      lexer->src ++;
   }
}

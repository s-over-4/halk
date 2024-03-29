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
   if (lexer->tokenl) {
      lexer->tokenl_last->nxt = token;
      lexer->tokenl_last = token;
   } else {
      lexer->tokenl = token;
      lexer->tokenl_last = token;
   }

   lexer->tokenc ++;
}

void lexer_add_current_char(lexer_t* lexer, int type) {
   token_t* t; /* the token to be added */

   t = token_init(type, *lexer->src);

   lexer_add_token(lexer, t);
}

void lexer_add_current_char_to_last_token(lexer_t* lexer, token_type_t type) {
   if (lexer->tokenl_last && lexer->tokenl_last->type == type) {
      token_add_char(lexer->tokenl_last, *lexer->src);
   } else {
      lexer_add_current_char(lexer, type);
   }
}

void lexer_do_reg(lexer_t* lexer) {
   switch (*lexer->src) {
      case SYNTAX_APPLY:
         lexer_add_current_char(lexer, TOKEN_TYPE_APPLY);
         break;
      case SYNTAX_TAG_DELIM:
         lexer->state = LEXER_STATE_TAG;
         break;
         /*case SYNTAX_NAMESPACE_DELIM:
         lexer_add_current_char(lexer, TOKEN_NAMESPACE_DELIM);
         break;*/
      case SYNTAX_SET:
         lexer_add_current_char(lexer, TOKEN_TYPE_SET);
         break;
      case SYNTAX_LLIST:
         lexer_add_current_char(lexer, TOKEN_TYPE_LLIST);
         break;
      case SYNTAX_RLIST:
         lexer_add_current_char(lexer, TOKEN_TYPE_RLIST);
         break;
      case SYNTAX_LGROUP:
         lexer_add_current_char(lexer, TOKEN_TYPE_LGROUP);
         break;
      case SYNTAX_RGROUP:
         lexer_add_current_char(lexer, TOKEN_TYPE_RGROUP);
         break;
      case SYNTAX_LBLOCK:
         lexer_add_current_char(lexer, TOKEN_TYPE_LBLOCK);
         break;
      case SYNTAX_RBLOCK:
         lexer_add_current_char(lexer, TOKEN_TYPE_RBLOCK);
         break;
      case SYNTAX_EXPR_END:
         lexer_add_current_char(lexer, TOKEN_TYPE_EXPR_END);
         break;
      case SYNTAX_LIST_DELIM:
         lexer_add_current_char(lexer, TOKEN_TYPE_LIST_DELIM);
         break;
      case SYNTAX_STR_DELIM:
         lexer->state = LEXER_STATE_STR;
         break;
      default:
         if (isdigit(*lexer->src)) {
            lexer_add_current_char(lexer, TOKEN_TYPE_INT);
            if (isdigit(*(lexer->src + 1))) { lexer->state = LEXER_STATE_INT; }

         } else if (strchr(SYNTAX_KWD_CHARS, *lexer->src)) {
            lexer_add_current_char(lexer, TOKEN_TYPE_KWD);
            if (strchr(SYNTAX_KWD_CHARS, *(lexer->src + 1))) { lexer->state = LEXER_STATE_KWD; }

         } else {
            lexer_add_current_char(lexer, TOKEN_TYPE_UNKNOWN);
            lexer->state = LEXER_STATE_REG;
         }
   }
}

void lexer_do_tag(lexer_t* lexer) {
   switch (*lexer->src) {
      case SYNTAX_LIST_DELIM:
         lexer_add_current_char(lexer, TOKEN_TYPE_LIST_DELIM);
         lexer->state = LEXER_STATE_REG;
         break;
      case SYNTAX_SET:
         lexer_add_current_char(lexer, TOKEN_TYPE_SET);
         lexer->state = LEXER_STATE_REG;
         break;
      case SYNTAX_APPLY:
         lexer_add_current_char(lexer, TOKEN_TYPE_APPLY);
         lexer->state = LEXER_STATE_REG;
         break;
      case SYNTAX_TAG_DELIM:
         lexer_add_token(lexer, token_init(TOKEN_TYPE_TAG, '\0'));
         break;
      default: lexer_add_current_char_to_last_token(lexer, TOKEN_TYPE_TAG);
   }
}

void lexer_do_str(lexer_t* lexer) {
   if (*lexer->src == SYNTAX_STR_DELIM) {
      lexer->state = LEXER_STATE_REG;
   } else {
      lexer_add_current_char_to_last_token(lexer, TOKEN_TYPE_STR);
   }
}

void lexer_do_int(lexer_t* lexer) {
   if (isdigit(*lexer->src)) {
      lexer_add_current_char_to_last_token(lexer, TOKEN_TYPE_INT);
      ! isdigit(*(lexer->src + 1)) && ( lexer->state = LEXER_STATE_REG );
   } else {
      LOG_ERR("int state at non-int token");
   }
}

void lexer_do_kwd(lexer_t* lexer) {
   if (strchr(SYNTAX_KWD_CHARS, *lexer->src)) {
      lexer_add_current_char_to_last_token(lexer, TOKEN_TYPE_KWD);
      ! strchr(SYNTAX_KWD_CHARS, *(lexer->src + 1)) && 
         ( lexer->state = LEXER_STATE_REG );
   } else {
      LOG_ERR("keyword state at non-keyword token");
   }
   
}

void lexer_run(lexer_t* lexer) {
   while (*lexer->src) {
      if (lexer->state == LEXER_STATE_REG) { lexer_do_reg(lexer); }
      else if (lexer->state == LEXER_STATE_TAG) { lexer_do_tag(lexer); }
      else if (lexer->state == LEXER_STATE_STR) { lexer_do_str(lexer); }
      else if (lexer->state == LEXER_STATE_INT) { lexer_do_int(lexer); }
      else if (lexer->state == LEXER_STATE_KWD) { lexer_do_kwd(lexer); }
      lexer->src ++;
   }
}

#ifndef LEXER_H
#define LEXER_H

#include "util.h"
#include "syntax.h"
#include "token.h"

/* The Lexer. */
typedef struct LEXER_STRUC {
   /* Source being read. */
   char* src;

   /* What the lexer is looking at right now. */
   enum LEXER_STATE {
      /* Normal 1-character token. */
      LEXER_STATE_REG,
      /* Definition tag. */
      LEXER_STATE_TAG,
      /* String. */
      LEXER_STATE_STR,
      /* Escaped character in string. */
      LEXER_STATE_STR_ESC,
      /* Integer. */
      LEXER_STATE_INT,
      /* Keyword. */
      LEXER_STATE_KWD
   } state;

   /* The linked list of tokens generated. */
   token_t* tokenl;
   /* Pointer to the last token in tokenl. */
   token_t* tokenl_last;
   /* Number of tokens in tokenl. */
   int tokenc;
} lexer_t;

/* Create lexer from source. */
lexer_t* lexer_init (char* src);

/* 
   Destroy a lexer.
   - Does not free `src.
   - Does not free `tokenl`.
*/
void lexer_destroy (lexer_t* lexer);

/* Add token to tokenl. */
void lexer_add_token(lexer_t* lexer, token_t* token);
/* Add the current character as a token to tokenl. Utility function `for lexer_do_reg()`. */
void lexer_add_current_char(lexer_t* lexer, int type);

/* 
   Add first character of given lexer's `src` to the value of the last token in `tokenl`, if it exists. 
   Otherwise, create new token and add it. 
*/
void lexer_add_current_char_to_last_token(lexer_t* lexer, token_type_t type);

/* Handle regular state. */
void lexer_do_reg(lexer_t* lexer);
/* Handle definition tag. state*/
void lexer_do_tag(lexer_t* lexer);
/* TODO: handle character state. */
void lexer_do_chr(lexer_t* lexer);
/* Handle string state. */
void lexer_do_str(lexer_t* lexer);
/* Handle integer. */
void lexer_do_int(lexer_t* lexer);
/* Handle keywords. */
void lexer_do_kwd(lexer_t* lexer);

/* Run lexer. */
void lexer_run(lexer_t* lexer);

#endif

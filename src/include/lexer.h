#ifndef LEXER_H
#define LEXER_H

#include "util.h"
#include "syntax.h"
#include "token.h"

#define LEXER_VALID (lexer->c != '\0' && lexer->i < strlen(lexer->content))

/* the lexer struct */
typedef struct LEXER_STRUC {
   /* source being read */
   char* src;

   /* what the lexer is looking at right now */
   enum LEXER_STATE {
      /* normal 1-character token */
      LEXER_STATE_REG,
      /* character */
      LEXER_STATE_CHR,
      /* string */
      LEXER_STATE_STR,
      /* definition */
      LEXER_STATE_DEF,
      /* call */
      LEXER_STATE_CAL
   } state;

   /* the linked list of tokens generated */
   token_t* tokenl;
   /* pointer to the last token in tokenl */
   token_t* tokenl_last;
   /* number of tokens in tokenl */
   int tokenc;
} lexer_t;

/* create lexer from source */
lexer_t* lexer_init (char* src);

/* destroy lexer **but not src or tokenl** */
void lexer_destroy (lexer_t* lexer);

/* add token to tokenl */
void lexer_add_token(lexer_t* lexer, token_t* token);
/* add the current character as a token to tokenl -- utility function for
   lexer_do_reg() */
void lexer_add_current_char(lexer_t* lexer, int type);

/* handle regular state */
void lexer_do_reg(lexer_t*);
/* handle character state */
void lexer_do_chr(lexer_t*);
/* handle string state */
void lexer_do_str(lexer_t*);
/* handle definition state */
void lexer_do_def(lexer_t*);
/* handle call state */
void lexer_do_cal(lexer_t*);

/* run lexer */
void lexer_run(lexer_t*);

#endif

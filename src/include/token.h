#ifndef TOKEN_H
#define TOKEN_H

#include "util.h"
#include "hlkt.h"

/* token struct */
typedef struct TOKEN_STRUC {
   /* token type */
   enum TOKEN_TYPE {
      TOKEN_UNKNOWN,
      TOKEN_CHAR,
      TOKEN_STR,
      TOKEN_EXPR_END,
      TOKEN_SET,
      TOKEN_LGROUP,
      TOKEN_RGROUP,
      TOKEN_APPLY,
      TOKEN_LIST_DELIM,
      TOKEN_TAG,
      TOKEN_NAMESPACE_DELIM,
      TOKEN_LBLOCK,
      TOKEN_RBLOCK,
      TOKEN_RLIST,
      TOKEN_LLIST,
      TOKEN_ESC
   } type;

   /* token value */
   char* val;

   /* next token */
   struct TOKEN_STRUC* nxt;
} token_t;

/* creates a token */
token_t* token_init(int type, char val);
/* destroys a token **and all tokens contained in nxt** **Make sure to set the nxt of any parent tokens to NULL** */
void token_destroy(token_t* token);

/* return pointer to the last token */
token_t* token_last(token_t* token);
/* add a character to the token value */
void token_add_char(token_t*, char);

/* print a token -- for debugging purposes */
void token_print(token_t* token);

#endif

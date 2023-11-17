#ifndef TOKEN_H
#define TOKEN_H

#include "util.h"
#include "hlkt.h"

/* Token struct. */
typedef struct TOKEN_STRUC {
   /* Token type. */
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
      TOKEN_ESC,
      TOKEN_KWD,
      TOKEN_INT
   } type;

   /* Token value. */
   char* val;

   /* Next token. */
   struct TOKEN_STRUC* nxt;
} token_t;

/* Creates a token. */
token_t* token_init(int type, char val);
/*
   Destroys a token.
   - Frees all tokens contained in `nxt`.
   - Make sure to set the `nxt` field of a parent token to `NULL`.
*/
void token_destroy(token_t* token);

/* Return pointer to the last token. */
token_t* token_last(token_t* token);
/* Add a character to the token value. */
void token_add_char(token_t*, char);

/* Print a token -- for debugging purposes. */
void token_print(token_t* token);

#endif

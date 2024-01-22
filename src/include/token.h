#ifndef TOKEN_H
#define TOKEN_H

#include "util.h"

typedef enum TOKEN_TYPE {
   TOKEN_TYPE_UNKNOWN,
   TOKEN_TYPE_CHAR,
   TOKEN_TYPE_STR,
   TOKEN_TYPE_EXPR_END,
   TOKEN_TYPE_SET,
   TOKEN_TYPE_LGROUP,
   TOKEN_TYPE_RGROUP,
   TOKEN_TYPE_APPLY,
   TOKEN_TYPE_LIST_DELIM,
   TOKEN_TYPE_TAG,
   TOKEN_TYPE_NAMESPACE_DELIM,
   TOKEN_TYPE_LBLOCK,
   TOKEN_TYPE_RBLOCK,
   TOKEN_TYPE_RLIST,
   TOKEN_TYPE_LLIST,
   TOKEN_TYPE_ESC,
   TOKEN_TYPE_KWD,
   TOKEN_TYPE_INT
} token_type_t;

/* Token struct. */
typedef struct TOKEN {
   /* Token type. */
   token_type_t type;

   /* Token value. */
   char* val;

   /* Next token. */
   struct TOKEN* nxt;
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

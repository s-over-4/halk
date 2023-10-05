#include <stdlib.h>

#include "include/token.h"

token_t* token_init(int type, char* val) {
   token_t* token;

   token = emalloc(sizeof(struct TOKEN_STRUC));
   token->type = type;
   token->val = val;
   token->nxt = NULL;

   return token;
}

void token_destroy(token_t* token) {
   free(token);
}

token_t* token_last(token_t* token) {
   token_t* t;

   while (t->nxt) {
      t = t->nxt;
   }

   return t;
}

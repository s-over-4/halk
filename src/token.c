#include "include/token.h"
#include <stdlib.h>

token_T* token_init(int type, char* val) {
   token_T* token = calloc(1, sizeof(struct TOKEN_STRUC));
   token->type = type;
   token->value = val;

   return token;
}

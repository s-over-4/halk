#include <stdlib.h>


#include "include/token.h"


// token constructor
token_t* token_init(int type, char* val) {
   token_t* token = calloc(1, sizeof(struct TOKEN_STRUC));
   token->type = type;
   token->value = val;

   return token;
}

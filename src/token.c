#include "include/token.h"

token_t* token_init(int type, char val) {
   token_t* token;

   token = emalloc(sizeof(token_t));
   token->type = type;
   token->val = emalloc(2);
   *token->val = val;
   token->val[1] = '\0';
   token->nxt = NULL;

   return token;
}

void token_destroy(token_t* token) {
   if (token->nxt) {
      token_destroy(token->nxt);
      token->nxt = NULL;
   }

   free(token->val);
   free(token);
}

token_t* token_last(token_t* token) {
   token_t* t;

   while (t->nxt) {
      t = t->nxt;
   }

   return t;
}

void token_add_char(token_t* token, char c) {
   size_t orig;

   orig = strlen(token->val);

   token->val = erealloc(token->val, orig + sizeof c + 1);
   token->val[orig] = c;
   token->val[orig + 1] = '\0';
}

void token_print(token_t* token) {

   log_dbg("token/t=%d\t/v=%s", token->type, token->val);

   if (token->nxt) {
      token_print(token->nxt);
   }
}

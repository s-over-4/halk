#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LEXER_STRUC {
   char c;           // current character in content
   unsigned int i;   // index of c
   char* content;    // the code itself
} lexer_t;

lexer_t* lexer_init(char* content);

void lexer_next(lexer_t* lexer);
void lexer_pass(lexer_t* lexer);

token_t* lexer_get_next_token(lexer_t* lexer);

token_t* lexer_get_string(lexer_t* lexer);

token_t* lexer_get_comment(lexer_t* lexer);

token_t* lexer_get_id(lexer_t* lexer);

token_t* lexer_next_token(lexer_t* lexer, token_t* token);

char* lexer_get_c_as_string(lexer_t* lexer);

#endif

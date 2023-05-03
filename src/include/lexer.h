#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LEXER_STRUC {
   char c;           // current character in content
   unsigned int i;   // index of c
   char* content;    // the code itself
} lexer_T;

lexer_T* lexer_init(char* content);
void lexer_next(lexer_T* lexer);
void lexer_pass(lexer_T* lexer);
token_T* lexer_get_next_token(lexer_T* lexer);
token_T* lexer_get_string(lexer_T* lexer);
token_T* lexer_get_id(lexer_T* lexer);
token_T* lexer_next_token(lexer_T* lexer, token_T* token);
char* lexer_get_c_as_string(lexer_T* lexer);

#endif

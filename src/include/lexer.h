#ifndef LEXER_H
#define LEXER_H


#include "token.h"


#define LEXER_VALID (lexer->c != '\0' && lexer->i < strlen(lexer->content))


typedef struct LEXER_STRUC {
   char c;           // current character in content
   unsigned int i;   // index of c
   char* content;    // the code itself
} lexer_t;


// constructor/destroyer
extern lexer_t*   lexer_init                 (char* content);
extern void       lexer_destroy              (lexer_t* lexer);

// advance the lexer
extern void       lexer_next                 (lexer_t* lexer);
extern void       lexer_pass                 (lexer_t* lexer);
extern token_t*   lexer_get_next_token       (lexer_t* lexer);    // chars -> tokens
extern token_t*   lexer_next_token           (lexer_t* lexer, int token_type);
extern char*      lexer_get_c_as_string      (lexer_t* lexer);

// collectors
extern token_t*   lexer_get_arr              (lexer_t* lexer);
extern token_t*   lexer_collect              (lexer_t* lexer, int (*end_char)(char), int fskip, int lskip, int type);

// special def collectors
extern token_t*   lexer_get_directive        (lexer_t* lexer);
extern token_t*   lexer_get_keyword          (lexer_t* lexer);

#endif

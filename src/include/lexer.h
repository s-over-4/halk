#ifndef LEXER_H
#define LEXER_H

#include "util.h"
#include "syntax.h"
#include "token.h"

#define LEXER_VALID (lexer->c != '\0' && lexer->i < strlen(lexer->content))

/* the lexer struct */
typedef struct LEXER_STRUC {
   /* current character in content */
   char c;

   /* index of c */
   unsigned int i;

   /* source being read */
   char* content;
} lexer_t;


/* create lexer from source code */
extern lexer_t*   lexer_init                 (char* content);

/* destroy the lexer */
extern void       lexer_destroy              (lexer_t* lexer);

/* move lexer forward one char */
extern void       lexer_next                 (lexer_t* lexer);

/* skip useless characters */
extern void       lexer_pass                 (lexer_t* lexer);

/* create tokens */
extern token_t*   lexer_get_next_token       (lexer_t* lexer);

/* create token and move 1 char */
extern token_t*   lexer_next_token           (lexer_t* lexer, int token_type);

/* create string from lexer->c */
extern char*      lexer_get_c_as_string      (lexer_t* lexer);

/*
   int fskip: skip first char?

   int lskip: skip last char?
*/
extern token_t*   lexer_collect              (lexer_t* lexer, int (*end_char)(char), int fskip, int lskip, int type);

/* run lexer from source */
lexer_t* lexer_run(lexer_t*);

#endif

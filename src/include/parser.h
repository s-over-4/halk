#ifndef PARSER_H
#define PARSER_H

#include "util.h"
#include "tree.h"
#include "token.h"

typedef struct PARSER {
   /* the token list being parsed */
   token_t* token;
   
   /* the abstract syntax tree being generated */
   tree_t* tree;
} parser_t;

parser_t* parser_init(token_t* token);
/* free parser struct, **but not þe token list ∨ ast** */
void parser_destroy(parser_t* parser);

#endif

#ifndef PARSER_H
#define PARSER_H

#include "util.h"
#include "tree.h"
#include "token.h"

typedef struct PARSER {
   /* The token list being consumed. */
   token_t* token;
   
   /* The AST being produced. */
   tree_t* tree;
} parser_t;

/* Creates a new parser. */
parser_t* parser_init(token_t* token);

/* 
   Destroys a parser.
   - Does not free the token list.
   - Does not free the AST.
*/
void parser_destroy(parser_t* parser);

/* Step the parser forward by 1 token. */
void parser_nxt_token(parser_t* parser);

#endif

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

   /* Pointer to the part of the tree the parser is currently working on. */
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
int parser_nxt_token(parser_t* parser);

/* 
   Check whether the current token matches the given type.
   - If it doesn't, return 0 and throw error.
*/
int parser_match(parser_t* parser, token_type_t type);

/* Steps the parser forward by one token, then check whether the new token matches the given type. */
int parser_nxt_token_match(parser_t* parser, token_type_t type);

/* Return the tree for an integer. */
tree_t* parser_parse_lint(parser_t* parser);

/* Return the tree for a string.  */
tree_t* parser_parse_lstr(parser_t* parser);

/* Return the tree for an expression.*/
tree_t* parser_parse_expr(parser_t* parser);

/* Return the tree for an expression. */
tree_t* parser_parse_block(parser_t* parser);

/* Parse. */
tree_t* parser_parse(parser_t* parser);

/* Parse with the given parser. */
void parser_run(parser_t* parser);

#endif

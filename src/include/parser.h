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
int parser_nxt_token(parser_t* parser);

/* Check whether the current token matches the given type. */
int parser_match(parser_t* parser, token_type_t type);

/* 
   parse lit: converting everything from strings to value in the tree
   parse expr: (For now) call parse lit
   parse blk: loop over all expressions until reaching an end block.

*/

/* Parse a single literal value. */
void parser_parse_lit(parser_t* parser);

/* Parse a single expression. */
void parser_parse_expr(parser_t* parser);

/* Parse a single block. */
void parser_parse_blk(parser_t* parser);

/* Parse the given tokens. */
void parser_parse(parser_t* parser);

#endif

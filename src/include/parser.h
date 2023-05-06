#ifndef PARSER_H
#define PARSER_H


#include "token.h"
#include "tree.h"
#include "lexer.h"


typedef struct PARSER_STRUC {
   lexer_t* lexer;
   token_t* token;
} parser_t;

// initialize a parser
parser_t* parser_init(lexer_t* lexer);

// check for expected token, or throw syntax error
void parser_check_expect(parser_t* parser, int token_type);

// creates the abstract syntax tree
tree_t* parser_parse(parser_t* parser);

tree_t* parser_parse_token_id(parser_t* parser);

// parse a single chunk
tree_t* parser_parse_chunk(parser_t* parser);

// parse all in list of chunks
tree_t* parser_parse_chunks(parser_t* parser);

tree_t* parser_parse_expr(parser_t* parser);

tree_t* parser_parse_fac(parser_t* parser);

tree_t* parser_parse_term(parser_t* parser);

tree_t* parser_parse_fn_call(parser_t* parser);

tree_t* parser_parse_var(parser_t* parser);
tree_t* parser_parse_var_def(parser_t* parser);

tree_t* parser_parse_str(parser_t* parser);


#endif

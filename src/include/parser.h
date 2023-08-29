#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "tree.h"

#include <stdarg.h>

typedef struct PARSER_STRUC {
   lexer_t* lexer;      // lexer used by the parser
   token_t* token;      // current token
} parser_t;

parser_t* parser_init(lexer_t* lexer);
void parser_destroy(parser_t* parser);

// expect token(s), or die 
void parser_token_expect(parser_t* parser, int token, ...);

// do the parse
tree_t* parser_parse(parser_t* parser);

// parse expressions 
// - returns what it evaluates to
// - can contain other exprs
tree_t* parser_parse_exprs(parser_t* parser);
tree_t* parser_parse_expr(parser_t* parser);

// parse blocks
// - in curly brackets
// - contains many exprs
// - returns last expr
tree_t* parser_parse_blocks(parser_t* parser);
tree_t* parser_parse_block(parser_t* parser);

tree_t* parser_parse_def(parser_t* parser);
tree_t* parser_parse_call(parser_t* parser);

tree_t* parser_parse_type_str(parser_t* parser);
tree_t* parser_parse_type_int(parser_t* parser);

#endif

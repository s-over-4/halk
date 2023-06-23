#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "tree.h"

typedef struct PARSER_STRUC {
   lexer_t* lexer;      // lexer used by the parser
   token_t* token;      // current token
} parser_t;

parser_t* parser_init(lexer_t* lexer);
void parser_destroy(parser_t* parser);

// expect token, or die 
void parser_token_expect(parser_t* parser, int (*expected_token)(token_t*));

// do the parse
tree_t* parser_parse(parser_t* parser);

// parse statements
// - end in semicolon or ) or }
// - can contain one expression
// - return what they evaluate to
tree_t* parser_parse_statements(parser_t* parser);
tree_t* parser_parse_statement(parser_t* parser);

// parse expressions 
// - in parenthetical
// - contain only one statement
// - return what that statement evaluates to
// - adds layer of scope)
// basically a statement, but with a layer of scope
tree_t* parser_parse_exprs(parser_t* parser);
tree_t* parser_parse_expr(parser_t* parser);

// parse blocks
// - in curly brackets
// - many statements
// - return what last statement evaluates to
tree_t* parser_parse_blocks(parser_t* parser);
tree_t* parser_parse_block(parser_t* parser);

// blocks contain many statements, any of which may contain any number of expressions

tree_t* parser_parse_def(parser_t* parser);
tree_t* parser_parse_call(parser_t* parser);

tree_t* parser_parse_type_str(parser_t* parser);
tree_t* parser_parse_type_int(parser_t* parser);

#endif

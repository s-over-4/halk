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
void parser_token_expect(parser_t* parser, int token_type);

// do the parse
tree_t* parser_parse(parser_t* parser);
tree_t* parser_parse_token(parser_t* parser);

// parse hunks
tree_t* parser_parse_hunk(parser_t* parser);
tree_t* parser_parse_hunks(parser_t* parser);

// leaves of the tree
tree_t* parser_parse_prim(parser_t* parser);
tree_t* parser_parse_subtree(parser_t* parser);
tree_t* parser_parse_def(parser_t* parser);
tree_t* parser_parse_call(parser_t* parser);

// primitives
tree_t* parser_parse_prim_str(parser_t* parser);
tree_t* parser_parse_prim_int(parser_t* parser);
tree_t* parser_parse_prim_unkwn(parser_t* parser);

// defs
tree_t* parser_parse_def_tags(parser_t* parser);
int parser_is_def_tag(char* maybe_tag);


#endif

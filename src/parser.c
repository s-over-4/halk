#include "include/parser.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
// initialize a parser
parser_t* parser_init(lexer_t* lexer) {
   parser_t* parser = calloc(1, sizeof(struct PARSER_STRUC));

   parser->lexer = lexer;
   parser->token = lexer_get_next_token(lexer);

   return parser;
}

// check for expected token, or throw syntax error
void parser_check_expect(parser_t* parser, int token_type) {
   if (parser->token->type == token_type) {
      parser->token = lexer_get_next_token(parser->lexer);
   } else {
      printf("[ERRR] PARSE ERROR at %d\n\tUnexpected token '%s' with type '%d'.", 
      parser->lexer->i, parser->token->value, parser->token->type);

      exit(1);
   }
}

// creates the abstract syntax tree
tree_t* parser_parse(parser_t* parser) {
   return parser_parse_chunks();
}

tree_t* parser_parse_token_id(parser_t* parser) {
   if (strcmp(parser->token->value, "var")) {
      return parser_parse_var(parser);
   } else { // if id not recognized, check for variables under that name
      return parser_parse_var_def(parser);
   }
}

// parse a single chunk
tree_t* parser_parse_chunk(parser_t* parser) {
   switch (parser->token->type) {
      case TOKEN_ID: {
         return parser_parse_token_id(parser);
      }
   }
}

// parse all in list of chunks
tree_t* parser_parse_chunks(parser_t* parser) {
   // initialize the subtree to return
   tree_t* subtree = tree_init(TREE_SUBTREE);

   // initialize the subtree_val with unit size
   subtree->subtree_val = calloc(1, sizeof(struct TREE_STRUC));

   tree_t* tree_chunk = parser_parse_chunk(parser);

   subtree->subtree_val[0] = tree_chunk;

   while (parser->token->type == TOKEN_SEMI) {
      // expect semicolon
      parser_check_expect(parser, TOKEN_SEMI);

      // make room for new subtree
      subtree->subtree_size ++;
      subtree->subtree_val = realloc(
         subtree->subtree_val,
         subtree->subtree_size * sizeof(struct TREE_STRUC)
      );

      // add to end of list
      subtree->subtree_val[subtree->subtree_size - 1] = tree_chunk;
   }

   return subtree;
}

tree_t* parser_parse_expr(parser_t* parser);

tree_t* parser_parse_fac(parser_t* parser);

tree_t* parser_parse_term(parser_t* parser);

tree_t* parser_parse_fn_call(parser_t* parser);

tree_t* parser_parse_var(parser_t* parser);

tree_t* parser_parse_str(parser_t* parser);
*/

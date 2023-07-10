#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/token.h"
#include "include/util.h"
#include "include/tree.h"
#include "include/lexer.h"
#include "include/parser.h"

parser_t* parser_init(lexer_t* lexer) {
   parser_t* parser;

   parser = calloc(1, sizeof(struct PARSER_STRUC));
   parser->lexer = lexer;
   parser->token = lexer_get_next_token(lexer);

   return parser;
}

void parser_destroy(parser_t* parser) { free(parser); }

void parser_token_expect(parser_t* parser, int token) {
   token == parser->token->type?
      parser->token = lexer_get_next_token(parser->lexer):
      die(
         "unexpected token\n\ttype: [%s]\n\tvalue: [%s]", 
         token_get_type(parser->token->type),
         parser->token->value
      );
}

void parser_token_expectf(parser_t* parser, int (*expected_token)(token_t*)) {
   expected_token(parser->token)?
      parser->token = lexer_get_next_token(parser->lexer):
      die(
         "unexpected token\n\ttype: [%s]\n\tvalue: [%s]", 
         token_get_type(parser->token->type),
         parser->token->value
      );
}

tree_t* parser_parse(parser_t* parser) { return parser_parse_exprs(parser); }

tree_t* parser_parse_expr(parser_t* parser) {
   switch (parser->token->type) {
      case TOKEN_DEF_TAG:
         return parser_parse_def(parser);
         break;
      case TOKEN_KEYWORD:
         return parser_parse_call(parser);
         break;
      default:
         die("BAD TOKEN"); /* TODO: make more informative error msgs */
   }

   return NULL; /* unreachable */
                /* hopefully */
}

tree_t* parser_parse_exprs(parser_t* parser) {
   tree_t* comp;
   tree_t* statement;

   comp = tree_init(TREE_COMP);
   comp->data.comp.value = calloc(1, sizeof(struct TREE_STRUC*));

   statement = parser_parse_expr(parser);
   comp->data.comp.value[0] = statement;
   while (parser->token->type == TOKEN_STMNT_END) {
      tree_t* statement;

      parser_token_expect(parser, TOKEN_STMNT_END);

      statement = parser_parse_expr(parser);
      comp->data.comp.size += 1;
      comp->data.comp.value = realloc(
         comp->data.comp.value,
         comp->data.comp.size * sizeof(struct TREE_STRUC)
      );
      comp->data.comp.value[comp->data.comp.size - 1] = statement;
   }

   return comp;
}

tree_t* parser_parse_blocks(parser_t* parser) {

}

tree_t* parser_parse_block(parser_t* parser) {

}

tree_t* parser_parse_def(parser_t* parser) {
   tree_t* def;

   def->type = TREE_DEF;

   def->data.def.name = parser->token->value;

//   def->data.def.

   while (parser->token->type == TOKEN_DEF_TAG) {
      
   } 

}

tree_t* parser_parse_call(parser_t* parser) {
}

tree_t* parser_parse_type_str(parser_t* parser) {
   tree_t* tree;
   
   tree->type = TREE_TYPE_STR;
   tree->data.type_str.value = parser->token->value;

   return tree;
}

tree_t* parser_parse_type_int(parser_t* parser) {
   tree_t* tree;

   tree->type = TREE_TYPE_INT;
   tree->data.type_int.value = strtol(parser->token->value, NULL, 10);

   return tree;
}


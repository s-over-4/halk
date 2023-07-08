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

void parser_token_expect(parser_t* parser, token_t* token) {
   if (token == parser->token) { 
      die(
         "unexpected token!\n\ttype: [%s]\n\tvalue: [%s]", 
         token_get_type(parser->token->type),
         parser->token->value
      );
   }
}

void parser_token_expectf(parser_t* parser, int (*expected_token)(token_t*)) {
   expected_token(parser->token)?
      parser->token = lexer_get_next_token(parser->lexer):
      die(
         "unexpected token!\n\ttype: [%s]\n\tvalue: [%s]", 
         token_get_type(parser->token->type),
         parser->token->value
      );
}

tree_t* parser_parse(parser_t* parser) { return parser_parse_statements(parser); }

tree_t* parser_parse_statements(parser_t* parser) {
   tree_t* comp;
   tree_t* statement;

   comp = tree_init(TREE_COMP);
   comp->data.comp.value = calloc(1, sizeof(struct TREE_STRUC*));

   statement = parser_parse_statement(parser);

   comp->data.comp.value[0] = statement;
   comp->data.comp.size += 1; 

   while (parser->token->type == TOKEN_STMNT_END) {
      statement = parser_parse_statement(parser);

      comp->data.comp.value[0] = statement;
      comp->data.comp.size += 1; 
   }
   
   return comp;
}

tree_t* parser_parse_statement(parser_t* parser) {

}

tree_t* parser_parse_blocks(parser_t* parser) {

}

tree_t* parser_parse_block(parser_t* parser) {

}

tree_t* parser_parse_def(parser_t* parser) {
   tree_t* tree;

   tree->type = TREE_DEF;
   tree->data.def.name = parser->token->value;

   lexer_next(parser->lexer);

   tree->data.def.mutability = strcmp(parser->token->value, "mut");
   
   // collect other tags
   // check for arguments
   // wait for DEF_SET
   // return value as parse_statement (could be just one or block)

   return tree;
}

tree_t* parser_parse_call(parser_t* parser) {
   tree_t* tree;

   tree->type = TREE_CALL;
   tree->data.call.target = parser->token->value;

   lexer_next(parser->lexer);

   if (parser->token->type == TOKEN_FN_APPLY) {

      lexer_next(parser->lexer);

      tree->data.call.args = realloc(tree->data.call.args, sizeof(tree->data.call.args) + sizeof(parser->token->value));
      tree->data.call.args_size += sizeof(parser->token->value);


      lexer_next(parser->lexer);

      while (parser->token->type == TOKEN_LIST_DELIM) {
         lexer_next(parser->lexer);
         tree->data.call.args = realloc(tree->data.call.args, sizeof(tree->data.call.args) + sizeof(parser->token->value));
         tree->data.call.args_size += sizeof(parser->token->value);
         lexer_next(parser->lexer);
      }

      return tree;
   } else {
      return tree;
   }
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


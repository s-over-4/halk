#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/token.h"
#include "include/tree.h"
#include "include/util.h"
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

void parser_token_expect(parser_t* parser, int (*expected_token)(token_t*)) {
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

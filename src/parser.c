#include "include/parser.h"
#include "include/token.h"

parser_t* parser_init(token_t* token) {
   parser_t* parser;

   parser = emalloc(sizeof(struct PARSER));
   parser->token = token;
   parser->tree = NULL;

   return parser;
}

void parser_destroy(parser_t* parser) {
   free(parser);
}

int parser_nxt_token(parser_t* parser) {
   if (parser->token->nxt) {
      parser->token = parser->token->nxt;
      return 1;
   } else {
      return 0;
   }
}

int parser_match(parser_t* parser, token_type_t type) {
   return parser->token->type == type;
}

void parser_parse_lit(parser_t* parser) {
}

void parser_parser_expr(parser_t* parser) {
}

void parser_parse_blk(parser_t* parser) {
}

void parser_parse(parser_t* parser) {
}

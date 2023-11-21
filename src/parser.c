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
   if (parser->token->type == type) {
      return 1;
   } else {
      log_err("Unexpected token.");
      return 0;
   }
}

int parser_nxt_token_match(parser_t* parser, token_type_t type) {
   parser_nxt_token(parser);
   return parser_match(parser, type);
}

tree_t* parser_parse_lit(parser_t* parser) {
   tree_t* lint;

   lint = tree_init(TREE_TYPE_LINT);
   lint->data.lint.val = atoi(parser->token->val);

   return lint;
}

tree_t* parser_parse_expr(parser_t* parser) {
   tree_t* expr;

   expr = tree_init(TREE_TYPE_EXPR);

   /* For now this is the only type of expression. */
   expr->data.expr.val = parser_parse_lit(parser);

   return expr;
}

tree_t* parser_parse_block(parser_t* parser) {
   tree_t* block;

   block = tree_init(TREE_TYPE_BLOCK);

   if (parser->token->type == TOKEN_EXPR_END) {
      if (parser_nxt_token(parser)) {
         block->data.block.val = parser_parse_expr(parser);
      } else {
         block->data.block.val = NULL;
      }

      if (parser_nxt_token(parser)) {
         block->data.block.nxt = parser_parse_block(parser);
      } else {
         block->data.block.nxt = NULL;
      }

      return block;
   }

   if (parser->token) {
      block->data.block.val = parser_parse_expr(parser);
   } else {
      block->data.block.val = NULL;
   }

   if (parser_nxt_token(parser)) {
      block->data.block.nxt = parser_parse_block(parser);
   } else {
      block->data.block.nxt = NULL;
   }

   return block;
}

tree_t* parser_parse(parser_t* parser) {
   return parser_parse_block(parser);
}

void parser_run(parser_t* parser) {
   parser->tree = parser_parse(parser);
}

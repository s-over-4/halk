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

tree_t* parser_parse_lint(parser_t* parser) {
   tree_t* lint;

   lint = tree_init(TREE_TYPE_LINT);
   lint->data.lint.val = atoi(parser->token->val);

   return lint;
}

tree_t* parser_parse_lstr(parser_t* parser) {
   tree_t* lstr;

   lstr = tree_init(TREE_TYPE_LSTR);
   lstr->data.lstr.len = strlen(parser->token->val);
   lstr->data.lstr.val = ecalloc(lstr->data.lstr.len + 1, sizeof(char));
   lstr->data.lstr.val[lstr->data.lstr.len] = '\0';
   strcpy(lstr->data.lstr.val, parser->token->val);

   return lstr;
}

tree_t* parser_parse_expr(parser_t* parser) {
   tree_t* expr;

   expr = tree_init(TREE_TYPE_EXPR);

   /* For now this is the only type of expression. */

   switch (parser->token->type) {
      case TOKEN_INT:
         expr->data.expr.val = parser_parse_lint(parser);
         break;
      case TOKEN_STR:
         expr->data.expr.val = parser_parse_lstr(parser);
         break;
      default:
         return expr;
   }

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

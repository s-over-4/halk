#include "include/parser.h"
#include "include/token.h"
#include "include/tree.h"

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
   /* Swap pointers to allow for future token destruction. */
   lstr->data.lstr.val = parser->token->val;
   parser->token->val = NULL; 

   return lstr;
}

tree_t* parser_parse_expr(parser_t* parser) {
   tree_t* expr;

   expr = tree_init(TREE_TYPE_EXPR);

   switch (parser->token->type) {
      case TOKEN_INT:
         expr->data.expr.val = parser_parse_lint(parser);
         break;
      case TOKEN_STR:
         expr->data.expr.val = parser_parse_lstr(parser);
         break;
      case TOKEN_KWD:
         expr->data.expr.val = parser_parse_call(parser);
         break;
      case TOKEN_TAG:
         expr->data.expr.val = parser_parse_def(parser);
         break;
      case TOKEN_LBLOCK:
         parser_nxt_token(parser);
         expr->data.expr.val = parser_parse_block(parser);
         break;
      default:
         return expr;
   }

   return expr;
}

tree_t* parser_parse_block(parser_t* parser) {
   if (!parser->token || parser->token->type == TOKEN_EXPR_END || parser->token->type == TOKEN_RBLOCK) { return NULL; }

   tree_t* block;

   block = tree_init(TREE_TYPE_BLOCK);

   block->data.block.val = parser_parse_expr(parser);
   block->data.block.nxt = parser_nxt_token_match(parser, TOKEN_EXPR_END) && parser_nxt_token(parser) ? 
      parser_parse_block(parser) : 
      NULL;

   return block;
}

tree_t* parser_parse_tag(parser_t* parser) {
   if (parser->token->type != TOKEN_TAG) { return NULL; }

   tree_t* tag;

   tag = tree_init(TREE_TYPE_TAG);

   tag->data.tag.val = parser->token->val;
   parser->token->val = NULL;
   tag->data.tag.nxt = (parser_nxt_token(parser) ? parser_parse_tag(parser) : NULL);

   return tag;
}

tree_t* parser_parse_darg(parser_t* parser) {
   tree_t* darg;

   darg = tree_init(TREE_TYPE_DARG);

   if (parser->token->type != TOKEN_TAG) { return NULL; }

   darg->data.darg.tag = parser_parse_tag(parser);

   log_war("%d", parser->token->type);

   if (parser->token->type != TOKEN_LIST_DELIM) { darg->data.darg.nxt = NULL; }
   else { parser_nxt_token(parser) && (darg->data.darg.nxt = parser_parse_darg(parser)); }

   return darg;
}

tree_t* parser_parse_def(parser_t* parser) {
   tree_t* def;

   def = tree_init(TREE_TYPE_DEF);

   def->data.def.tag = parser_parse_tag(parser);

   parser->token->type == TOKEN_APPLY && parser_nxt_token(parser) && (def->data.def.arg = parser_parse_darg(parser));
   parser->token->type == TOKEN_SET && parser_nxt_token(parser) && (def->data.def.val = parser_parse_expr(parser));
   
   return def;
}

tree_t* parser_parse_carg(parser_t* parser) {
   tree_t* carg;

   carg = tree_init(TREE_TYPE_CARG);

   carg->data.carg.val = parser_parse_expr(parser);
   carg->data.carg.nxt = (parser_nxt_token_match(parser, TOKEN_LIST_DELIM) && parser_nxt_token(parser) ? parser_parse_carg(parser) : NULL);

   return carg;
}

tree_t* parser_parse_call(parser_t* parser) {
   tree_t* call;

   call = tree_init(TREE_TYPE_CALL);

   call->data.call.target = parser->token->val;
   parser->token->val = NULL;
   parser_nxt_token_match(parser, TOKEN_APPLY) || (call->data.call.arg = NULL);
   call->data.call.arg = (parser_nxt_token(parser) ? parser_parse_carg(parser) : NULL);

   return call;
}

tree_t* parser_parse(parser_t* parser) {
   return parser_parse_block(parser);
}

void parser_run(parser_t* parser) {
   parser->tree = parser_parse(parser);
}

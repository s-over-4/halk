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
   if (parser) { free(parser); }
}

/* TODO: What if the program begins with a ";"? */
int parser_nxt_token(parser_t* parser) {
   /* Preserve original token list, to be cleaned up by lexer. */
   if (!parser->token) { return 0; }
   parser->token = parser->token->nxt;
   if (parser->token && parser->token->type == TOKEN_TYPE_EXPR_END) {
      return parser_nxt_token(parser);
   }
   return parser->token ? 1 : 0;
}

tree_t* parser_parse_init(parser_t* parser) {
   /* There is nothing to do. */
   if (!parser->token || parser->token->type == TOKEN_TYPE_RBLOCK) {
      return NULL;
   } 
   tree_t* block;
   block = tree_init(TREE_TYPE_BLOCK);

   block->data.block.val = parser_parse_expr(parser);
   block->data.block.nxt = parser_parse_block(parser);

   return block;
}

tree_t* parser_parse_block(parser_t* parser) {
   /* There is nothing to do. */
   if (!parser->token || parser->token->type == TOKEN_TYPE_RBLOCK) {
      parser_nxt_token(parser);  /* Skip over closing bracket. */
      return NULL;
   } 
   tree_t* block;
   block = tree_init(TREE_TYPE_BLOCK);

   block->data.block.val = parser_parse_expr(parser);
   block->data.block.nxt = parser_parse_block(parser);

   parser_nxt_token(parser);  /* Skip over semicolon. */

   return block;
}

tree_t* parser_parse_expr(parser_t* parser) {
   tree_t* expr = NULL;

   switch (parser->token->type) {
      case TOKEN_TYPE_INT:
         expr = parser_parse_lint(parser);
         break;
      case TOKEN_TYPE_STR:
         expr = parser_parse_lstr(parser);
         break;
      case TOKEN_TYPE_LBLOCK:
         parser_nxt_token(parser);  /* Skip over opening curly bracket. */
         expr = parser_parse_block(parser);
         break;
      default:
         log_war("%s: Unknown token type: %d", __func__, parser->token->type);
         parser_nxt_token(parser);
   }

   return expr;
}

/* I don't know if these need to exist. Guess I'll wait and see… */
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
   parser_nxt_token(parser);

   return lint;
}

tree_t* parser_parse_lstr(parser_t* parser) {
   tree_t* lstr;

   lstr = tree_init(TREE_TYPE_LSTR);

   lstr->data.lstr.len = strlen(parser->token->val);
   /* Move token value to tree, to allow for future token destruction. */
   lstr->data.lstr.val = parser->token->val;
   parser->token->val = NULL; 
   parser_nxt_token(parser);

   return lstr;
}

tree_t* parser_parse_tag(parser_t* parser) {
   if (parser->token->type != TOKEN_TYPE_TAG) { return NULL; }

   tree_t* tag;

   tag = tree_init(TREE_TYPE_TAG);

   tag->data.tag.val = parser->token->val;
   parser->token->val = NULL;
   tag->data.tag.nxt = (
      parser_nxt_token(parser) ? 
         parser_parse_tag(parser) : 
         NULL
   );

   return tag;
}

tree_t* parser_parse_darg(parser_t* parser) {
   tree_t* darg;

   darg = tree_init(TREE_TYPE_DARG);

   if (parser->token->type != TOKEN_TYPE_TAG) { return NULL; }

   darg->data.darg.tag = parser_parse_tag(parser);

   log_war("%d", parser->token->type);

   if (parser->token->type != TOKEN_TYPE_LIST_DELIM) {
      darg->data.darg.nxt = NULL;
   } else {
      parser_nxt_token(parser) && 
         (darg->data.darg.nxt = parser_parse_darg(parser));
   }

   return darg;
}

tree_t* parser_parse_def(parser_t* parser) {
   tree_t* def;

   def = tree_init(TREE_TYPE_DEF);

   def->data.def.tag = parser_parse_tag(parser);

   parser->token->type == TOKEN_TYPE_APPLY && 
      parser_nxt_token(parser) &&
      ( def->data.def.arg = parser_parse_darg(parser) );
   parser->token->type == TOKEN_TYPE_SET && 
      parser_nxt_token(parser) && 
      ( def->data.def.val = parser_parse_expr(parser) );
   
   return def;
}

tree_t* parser_parse_carg(parser_t* parser) {
   tree_t* carg;

   carg = tree_init(TREE_TYPE_CARG);

   carg->data.carg.val = parser_parse_expr(parser);
   carg->data.carg.nxt = (
      parser_nxt_token_match(parser, TOKEN_TYPE_LIST_DELIM) && 
      parser_nxt_token(parser) 
   ) ? 
      parser_parse_carg(parser) : 
      NULL;

   return carg;
}

tree_t* parser_parse_call(parser_t* parser) {
   tree_t* call;

   call = tree_init(TREE_TYPE_CALL);

   call->data.call.target = parser->token->val;
   parser->token->val = NULL;
   call->data.call.arg = (
      parser_nxt_token_match(parser, TOKEN_TYPE_APPLY) && parser_nxt_token(parser) ?
         parser_parse_carg(parser) : 
         NULL
   );

   return call;
}

void parser_parse(parser_t* parser) {
   while (parser->token) {
      switch (parser->token->type) {
         case TOKEN_TYPE_INT:
            parser->tree->data.block.val = parser_parse_lint(parser);
            break;
      }

      parser_nxt_token(parser);
   }

}

void parser_run(parser_t* parser) {
   parser->tree = parser_parse_block(parser);
}

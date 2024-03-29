#include "include/parser.h"
#include "include/token.h"
#include "include/util.h"

parser_t* parser_init(token_t* token) {
   parser_t* parser;

   parser = emalloc(sizeof(struct PARSER));
   parser->token = token;
   parser->tree = NULL;
   parser->ltree = NULL;

   return parser;
}

void parser_destroy(parser_t* parser) {
   if (parser) { free(parser); }
}

int parser_nxt_token(parser_t* parser) {
   /* Preserve original token list, to be cleaned up by lexer. */
   if (!parser->token) { return 0; }
   parser->token = parser->token->nxt;
   if (parser->token && parser->token->type == TOKEN_TYPE_EXPR_END) {
      return parser_nxt_token(parser);
   }
   return parser->token ? 1 : 0;
}

#if 0 /* TODO: This seems like it might be useful??
tree_t* parser_parse_init(parser_t* parser) {
   /* There is nothing to do. */
   if (!parser->token) {
      return NULL;
   } 

   tree_t* block;
   block = tree_init(TREE_TYPE_BLOCK, NULL);

   block->data.block.val = parser_parse_expr(parser);
   block->data.block.nxt = parser_parse_block(parser);

   return block;
}
#endif

tree_t* parser_parse_block(parser_t* parser) {
   /* There is nothing to do. */
   if (!parser->token || parser->token->type == TOKEN_TYPE_RBLOCK) {
      (void) parser_nxt_token(parser); /* Skip over closing bracket. */
      return NULL;
   } 

   tree_t* block;
   block = tree_init(TREE_TYPE_BLOCK, parser->ltree);

   parser->ltree = block;
   block->data.block.val = parser_parse_expr(parser);

   parser->ltree = block;
   block->data.block.nxt = parser_parse_block(parser);

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
         /* TODO: Move this into parser_parse_block, parser_parse_init exists
          * now. */
         parser_nxt_token(parser);  /* Skip over opening curly bracket. */
         expr = parser_parse_block(parser);
         break;
      case TOKEN_TYPE_KWD:
         expr = parser_parse_call(parser);
         break;
      case TOKEN_TYPE_TAG:
         expr = parser_parse_def(parser);
         break;
      default:
         LOG_WARF("%s: Unknown token type: %d", __func__, parser->token->type);
         parser_nxt_token(parser);
   }

   return expr;
}

tree_t* parser_parse_def(parser_t* parser) {
   tree_t* def = tree_init(TREE_TYPE_DEF, parser->ltree);

   parser->ltree = def;
   def->data.def.tag = parser_parse_tag(parser);

   if (parser->token->type == TOKEN_TYPE_APPLY) {
      parser_nxt_token(parser);  /* Skip over apply. */

      parser->ltree = def;
      def->data.def.arg = parser_parse_darg(parser);
   } else {
      def->data.def.arg = NULL;
   }

   if (parser->token->type == TOKEN_TYPE_SET) {
      parser_nxt_token(parser);  /* Skip over set. */

      parser->ltree = def;
      def->data.def.val = parser_parse_expr(parser);
   } else {
      def->data.def.val = NULL;
   }

   return def;
}

tree_t* parser_parse_tag(parser_t* parser) {
   if (
      parser->token && 
      parser->token->type != TOKEN_TYPE_TAG
   ) { return NULL; }

   tree_t* tag = tree_init(TREE_TYPE_TAG, parser->ltree);

   tag->data.tag.val = parser->token->val;
   parser->token->val = NULL;

   parser_nxt_token(parser);

   parser->ltree = tag;
   tag->data.tag.nxt = parser_parse_tag(parser);

   return tag;
}

tree_t* parser_parse_darg(parser_t* parser) {
   tree_t* darg = tree_init(TREE_TYPE_DARG, parser->ltree);

   parser->ltree = darg;
   darg->data.darg.tag = parser_parse_tag(parser);
   
   if (parser->token->type == TOKEN_TYPE_LIST_DELIM) {
      parser_nxt_token(parser);  /* Skip over list delim. */

      parser->ltree = darg;
      darg->data.darg.nxt = parser_parse_darg(parser);
   } else {
      darg->data.darg.nxt = NULL;
   }

   return darg;
}

tree_t* parser_parse_carg(parser_t* parser) {
   tree_t* carg;

   carg = tree_init(TREE_TYPE_CARG, parser->ltree); 

   parser->ltree = carg;
   carg->data.carg.val = parser_parse_expr(parser);

   if (
      parser->token
      && parser->token->type == TOKEN_TYPE_LIST_DELIM
      && parser_nxt_token(parser)
   ) {
      parser->ltree = carg;
      carg->data.carg.nxt = parser_parse_carg(parser);
   } else {
      carg->data.carg.nxt = NULL;
   }

   return carg;
}

tree_t* parser_parse_kwd(parser_t* parser) {
   tree_t* call;

   call = tree_init(TREE_TYPE_CALL, parser->ltree);

   call->data.call.target = parser->token->val;
   parser->token->val = NULL;

   /* Skip over keyword, check for arguments. */
   if (
      parser_nxt_token(parser) &&
      parser->token->type == TOKEN_TYPE_APPLY
   ) {
      /* Expect some arguments. */
      parser_nxt_token(parser);

      parser->ltree = call;
      call->data.call.arg = parser_parse_carg(parser);
   } else {
      /* There're no arguments. */
      call->data.call.arg = NULL;
   }

   return call;
}

/* I don't know if these need to exist. Guess I'll wait and see… */
int parser_match(parser_t* parser, token_type_t type) {
   return parser->token ? parser->token->type == type : 0;
}

int parser_nxt_token_match(parser_t* parser, token_type_t type) {
   parser_nxt_token(parser);
   return parser_match(parser, type);
}

tree_t* parser_parse_lint(parser_t* parser) {
   tree_t* lint;

   lint = tree_init(TREE_TYPE_LINT, parser->ltree);
   lint->data.lint.val = atoi(parser->token->val);
   parser_nxt_token(parser);

   return lint;
}

tree_t* parser_parse_lstr(parser_t* parser) {
   tree_t* lstr;

   lstr = tree_init(TREE_TYPE_LSTR, parser->ltree);

   lstr->data.lstr.len = strlen(parser->token->val);
   /* Move token value to tree, to allow for future token destruction. */
   lstr->data.lstr.val = parser->token->val;
   parser->token->val = NULL; 
   parser_nxt_token(parser);

   return lstr;
}

tree_t* parser_parse_call(parser_t* parser) {
   tree_t* call;

   call = tree_init(TREE_TYPE_CALL, parser->ltree);

   call->data.call.target = parser->token->val;
   parser->token->val = NULL;

   /*
      If there's a call with an apply, but the file ends just after, NULL.
      ¯\_(ツ)_/¯ 
   */
   if (
      parser_nxt_token(parser)
      && parser->token->type == TOKEN_TYPE_APPLY
      && parser_nxt_token(parser)
   ) {
      parser->ltree = call;
      call->data.call.arg = parser_parse_carg(parser);
   } else {
      call->data.call.arg = NULL;
   }

   return call;
}

#if 0 /* ??? */
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
#endif

void parser_run(parser_t* parser) {
   parser->ltree = NULL;
   parser->tree = parser_parse_block(parser);
}

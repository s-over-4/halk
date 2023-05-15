#include "include/parser.h"
#include "include/token.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
      fprintf(stderr, "[ERRR] [%d]\n\tUnexpected token '%s' with type '%d'.", 
      parser->lexer->i, parser->token->value, parser->token->type);

      exit(1);
   }
}

// creates the abstract syntax tree
tree_t* parser_parse(parser_t* parser) {
   return parser_parse_chunks(parser);
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
      case TOKEN_KEYWORD: {
         return parser_parse_keyword(parser);
         break;
      }
      default: {
         fputs("smthn smthn \"invalid syntax,\" idk.", stderr);
         exit(1);
      }
   }
}

tree_t* parser_parse_chunks(parser_t* parser) {
   tree_t* subtree = tree_init(TREE_SUBTREE);
   subtree->data.subtree.val = calloc(1, sizeof(struct TREE_STRUC));

   tree_t* chunk = parser_parse_chunk(parser);
   subtree->data.subtree.val[0] = chunk;

   while (parser->token->type == TOKEN_END) {
      parser_check_expect(parser, TOKEN_END);

      tree_t* chunk = parser_parse_chunk(parser);
      subtree->data.subtree.size += 1;
      subtree->data.subtree.val = realloc(
            subtree->data.subtree.val, 
            subtree->data.subtree.size * sizeof(struct TREE_STRUC)
      );
      subtree->data.subtree.val[subtree->data.subtree.size - 1] = chunk;
      
   }

   return subtree;
}

tree_t* parser_parse_expr(parser_t* parser) {};

tree_t* parser_parse_fac(parser_t* parser) {};

tree_t* parser_parse_term(parser_t* parser) {};

tree_t* parser_parse_fn_call(parser_t* parser) {};

tree_t* parser_parse_fn_def(parser_t* parser) {};

tree_t* parser_parse_var(parser_t* parser) {};

tree_t* parser_parse_var_def(parser_t* parser) {
   int var_is_const = 0;
   parser_check_expect(parser, TOKEN_KEYWORD);        // let
   char* var_name = parser->token->value;             // set variable name
   parser_check_expect(parser, TOKEN_KEYWORD);        // expect variable name & advance

   if (parser->token->type == TOKEN_DEFINE_CONST) {   // check either constant or mutable variable
      var_is_const = 1;
      parser_check_expect(parser, TOKEN_DEFINE_CONST);
   } else {
      parser_check_expect(parser, TOKEN_DEFINE_MUT);
   }

   tree_t* var_val = parser_parse_expr(parser);       // set the value
   tree_t* var_def = tree_init(TREE_VAR_DEF);         // create the var

   var_def->data.var_def.name = var_name;
   var_def->data.var_def.val = var_val;
   var_def->data.var_def.is_const = &var_is_const;

   return var_def;
};

tree_t* parser_parse_str(parser_t* parser) {};

tree_t* parser_parse_keyword(parser_t* parser) {
   if (strcmp(parser->token->value, "let")) {
      return parser_parse_var_def(parser);
   } else if (strcmp(parser->token->value, "fn")) {
      return parser_parse_fn_def(parser);
   } else {
      return parser_parse_var(parser);
   }
}


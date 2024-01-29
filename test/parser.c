#include "include/test.h"
#include "../src/include/pp.h"
#include "../src/include/lexer.h"
#include "../src/include/tree.h"
#include "../src/include/parser.h"

TEST_INIT

void empty() {
   /* 
      Hmm… I feel as though this setup/cleanup process could be wrapped in a 
      macro. Tentative TODO?
   */
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "";

   /*

      NULL

   */

   tree = NULL;
   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   /* Probably not cleaning up fully here. Whatever. */
   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void single_lint() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "1";

   /*

      [block]
      val:
         [lint]
         val:
            1
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree->data.block.val = tree_init(TREE_TYPE_LINT);
         tree->data.block.val->data.lint.val = 1;
      tree->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void double_lint() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "1;1";

   /*

      [block]
      val:
         [lint]
         val:
            1
      nxt:
         [block]
         val:
            [lint]
            val:
               1
         nxt:
            NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0lint = tree->data.block.val = tree_init(TREE_TYPE_LINT);
         tree0lint->data.lint.val = 1;
      tree_t* tree1block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree2lint = tree1block->data.block.val = tree_init(TREE_TYPE_LINT);
            tree2lint->data.lint.val = 1;
         tree1block->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void single_lstr() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "\"Hello, World.\"";

   /*

      [block]
      val:
         [lstr]
         val:
            "Hello, World."
         len:
            13
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0lstr = tree->data.block.val = tree_init(TREE_TYPE_LSTR);
         tree0lstr->data.lstr.val = "Hello, World.";
         tree0lstr->data.lstr.len = 13;
      tree->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void double_lstr() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "\"foo\";\"bar\"";

   /*

      [block]
      val:
         [lstr]
         val:
            "foo"
         len:
            3
      nxt:
         [block]
         val:
            [lstr]
            val:
               "bar"
            len:
               3
         nxt:
            NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0lstr = tree->data.block.val = tree_init(TREE_TYPE_LSTR);
         tree0lstr->data.lstr.val = "foo";
         tree0lstr->data.lstr.len = 3;
      tree_t* tree0block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree1lstr = tree0block->data.block.val = tree_init(TREE_TYPE_LSTR);
            tree1lstr->data.lstr.val = "bar";
            tree1lstr->data.lstr.len = 3;
         tree0block->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void single_block() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "{1}";

   /*

      [block]
      val:
         [block]
         val:
            [lint]
            val:
               1
         nxt:
            NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0block = tree->data.block.val = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree0lint = tree0block->data.block.val = tree_init(TREE_TYPE_LINT);
            tree0lint->data.lint.val = 1;
         tree0block->data.block.nxt = NULL;
      tree->data.block.nxt = NULL;


   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void lint_and_block() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "1;{1}";

   /*

      [block]
      val:
         [lint]
         val:
            1
      nxt:
         [block]
         val:
            [block]
            val:
               [lint]
               val:
                  1
            nxt:
               NULL
         nxt:
            NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0lint = tree->data.block.val = tree_init(TREE_TYPE_LINT);
         tree0lint->data.lint.val = 1;
      tree_t* tree0block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree1block = tree0block->data.block.val = tree_init(TREE_TYPE_BLOCK);
            tree_t* tree1lint = tree1block->data.block.val = tree_init(TREE_TYPE_LINT);
               tree1lint->data.lint.val = 1;
            tree1block->data.block.nxt = NULL;
         tree0block->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

int main() {
   empty();
   single_lint();
   double_lint();
   single_lstr();
   double_lstr();
   single_block();
   lint_and_block();

   TEST_REPORT;

   return 0;
}

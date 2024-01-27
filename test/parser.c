#include "include/test.h"
#include "../src/include/pp.h"
#include "../src/include/lexer.h"
#include "../src/include/tree.h"
#include "../src/include/parser.h"

TEST_INIT

void test_simple_empty() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = " ";

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

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
}

void test_single_lint() {
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

void test_double_lint() {
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

int main(int argc, char** argv) {
   test_simple_empty();
   test_single_lint();
   test_double_lint();

   TEST_REPORT;

   return 0;
}

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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
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
         char* str0 = tree0lstr->data.lstr.val = ecalloc(14, sizeof(char));
            strcpy(str0, "Hello, World.");
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
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
         char* str0 = tree0lstr->data.lstr.val = ecalloc(4, sizeof(char));
            strcpy(str0, "foo");
         tree0lstr->data.lstr.len = 3;
      tree_t* tree0block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree1lstr = tree0block->data.block.val = tree_init(TREE_TYPE_LSTR);
            char* str1 = tree1lstr->data.lstr.val = ecalloc(4, sizeof(char));
               strcpy(str1, "bar");
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void lint_and_block() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "1{1}";

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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void double_block() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "{1}{2}";

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
         [block]
         val:
            [block]
            val:
               [lint]
               val:
                  2
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
      tree_t* tree1block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree2block = tree1block->data.block.val = tree_init(TREE_TYPE_BLOCK);
            tree_t* tree1lint = tree2block->data.block.val = tree_init(TREE_TYPE_LINT);
               tree1lint->data.lint.val = 2;
            tree2block->data.block.nxt = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void nested_block() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "{1;2}";

   /*

      [block]
      val:
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
                  2
            nxt:
               NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0block = tree->data.block.val = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree0lint = tree0block->data.block.val = tree_init(TREE_TYPE_LINT);
            tree0lint->data.lint.val = 1;
         tree_t* tree1block = tree0block->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
            tree_t* tree1lint = tree1block->data.block.val = tree_init(TREE_TYPE_LINT);
               tree1lint->data.lint.val = 2;
            tree1block->data.block.nxt = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void superfluous_semicolons() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "{;;;;;\"Hello\";;;;;;;;;;;};;;\"World\";;;;;;;;";

   /*

      [block]
      val:
         [block]
         val:
            [lstr]
            val:
               Hello
            len:
               5
         nxt:
            NULL
      nxt:
         [block]
         val:
            [lstr]
            val:
               World
            len:
               5
         nxt:
            NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0block = tree->data.block.val = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree0lstr = tree0block->data.block.val = tree_init(TREE_TYPE_LSTR);
            char* str0 = tree0lstr->data.lstr.val = ecalloc(6, sizeof(char));
               strcpy(str0, "Hello");
            tree0lstr->data.lstr.len = 5;
         tree_t* tree1block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
            tree_t* tree1lstr = tree1block->data.block.val = tree_init(TREE_TYPE_LSTR);
               char* str1 = tree1lstr->data.lstr.val = ecalloc(6, sizeof(char));
                  strcpy(str1, "World");
            tree1lstr->data.lstr.len = 5;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void bare_call() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "f";

   /*

      [block]
      val:
         [call]
         target:
            f
         arg:
            NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0call = tree->data.block.val = tree_init(TREE_TYPE_CALL);
         char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
            strcpy(target0, "f");
         tree0call->data.call.arg = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void double_bare_call() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "f;g";

   /*

      [block]
      val:
         [call]
         target:
            f
         arg:
            NULL
      nxt:
         [block]
         val:
            [call]
            target:
               g
            arg:
               NULL
         nxt:
            NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0call = tree->data.block.val = tree_init(TREE_TYPE_CALL);
         char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
            strcpy(target0, "f");
         tree0call->data.call.arg = NULL;
      tree_t* tree1block = tree->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
         tree_t* tree1call = tree1block->data.block.val = tree_init(TREE_TYPE_CALL);
            char* target1 = tree1call->data.call.target = ecalloc(2, sizeof(char));
               strcpy(target1, "g");
            tree1call->data.call.arg = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void cargumented_call_of_call() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "f.x";

   /*

      [block]
      val:
         [call]
         target:
            f
         arg:
            [carg]
            val:
               [call]
               target:
                  x
               arg:
                  NULL
            nxt:
               NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0call = tree->data.block.val = tree_init(TREE_TYPE_CALL);
         char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
            strcpy(target0, "f");
         tree_t* tree0carg = tree0call->data.call.arg = tree_init(TREE_TYPE_CARG);
            tree_t* tree1call = tree0carg->data.carg.val = tree_init(TREE_TYPE_CALL);
               char* target1 = tree1call->data.call.target = ecalloc(2, sizeof(char));
                  strcpy(target1, "x");
               tree1call->data.call.arg = NULL;
            tree0carg->data.carg.nxt = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void cargumented_call_of_lint() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "f.5";

   /*

      [block]
      val:
         [call]
         target:
            f
         arg:
            [carg]
            val:
               [lint]
               val:
                  5
            nxt:
               NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0call = tree->data.block.val = tree_init(TREE_TYPE_CALL);
         char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
            strcpy(target0, "f");
         tree_t* tree0carg = tree0call->data.call.arg = tree_init(TREE_TYPE_CARG);
            tree_t* tree0lint = tree0carg->data.carg.val = tree_init(TREE_TYPE_LINT);
               tree0lint->data.lint.val = 5;
            tree0carg->data.carg.nxt = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void call_many_arg() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = "f.x,y,z";

   /*

      [block]
      val:
         [call]
         target:
            f
         arg:
            [carg]
            val:
               [call]
               target:
                  x
               arg:
                  NULL
            nxt:
               [carg]
               val:
                  [call]
                  target:
                     y
                  arg:
                     NULL
               nxt:
                  [carg]
                  val:
                     [call]
                     target:
                        z
                     arg:
                        NULL
                  nxt:
                     NULL
            nxt:
               NULL
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0call = tree->data.block.val = tree_init(TREE_TYPE_CALL);
         char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
            strcpy(target0, "f");
         tree_t* tree0carg = tree0call->data.call.arg = tree_init(TREE_TYPE_CARG);
            tree_t* tree1call = tree0carg->data.carg.val = tree_init(TREE_TYPE_CALL);
               char* target1 = tree1call->data.call.target = ecalloc(2, sizeof(char));
                  strcpy(target1, "x");
               tree1call->data.call.arg = NULL;
            tree_t* tree1carg = tree0carg->data.carg.nxt = tree_init(TREE_TYPE_CARG);
               tree_t* tree2call = tree1carg->data.carg.val = tree_init(TREE_TYPE_CALL);
                  char* target2 = tree2call->data.call.target = ecalloc(2, sizeof(char));
                     strcpy(target2, "y");
                  tree2call->data.call.arg = NULL;
               tree_t* tree2carg = tree1carg->data.carg.nxt = tree_init(TREE_TYPE_CARG);
                  tree_t* tree3call = tree2carg->data.carg.val = tree_init(TREE_TYPE_CALL);
                     char* target3 = tree3call->data.call.target = ecalloc(2, sizeof(char));
                        strcpy(target3, "z");
                     tree3call->data.call.arg = NULL;
                  tree2carg->data.carg.nxt = NULL;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void def_bare_lint() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = ":i:n = 3";

   /*

      [block]
      val:
         [def]
         tag:
            [tag]
            val:
               i
            nxt:
               [tag]
               val:
                  n
               nxt:
                  NULL
         arg:
            NULL
         val:
            [lint]
            val:
               3
      nxt:
         NULL

   */

   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0def = tree->data.block.val = tree_init(TREE_TYPE_DEF);
         tree_t* tree0tag = tree0def->data.def.tag = tree_init(TREE_TYPE_TAG);
            char* val0 = tree0tag->data.tag.val = ecalloc(2, sizeof(char));
               strcpy(val0, "i");
            tree_t* tree1tag = tree0tag->data.tag.nxt = tree_init(TREE_TYPE_TAG);
               char* val1 = tree1tag->data.tag.val = ecalloc(2, sizeof(char));
                  strcpy(val1, "n");
               tree1tag->data.tag.nxt = NULL;
         tree0def->data.def.arg = NULL;
         tree_t* tree0lint = tree0def->data.def.val = tree_init(TREE_TYPE_LINT);
            tree0lint->data.lint.val = 3;
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
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

void def_with_arg() {
   tree_t* tree;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   char src[] = ":i:f.:i:x=x";

   /*
      [block]
      val:
         [def]
         tag:
            [tag]
            val:
               i
            nxt:
               [tag]
               val:
                  f
               nxt:
                  NULL
         arg:
            [darg]
            tag:
               [tag]
               val:
                  i
               nxt:
                  [tag]
                  val:
                     x
                  nxt:
                     NULL
            nxt:
               NULL
         val:
            [call]
            target:
               x
            arg:
               NULL
      nxt:
         NULL
   */

   /* TODO: Write this test. */
   tree = tree_init(TREE_TYPE_BLOCK);
      tree_t* tree0def = tree->data.block.val = tree_init(TREE_TYPE_DEF);
         tree_t* tree0tag = tree0def->data.def.tag = tree_init(TREE_TYPE_TAG);
            char* val0 = tree0tag->data.tag.val = ecalloc(2, sizeof(char));
               strcpy(val0, "i");
            tree_t* tree1tag = tree0tag->data.tag.nxt = tree_init(TREE_TYPE_TAG);
               char* val1 = tree1tag->data.tag.val = ecalloc(2, sizeof(char));
                  strcpy(val1, "f");
               tree1tag->data.tag.nxt = NULL;
         tree_t* tree0arg = tree0def->data.def.arg = tree_init(TREE_TYPE_DARG);
            tree_t* tree2tag = tree0arg->data.darg.tag = tree_init(TREE_TYPE_TAG);
               char* val2 = tree2tag->data.tag.val = ecalloc(2, sizeof(char));
                  strcpy(val2, "i");
               tree_t* tree3tag = tree2tag->data.tag.nxt = tree_init(TREE_TYPE_TAG);
                  char* val3 = tree3tag->data.tag.val = ecalloc(2, sizeof(char));
                     strcpy(val3, "x");
                  tree3tag->data.tag.nxt = NULL;
         tree_t* tree0call = tree0def->data.def.val = tree_init(TREE_TYPE_CALL);
            char* target0 = tree0call->data.call.target = ecalloc(2, sizeof(char));
               strcpy(target0, "x");
            tree0call->data.call.arg = NULL;
      tree->data.block.nxt = NULL;

   pp = pp_init(src);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(parser->tree, tree) == 1);

   tree_print(tree, 0);
   tree_print(parser->tree, 0);

   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   free(pp->psrc);
   pp_destroy(pp);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   tree_destroy(tree);
}

int main() {
   empty();
   single_lint();
   double_lint();
   single_lstr();
   double_lstr();
   single_block();
   lint_and_block();
   double_block();
   nested_block();
   superfluous_semicolons();
   bare_call();
   double_bare_call();
   cargumented_call_of_call();
   cargumented_call_of_lint();
   call_many_arg();
   def_bare_lint();
   def_with_arg();

   TEST_REPORT;

   return 0;
}

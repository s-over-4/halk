#include "include/test.h"
#include "../src/include/pp.h"
#include "../src/include/lexer.h"
#include "../src/include/tree.h"

unsigned int TESTS_RUN = 0, TESTS_PASSED = 0;

int main(int argc, char** argv) {
   tree_t* tree_0;
   tree_t* tree_1;

   tree_t* tree_lint_0;
   tree_t* tree_lint_1;
   tree_t* tree_lstr_0;
   tree_t* tree_lstr_1;
   tree_t* tree_tag_0;
   tree_t* tree_tag_1;
   tree_t* tree_def_0;
   tree_t* tree_def_1;
   tree_t* tree_carg_0;
   tree_t* tree_carg_1;
   tree_t* tree_call_0;
   tree_t* tree_call_1;
   tree_t* tree_call_2;
   tree_t* tree_block_0;
   tree_t* tree_block_1;
   tree_t* tree_block_2;
   tree_t* tree_block_3;
   tree_t* tree_expr_0;
   tree_t* tree_expr_1;
   tree_t* tree_expr_2;

   tree_0 = tree_init(TREE_TYPE_EXPR);
   tree_1 = tree_init(TREE_TYPE_BLOCK);

   tree_lint_0 = tree_init(TREE_TYPE_LINT);
   tree_lint_1 = tree_init(TREE_TYPE_LINT);
   tree_lstr_0 = tree_init(TREE_TYPE_LSTR);
   tree_lstr_1 = tree_init(TREE_TYPE_LSTR);
   tree_tag_0 = tree_init(TREE_TYPE_TAG);
   tree_tag_1 = tree_init(TREE_TYPE_TAG);
   tree_carg_0 = tree_init(TREE_TYPE_CARG);
   tree_carg_1 = tree_init(TREE_TYPE_CARG);
   tree_call_0 = tree_init(TREE_TYPE_CALL);
   tree_call_1 = tree_init(TREE_TYPE_CALL);
   tree_call_2 = tree_init(TREE_TYPE_CALL);
   tree_block_0 = tree_init(TREE_TYPE_BLOCK);
   tree_block_1 = tree_init(TREE_TYPE_BLOCK);
   tree_block_2 = tree_init(TREE_TYPE_BLOCK);
   tree_block_3 = tree_init(TREE_TYPE_BLOCK);
   tree_expr_0 = tree_init(TREE_TYPE_EXPR);
   tree_expr_1 = tree_init(TREE_TYPE_EXPR);
   tree_expr_2 = tree_init(TREE_TYPE_EXPR);

   /* Simple cases with nonexistent trees. */
      ASSERT(tree_cmp(NULL, tree_0) == 0);
      ASSERT(tree_cmp(tree_0, NULL) == 0);
      ASSERT(tree_cmp(NULL, NULL) == 1);

   /* Test tree types. */
      ASSERT(tree_cmp(tree_0, tree_0) == 1);
      ASSERT(tree_cmp(tree_0, tree_1) == 0);

   /* Test lints. */
      tree_lint_0->data.lint.val = 0;
      tree_lint_1->data.lint.val = 1;
      ASSERT(tree_cmp(tree_lint_0, tree_lint_0) == 1);
      ASSERT(tree_cmp(tree_lint_0, tree_lint_1) == 0);

   /* Test lstrs. */
      tree_lstr_0->data.lstr.val = "foo";
      tree_lstr_0->data.lstr.len = 3;
      tree_lstr_1->data.lstr.val = "bar";
      tree_lstr_1->data.lstr.len = 3;
      ASSERT(tree_cmp(tree_lstr_0, tree_lstr_0) == 1);
      ASSERT(tree_cmp(tree_lstr_0, tree_lstr_1) == 0);
      tree_lstr_1->data.lstr.val = "barr";
      tree_lstr_1->data.lstr.len = 4;
      ASSERT(tree_cmp(tree_lstr_0, tree_lstr_1) == 0);

   /* Test tags. */
      tree_tag_0->data.tag.val = "int";
      tree_tag_0->data.tag.nxt = NULL;
      tree_tag_1->data.tag.val = "str";
      tree_tag_1->data.tag.nxt = NULL;
      ASSERT(tree_cmp(tree_tag_0, tree_tag_0) == 1);
      ASSERT(tree_cmp(tree_tag_0, tree_tag_1) == 0);
      tree_tag_1->data.tag.nxt = tree_tag_0;
      ASSERT(tree_cmp(tree_tag_0, tree_tag_1) == 0);
      ASSERT(tree_cmp(tree_tag_0, tree_tag_1->data.tag.nxt) == 1);

   /* Test calls without arguments. */
      tree_call_0->data.call.arg = NULL;
      tree_call_0->data.call.target = "foo";
      tree_call_1->data.call.arg = NULL;
      tree_call_1->data.call.target = "bar";
      ASSERT(tree_cmp(tree_call_0, tree_call_0) == 1);
      ASSERT(tree_cmp(tree_call_0, tree_call_1) == 0);

   /* Test calls with one argument. */
      tree_lint_0->data.lint.val = 42;
      tree_expr_0->data.expr.val = tree_lint_0;
      tree_carg_0->data.carg.val = tree_expr_0;
      tree_carg_0->data.carg.nxt = NULL;

      tree_call_0->data.call.arg = tree_carg_0;
      tree_call_0->data.call.target = "foo";

      tree_call_1->data.call.arg = NULL;
      tree_call_1->data.call.target = "foo";

      /* Call with 1 arguments vs call without arguments. */
      ASSERT(tree_cmp(tree_call_0, tree_call_0) == 1);
      ASSERT(tree_cmp(tree_call_0, tree_call_1) == 0);

      tree_lint_1->data.lint.val = 43;
      tree_expr_1->data.expr.val = tree_lint_1;
      tree_carg_1->data.carg.val = tree_expr_1;
      tree_carg_1->data.carg.nxt = NULL;

      tree_call_1->data.call.arg = tree_carg_1;
      tree_call_1->data.call.target = "foo";

      /* Calls each with a different single argument of the same type. */
      ASSERT(tree_cmp(tree_call_1, tree_call_1) == 1);
      ASSERT(tree_cmp(tree_call_0, tree_call_1) == 0);

   /* Test simple blocks with 1 expression. */
      /* Equivalent halk code:
         {
            foo;
         }
      */
      tree_call_0->data.call.arg = NULL;
      tree_call_0->data.call.target = "foo";
      tree_expr_0->data.expr.val = tree_call_0;
      tree_block_0->data.block.val = tree_expr_0;
      tree_block_0->data.block.nxt = NULL;

      /* 
         Equivalent halk code: 
         {}
      */
      tree_block_1->data.block.val = NULL;
      tree_block_1->data.block.nxt = NULL;

      ASSERT(tree_cmp(tree_block_0, tree_block_0) == 1); 
      ASSERT(tree_cmp(tree_block_0, tree_block_1) == 0); 

      /*
         Equivalent halk code:
         {
            bar;
         }
      */
      tree_call_1->data.call.arg = NULL;
      tree_call_1->data.call.target = "bar";
      tree_expr_1->data.expr.val = tree_call_1;
      tree_block_1->data.block.val = tree_expr_1;
      tree_block_1->data.block.nxt = NULL;

      ASSERT(tree_cmp(tree_block_1, tree_block_1) == 1);
      ASSERT(tree_cmp(tree_block_0, tree_block_1) == 0);

   /* Blocks with multiple expressions. */
      /*
         Equivalent halk code:
         {
            foo;
            foo;
         }
      */

      tree_call_0->data.call.arg = NULL;
      tree_call_0->data.call.target = "foo";
      tree_expr_0->data.expr.val = tree_call_0;

      tree_block_0->data.block.val = tree_expr_0;
      tree_block_1->data.block.val = tree_expr_0;
      tree_block_1->data.block.nxt = NULL;
      tree_block_0->data.block.nxt = tree_block_1;

      ASSERT(tree_cmp(tree_block_0, tree_block_0) == 1);      
      /* {foo;} vs {foo; foo;} */
      ASSERT(tree_cmp(tree_block_1, tree_block_0) == 0);      

      /*
         Equivalent halk code:
         {
            bar;
            foo;
         }
      */
      tree_block_2->data.block.val = tree_expr_1;
      tree_block_2->data.block.nxt = tree_block_1;

      ASSERT(tree_cmp(tree_block_2, tree_block_2) == 1);
      /* {bar; foo;} vs {foo; foo;} */
      ASSERT(tree_cmp(tree_block_2, tree_block_0) == 0);

      /*
         Equivalent halk code:
         {
            foo;
            bar;
         }
      */

      tree_call_1->data.call.arg = NULL;
      tree_call_1->data.call.target = "bar";
      tree_expr_1->data.expr.val = tree_call_1;

      tree_block_2->data.block.val = tree_expr_1;
      tree_block_3->data.block.val = tree_expr_0;
      tree_block_3->data.block.nxt = tree_block_2;
      tree_block_2->data.block.nxt = NULL;

      ASSERT(tree_cmp(tree_block_2, tree_block_2) == 1);
      /* {bar;} vs {foo; bar;} */
      ASSERT(tree_cmp(tree_block_2, tree_block_3) == 0);
      /* {foo; foo;} vs {foo; bar;} */
      ASSERT(tree_cmp(tree_block_0, tree_block_3) == 0);

   /* Test some more complicated trees. */
      tree_call_2->data.call.arg = NULL;
      tree_call_2->data.call.target = "x";
      tree_expr_2->data.expr.val = tree_call_2;
      tree_carg_0->data.carg.val = tree_expr_2;
      tree_call_0->data.call.arg = tree_carg_0;
      tree_call_0->data.call.target = "foo";
      tree_expr_0->data.expr.val = tree_call_0;
      tree_block_0->data.block.val = tree_expr_0;
      tree_block_0->data.block.nxt = NULL;

      tree_call_1->data.call.arg = NULL;
      tree_call_1->data.call.target = "bart";
      tree_expr_1->data.expr.val = tree_call_1;
      tree_block_1->data.block.val = tree_expr_1;
      tree_block_1->data.block.nxt = tree_block_0;

      ASSERT(tree_cmp(tree_block_0, tree_block_0) == 1);
      ASSERT(tree_cmp(tree_block_0, tree_block_1) == 0);

   TEST_REPORT;
   return 0;
}

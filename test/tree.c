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
   tree_t* tree_call_0;
   tree_t* tree_call_1;

   tree_0 = tree_init(TREE_TYPE_EXPR);
   tree_1 = tree_init(TREE_TYPE_BLOCK);

   tree_lint_0 = tree_init(TREE_TYPE_LINT);
   tree_lint_1 = tree_init(TREE_TYPE_LINT);
   tree_lstr_0 = tree_init(TREE_TYPE_LSTR);
   tree_lstr_1 = tree_init(TREE_TYPE_LSTR);
   tree_tag_0 = tree_init(TREE_TYPE_TAG);
   tree_tag_1 = tree_init(TREE_TYPE_TAG);
   tree_def_0 = tree_init(TREE_TYPE_DEF);
   tree_def_1 = tree_init(TREE_TYPE_DEF);
   tree_call_0 = tree_init(TREE_TYPE_CALL);
   tree_call_1 = tree_init(TREE_TYPE_CALL);

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

   TEST_REPORT;
   return 0;
}

#include "include/doer.h"


/* Creates a new doer from a tree.  */
doer_t* doer_init(tree_t* tree) {
   doer_t* doer;

   doer = emalloc(sizeof(doer_t));

   doer->tree = tree;

   return doer;
}

/*
   Destroys a doer.
   - Does not destroy the `tree`.
*/
void doer_destroy(doer_t* doer) {
   free(doer);
}


void doer_do_blin_print(char* s) {

}

void doer_do_block(tree_t* tree) {
   tree->data.block.val 
}

void doer_do_expr(tree_t* tree) {
   /* For now, assume the only expression that exists is a call to print(). */

   

}

void doer_do_lint(tree_t* tree) {

}

void doer_do_lstr(tree_t* tree) {

}

void doer_do_tag(tree_t* tree) {

}

void doer_do_darg(tree_t* tree) {

}

void doer_do_carg(tree_t* tree) {

}

void doer_do_def(tree_t* tree) {

}

void doer_do_call(tree_t* tree) {

}


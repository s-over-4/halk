#ifndef DOER_H
#define DOER_H

#include "util.h"
#include "tree.h"

/* Doer? I 'ardly know 'er! */
typedef struct DOER {
   tree_t* tree;
} doer_t;

/* Creates a new parser. */
doer_t* doer_init(tree_t* tree);

/*
   Destroys a doer.
   - Does not free the `tree`.
*/
void doer_destroy(doer_t* doer);

void doer_do_blin_print(char* s);

tree_t* doer_do_block(doer_t* doer);
tree_t* doer_do_expr(doer_t* doer);
tree_t* doer_do_lint(doer_t* doer);
tree_t* doer_do_lstr(doer_t* doer);
tree_t* doer_do_tag(doer_t* doer);
tree_t* doer_do_darg(doer_t* doer);
tree_t* doer_do_carg(doer_t* doer);
tree_t* doer_do_def(doer_t* doer);
tree_t* doer_do_call(doer_t* doer);

#endif

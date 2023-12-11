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

void doer_do_block(tree_t* tree);
void doer_do_expr(tree_t* tree);
void doer_do_lint(tree_t* tree);
void doer_do_lstr(tree_t* tree);
void doer_do_tag(tree_t* tree);
void doer_do_darg(tree_t* tree);
void doer_do_carg(tree_t* tree);
void doer_do_def(tree_t* tree);
void doer_do_call(tree_t* tree);

#endif

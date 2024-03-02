#ifndef DOER_H
#define DOER_H

#include "util.h"
#include "tree.h"

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

/* Built-in function. */
typedef struct BLINF {
   void (*fp)(doer_t*);
   char name[24];
} blinf_t;

void doer_do_blin_print(doer_t* tree); // Built-in function `print`.
void doer_do_blin_printl(doer_t* tree); // Built-in function `print`.

void doer_do_block(doer_t* tree);
void doer_do_expr(doer_t* tree);
void doer_do_lint(doer_t* tree);
void doer_do_lstr(doer_t* tree);
void doer_do_tag(doer_t* tree);
void doer_do_darg(doer_t* tree);
void doer_do_carg(doer_t* tree);
void doer_do_def(doer_t* tree);
void doer_do_call(doer_t* tree);

const static blinf_t blinfs[] = {
   { doer_do_blin_print, "print" },
   { doer_do_blin_printl, "printl" }
};

#endif

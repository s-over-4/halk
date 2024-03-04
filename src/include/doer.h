#ifndef DOER_H
#define DOER_H

#include "util.h"
#include "tree.h"

typedef struct TARGET {
   char* name;          // The name of the target (unique).
   tree_t* tree;        // The tree to which the target refers.
   struct TARGET* nxt;  // The next target in the list.
} target_t;

target_t* target_init(char* name, tree_t* tree);
/*
   Destroy a target.
   - Destroys all subsequent targets.
   - Frees `name`.
   - Does not free `tree`.
   Remember to NULL a parent target's `nxt`.
*/
void target_destroy(target_t* target);
// Print out the target list. Useful for debugging.
void target_print(target_t* target);

typedef struct DOER {
   tree_t* tree;        // The tree the doer is reading from.
   target_t* targets;   // The targets the doer must remember.
   target_t* ltarget;   // The last target in the list (after which new
                        // targets will be appended.)
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

void doer_add_target(doer_t* doer, target_t* target);

// Built-in functions.
// `print`: print a string.
void blin_print(doer_t* tree);
// `printl`: print a string, and add a newline.
void blin_printl(doer_t* tree);

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
   { blin_print, "print" },
   { blin_printl, "printl" }
};

#endif

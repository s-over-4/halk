#ifndef DOER_H
#define DOER_H

#include "util.h"
#include "tree.h"

// Points to a part of the AST the doer wishes to remember.
typedef struct TARGET {
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
   tree_t* (*fp)(doer_t*);    // The callback function in C.
   tree_type_t returnt;    // The return type of the function.
   tree_type_t* argts;     // Array of the arguments' types.
   char name[24];
} blinf_t;

void doer_add_target(doer_t* doer, target_t* target);
tree_t* doer_find_target_from_call(doer_t* doer);

// Given a tree, evaluate it to a primitive type.
tree_t* doer_eval_prim(doer_t* doer);
// Given a tree, evaluate it to a string (or type error).
char* doer_eval_str(doer_t* doer);
int doer_eval_lint(doer_t* doer);

// Built-in functions.
// `die`: dies. Does not accept any arguments, returns int (if a tree falls in
// the forest, &c &c.) TODO: Make this actually clean up afterwards.
tree_t* blin_die(doer_t* doer);
// `print`: print a string.
tree_t* blin_print(doer_t* doer);
static tree_type_t blin_print_args[] = { TREE_TYPE_LSTR };
// `printl`: print a string, and add a newline.
tree_t* blin_printl(doer_t* doer);
static tree_type_t blin_printl_args[] = { TREE_TYPE_LSTR };
// `str_cat`: concatenate strings.
// Returns a tree pointer to a lstr.
tree_t* blin_str_cat(doer_t* doer);
static tree_type_t blin_str_cat_args[] = { TREE_TYPE_LSTR, TREE_TYPE_LSTR };
// `+`: Add two integers.
tree_t* blin_add(doer_t* doer);
static tree_type_t blin_add_args[] = { TREE_TYPE_LINT, TREE_TYPE_LINT };

void doer_do_call(doer_t* doer);
tree_t* doer_do_call_blin(doer_t* doer);
tree_t* doer_do_call_def(doer_t* doer);
tree_t* doer_do_carg(doer_t* doer);
void doer_do_block(doer_t* tree);
void doer_do_expr(doer_t* tree);
void doer_do_lint(doer_t* tree);
void doer_do_lstr(doer_t* tree);
void doer_do_tag(doer_t* tree);
void doer_do_darg(doer_t* tree);
void doer_do_def(doer_t* tree);

static blinf_t blinfs[] = {
   { blin_die, TREE_TYPE_LINT, NULL, "die" },
   { blin_print, TREE_TYPE_LSTR, blin_print_args, "print" },
   { blin_printl, TREE_TYPE_LSTR, blin_printl_args, "printl" },
   { blin_str_cat, TREE_TYPE_LSTR, blin_str_cat_args, "str_cat" },
   { blin_add, TREE_TYPE_LINT, blin_add_args, "+" },
};

#endif

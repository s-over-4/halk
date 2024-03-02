#include "include/doer.h"
#include "include/tree.h"
#include "include/util.h"

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

void doer_do_blin_print(doer_t* doer) {
   printf(
      "%s",
      doer->tree->data.call.arg->data.carg.val->data.lstr.val
   );
}

void doer_do_blin_printl(doer_t* doer) {
   printf(
      "%s\n",
      doer->tree->data.call.arg->data.carg.val->data.lstr.val
   );
}

void doer_do_block(doer_t* doer) {
   if (!doer->tree) return;
   
   tree_t* tree_root = doer->tree;

   doer->tree = doer->tree->data.block.val;
   doer_do_expr(doer);
   doer->tree = tree_root->data.block.nxt;
   doer_do_block(doer);
}

void doer_do_expr(doer_t* doer) {
   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         /* Assume only call is `print` for now. */
         doer_do_call(doer);
         break;
      default:
         LOG_WARF("unknown tree type: %d", doer->tree->type);
   }
}

void doer_do_call(doer_t* doer) {
   /* Search through built-in functions first. */
   for (int i = 0; i < sizeof(blinfs) / sizeof(blinf_t); i++) {
      if (!strcmp(blinfs[i].name, doer->tree->data.call.target)) {
         (blinfs[i].fp)(doer);
         break;
      }
   }
}

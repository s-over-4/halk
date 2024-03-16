#include "include/doer.h"
#include "include/tree.h"
#include "include/util.h" 

target_t* target_init(char* name, tree_t* tree) {
   target_t* target = emalloc(sizeof(target_t));
   target->tree = tree;
   target->nxt = NULL;
   return target;
}

void target_destroy(target_t* target) {
   if (target) {
      target_destroy(target->nxt);
      free(target);
   }
}

void target_print(target_t* target) {
   if (!target) return;
   LOG_DBGF("target points to tree: %p", target->tree);
   target_print(target->nxt);
}

/* Creates a new doer from a tree.  */
doer_t* doer_init(tree_t* tree) {
   doer_t* doer;

   doer = emalloc(sizeof(doer_t));

   doer->tree = tree;
   doer->targets = NULL;
   doer->ltarget = doer->targets;

   return doer;
}

/*
   Destroys a doer.
   - Does not destroy the `tree`.
*/
void doer_destroy(doer_t* doer) {
   target_destroy(doer->targets);
   free(doer);
}

void doer_add_target(doer_t* doer, target_t* target) {
   // First target being added.
   if (!doer->targets) doer->targets = doer->ltarget = target;
   else doer->ltarget->nxt = target;
}

/*

   :str:var = "Hello"
   printl.var

*/

char* doer_eval_str(doer_t* doer) {
   // Assume tree type is a simple call to variable.
   // Search through target list for matching variable.
   // Return its value as a string (assume it's a string).
   // Assume there is only 1 target in the target list.

   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         // Assume there is only 1 target in the target list.
         doer->tree = doer->ltarget->tree->data.def.val;
         return doer_eval_str(doer);
      case TREE_TYPE_LSTR:
         // Already done \o/
         return doer->tree->data.lstr.val;
      default:
         DIE("Wrong type, FOOL!");
   }
}

void blin_die(doer_t* doer) {
   DIE(":(\nYour PC ran into a\n");
}

void blin_print(doer_t* doer) {
   doer->tree = doer->tree->data.call.arg->data.carg.val;

   printf(
      "%s",
      doer_eval_str(doer)
   );
}

void blin_printl(doer_t* doer) {
   doer->tree = doer->tree->data.call.arg->data.carg.val;

   printf(
      "%s\n",
      doer_eval_str(doer)
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
         doer_do_call(doer);
         break;
      case TREE_TYPE_DEF:
         doer_do_def(doer);
         break;
      default:
         LOG_WARF("unknown tree type: %d", doer->tree->type);
   }
}

void doer_do_def(doer_t* doer) {
   target_t* target = target_init(
      doer->tree->      // HACK: Grab the 2nd tag's value (w/o checking if
                        // it's actually there…).
         data.def.tag->
         data.tag.nxt->
         data.tag.val,
      doer->tree
   );

   doer_add_target(doer, target);
}

void doer_do_call(doer_t* doer) {
   // Search through built-in functions first.
   for (int i = 0; i < sizeof(blinfs) / sizeof(blinf_t); i++) {
      if (!strcmp(blinfs[i].name, doer->tree->data.call.target)) {
         (blinfs[i].fp)(doer);
         return;
      }
   }

   // Search through targets next.
   LOG_DBGF("got %s", doer->ltarget->tree->data.def.tag->data.tag.nxt->data.tag.val);
}

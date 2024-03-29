#include "include/doer.h"
#include "include/tree.h"
#include "include/util.h" 
#include <string.h>

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
   else {
      doer->ltarget->nxt = target;
      doer->ltarget = target;
   }
}

tree_t* doer_find_target_from_call(target_t* targetl, tree_t* call) {
   if (!targetl) { DIE("Call to missing value."); }
   
   char* last_target_name = targetl->tree->data.def.tag->data.tag.nxt->data.tag.val;
   char* call_name = call->data.call.target;

   if (!strcmp(last_target_name, call_name)) {
      return targetl->tree; 
   } else {
      return doer_find_target_from_call(targetl->nxt, call);
   }
}

char* doer_eval_str(doer_t* doer) {
   // Assume tree type is a simple call to variable.
   // Search through target list for matching variable.
   // Return its value as a string (assume it's a string).

   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         doer->tree = doer_find_target_from_call(doer->targets, doer->tree);
         return doer_eval_str(doer);
      case TREE_TYPE_DEF:
         doer->tree = doer->tree->data.def.val;
         return doer_eval_str(doer);
      case TREE_TYPE_LSTR:
         // Already done \o/.
         return doer->tree->data.lstr.val;
      default:
         DIE("Wrong type, FOOL!");
   }
}

void blin_die(doer_t* doer) {
   exit(1);
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

void blin_str_cat(doer_t* doer) {
   tree_t* oldt = doer->tree;
   doer->tree = doer->tree->data.call.arg->data.carg.val;
   char* str1 = doer_eval_str(doer);
   doer->tree = oldt->data.call.arg->data.carg.nxt->data.carg.val;
   char* str2 = doer_eval_str(doer);

   tree_destroy(doer->tree);

//    doer->tree = tree_init(TREE_TYPE_LSTR);
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
         LOG_WARF("Unknown tree type: %d", doer->tree->type);
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

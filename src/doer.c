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

tree_t* doer_find_target_from_call(doer_t* doer) {
   tree_t* this_call = doer->tree;
   char* call_name = this_call->data.call.target;

   target_t* target = doer->targets;

   while (target) {
      tree_t* tag = target->tree->data.def.tag;

      // HACK: Not saving types, just going straight to the good stuff.
      char* target_type = tag->data.tag.val;

      // Extract target's name from 2nd tag's val.
      char* target_name = tag->data.tag.nxt->data.tag.val;


      if (!strcmp(target_name, call_name)) {
         return target->tree; 
      } else {
         target = target->nxt;
      }
   }

   DIEF("Call to missing target: %s", call_name);
}

tree_t* doer_eval_prim(doer_t* doer) {
   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         doer_do_call(doer);
         return doer_eval_prim(doer);
      case TREE_TYPE_DEF:
         doer->tree = doer->tree->data.def.val;
         return doer_eval_prim(doer);
      case TREE_TYPE_LSTR:
      case TREE_TYPE_LINT:
         return doer->tree;
      default:
         DIE("???");
   }
}

char* doer_eval_str(doer_t* doer) {
   // Assume tree type is a simple call to variable.
   // Search through target list for matching variable.
   // Return its value as a string (assume it's a string).

   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         doer_do_call(doer);
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

int doer_eval_lint(doer_t* doer) {
   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         doer_do_call(doer);
         return doer_eval_lint(doer);
      case TREE_TYPE_DEF:
         doer->tree = doer->tree->data.def.val;
         return doer_eval_lint(doer);
      case TREE_TYPE_LINT:
         // Already done \o/.
         return doer->tree->data.lint.val;
      default:
         DIE("Wrong type, FOOL!");
   }
}

tree_t* blin_die(doer_t* doer) {
   exit(1);
   return NULL;   // Doesn't really matter what happens here.
}

tree_t* blin_print(doer_t* doer) {
   tree_t* oldt = doer->tree;
   doer->tree = doer->tree->data.call.arg->data.carg.val;
   tree_t* arg = doer_eval_prim(doer);

   char* rval;

   switch (arg->type) {
      case TREE_TYPE_LINT:
         printf("%d", arg->data.lint.val);
         rval = ecalloc(64, sizeof(char));
         sprintf(rval, "%d", arg->data.lint.val);
         break;
      case TREE_TYPE_LSTR:
         printf("%s", arg->data.lstr.val);
         rval = ecalloc(arg->data.lstr.len + 1, sizeof(char));
         sprintf(rval, "%s", arg->data.lstr.val);
         break;
      default:
         rval = ecalloc(1, sizeof(char));
         rval[0] = '\0';
   }

   tree_t* lstr = tree_init(TREE_TYPE_LSTR, oldt->parent);
   lstr->data.lstr.val = rval;
   lstr->data.lstr.len = strlen(rval);

   return lstr;
}

tree_t* blin_printl(doer_t* doer) {
   tree_t* oldt = doer->tree;
   doer->tree = doer->tree->data.call.arg->data.carg.val;
   tree_t* arg = doer_eval_prim(doer);

   char* rval;

   switch (arg->type) {
      case TREE_TYPE_LINT:
         printf("%d\n", arg->data.lint.val);
         rval = ecalloc(64, sizeof(char));
         sprintf(rval, "%d\n", arg->data.lint.val);
         break;
      case TREE_TYPE_LSTR:
         printf("%s\n", arg->data.lstr.val);
         rval = ecalloc(arg->data.lstr.len + 2, sizeof(char));
         sprintf(rval, "%s\n", arg->data.lstr.val);
         break;
      default:
         rval = ecalloc(2, sizeof(char));
         rval[0] = '\n';
         rval[1] = '\0';
   }

   tree_t* lstr = tree_init(TREE_TYPE_LSTR, oldt->parent);
   lstr->data.lstr.val = rval;
   lstr->data.lstr.len = strlen(rval);

   return lstr;
}

tree_t* blin_str_cat(doer_t* doer) {
   tree_t* oldt = doer->tree;
   doer->tree = doer->tree->data.call.arg->data.carg.val;
   char* str1 = doer_eval_str(doer);
   doer->tree = oldt->data.call.arg->data.carg.nxt->data.carg.val;
   char* str2 = doer_eval_str(doer);

   char* val = emalloc(
      sizeof(str1) +
      sizeof(str2) -
      sizeof(char)
   );

   strcpy(val, str1);
   strcat(val, str2);

   doer->tree = tree_init(TREE_TYPE_LSTR, oldt->parent);

   doer->tree->data.lstr.val = val;
   doer->tree->data.lstr.len = strlen(val);

   return doer->tree; 
}

tree_t* blin_add(doer_t* doer) {
   tree_t* tree = doer->tree;

   tree_t* args = tree->data.call.arg;
   tree_t* arg1 = args;
   tree_t* arg2 = arg1->data.carg.nxt;

   doer->tree = arg1->data.carg.val;
   int a = doer_eval_lint(doer);
   doer->tree = arg2->data.carg.val;
   int b = doer_eval_lint(doer);

   tree_t* newt =  tree_init(TREE_TYPE_LINT, tree->parent);

   newt->data.lint.val = a + b;

   return newt;
}

tree_t* blin_sub(doer_t* doer) {
   tree_t* tree = doer->tree;

   tree_t* args = tree->data.call.arg;
   tree_t* arg1 = args;
   tree_t* arg2 = arg1->data.carg.nxt;

   doer->tree = arg1->data.carg.val;
   int a = doer_eval_lint(doer);
   doer->tree = arg2->data.carg.val;
   int b = doer_eval_lint(doer);

   tree_t* newt =  tree_init(TREE_TYPE_LINT, tree->parent);

   newt->data.lint.val = a - b;

   return newt;
}

tree_t* blin_mul(doer_t* doer) {
   tree_t* tree = doer->tree;

   tree_t* args = tree->data.call.arg;
   tree_t* arg1 = args;
   tree_t* arg2 = arg1->data.carg.nxt;

   doer->tree = arg1->data.carg.val;
   int a = doer_eval_lint(doer);
   doer->tree = arg2->data.carg.val;
   int b = doer_eval_lint(doer);

   tree_t* newt =  tree_init(TREE_TYPE_LINT, tree->parent);

   newt->data.lint.val = a * b;

   return newt;
}

void doer_do_block(doer_t* doer) {
   if (!doer->tree) return;
   
   tree_t* tree_block = doer->tree;

   doer->tree = doer->tree->data.block.val;
   doer_do_expr(doer);
   doer->tree = tree_block->data.block.nxt;
   doer_do_block(doer);
}

void doer_do_expr(doer_t* doer) {
   switch (doer->tree->type) {
      case TREE_TYPE_CALL:
         // Add targets
         doer_do_call(doer);
         // Remove targets
         break;
      case TREE_TYPE_DEF:
         doer_do_def(doer);
         break;
      default:
         LOG_WARF("Unknown tree type: %d", doer->tree->type);
   }
}

void doer_do_def(doer_t* doer) {
   tree_t* tag2 = doer->tree->data.def.tag->data.tag.nxt;
   target_t* target = target_init(
      tag2->data.tag.val,     // HACK: Grab the 2nd tag's value, without
                                    // checking if it's actually there…
      doer->tree
   );

   doer_add_target(doer, target);
}

void doer_do_call(doer_t* doer) {
   tree_t* the_call = doer->tree;
   tree_t* resolved = NULL;

   // Could modify the *current* tree, but only if it's a blin.
   resolved = doer_do_call_blin(doer);

   if (!resolved) {
      doer->tree = the_call;
      resolved = doer_find_target_from_call(doer);
   }

   tree_swp_call(the_call, resolved);
   tree_destroy(the_call);
   doer->tree = resolved;
}

tree_t* doer_do_call_blin(doer_t* doer) {
   for (int i = 0; i < sizeof(blinfs) / sizeof(blinf_t); i++)
      if (!strcmp(blinfs[i].name, doer->tree->data.call.target))
         return (blinfs[i].fp)(doer);

   return NULL;
}

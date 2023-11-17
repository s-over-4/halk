#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree;

   tree = emalloc(sizeof(struct TREE));

   tree->type = type;
   
   switch (tree->type) {
      case TREE_TYPE_LINT:
         tree->data.lint.val = 0;
         break;
      case TREE_TYPE_LSTR:
         tree->data.lstr.len = 0;
         break;
      case TREE_TYPE_TAG:
         tree->data.tag.val = NULL;
         tree->data.tag.nxt = NULL;
         break;
      case TREE_TYPE_DARG:
         tree->data.darg.tag = NULL;
         tree->data.darg.nxt = NULL;
         break;
      case TREE_TYPE_CARG:
         tree->data.carg.val = NULL;
         tree->data.carg.nxt = NULL;
         break;
      case TREE_TYPE_DEF:
         tree->data.def.tag = NULL;
         tree->data.def.arg = NULL;
         tree->data.def.val = NULL;
         break;
      case TREE_TYPE_CAL:
         tree->data.cal.target = NULL;
         tree->data.cal.arg = NULL;
         break;
   }

   return tree;
}

void tree_destroy(tree_t* tree) {
   free(tree);
}

tree_targ_t* tree_targ_init(tree_t* tree) {
   tree_targ_t* targ;

   targ = emalloc(sizeof(tree_targ_t));
   targ->tree = tree;
   targ->nxt = NULL;

   return targ;
}

void tree_targ_destroy(tree_targ_t* targ) {
   if (targ->nxt) {
      tree_targ_destroy(targ->nxt);
      targ->nxt = NULL;
   }

   free(targ);
} 

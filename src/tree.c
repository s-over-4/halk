#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree = calloc(1, sizeof(struct TREE_STRUC));

   tree->type = type;

   switch (type) {
      case TREE_VAR_DEF:
         tree->data.var_def.name       = NULL;
         tree->data.var_def.val        = NULL;
         tree->data.var_def.is_const   = 0;
         break;
      case TREE_VAR:
         tree->data.var.name           = NULL;
         break;
      case TREE_FN_DEF:
         tree->data.fn_def.name        = NULL;
         tree->data.fn_def.val         = NULL;
         tree->data.fn_def.argv        = NULL;
         tree->data.fn_def.argsize     = 0;
         break;
      case TREE_FN_CALL:
         tree->data.fn_call.name       = NULL;
         tree->data.fn_call.argv       = NULL;
         tree->data.fn_call.argsize    = 0;
         break;
      case TREE_STR:
         tree->data.str.val            = NULL;
         tree->data.subtree.val        = NULL;
         tree->data.subtree.size       = 0;
         break;
   }

   return tree;
}

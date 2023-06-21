#include "include/tree.h"


prim_t* prim_init(int type) {
   prim_t* prim = calloc(1, sizeof(struct PRIM_STRUC));

   prim->type = type;
   prim->is_mutable = 0;

   switch (type) {
      case STR:
         prim->val.prim_str.len = NULL;
         prim->val.prim_str.val = NULL;
         break;
      case INT:
         prim->val.prim_int.val = NULL; 
      default:
         prim->val.prim_unkwn.val = NULL;
   }

   return prim;
}


tree_t* tree_init(int type) {
   tree_t* tree = calloc(1, sizeof(struct TREE_STRUC));

   tree->type = type;

   switch (type) {
      case TREE_PRIM:
         tree->oftype.prim.val         = NULL;
         break;
      case TREE_SUBTREE:
         tree->oftype.subtree.size     = 0;
         tree->oftype.subtree.val      = NULL;
         break;
      case TREE_DEF:
         tree->oftype.def.args         = NULL;
         tree->oftype.def.name         = NULL;
         tree->oftype.def.val          = NULL;
         break;
      case TREE_CALL:
         tree->oftype.call.args        = NULL;
         tree->oftype.call.name        = NULL;
         break;
   }

   return tree;
}

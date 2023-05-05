#include "include/tree.h"

TREE_t* tree_init(int type) {
   // give the tree just enough room
   TREE_t* tree = calloc(1, sizeof(struct TREE_STRUC));

   tree->type = type;

   tree->VAR_DEF_name      = NULL;
   tree->VAR_DEF_value     = NULL;
   tree->VAR_name          = NULL;


   return tree;
}

#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree;

   tree = calloc(1, sizeof(struct TREE_STRUC));
   tree->type = type;
   
   switch (type) {
      case TREE_COMP:
         tree->data.comp.value         = (void*) 0;
         tree->data.comp.size          = 0;
         break;
      case TREE_DEF:
         tree->data.def.mutability     = 0;
         tree->data.def.name           = (void*) 0;
         tree->data.def.value          = (void*) 0;
         break;
      case TREE_CALL:
         tree->data.call.args          = (void*) 0;
         tree->data.call.args_size     = 0;
         tree->data.call.target        = (void*) 0;
         break;
      case TREE_TYPE_STR:
         tree->data.type_str.value     = (void*) 0;
         break;
      case TREE_TYPE_INT:
         tree->data.type_int.value     = (void*) 0;
         break;
   }

   return tree;
}

void tree_destroy(tree_t* tree) {
   free(tree);
}

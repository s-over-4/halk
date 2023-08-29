#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree;

   tree = calloc(1, sizeof(struct TREE_STRUC));
   tree->type = type;
   
   switch (type) {
      case TREE_COMP:
         tree->data.comp.value         = NULL;
         tree->data.comp.size          = 0;
         break;
      case TREE_DEF:
         tree->data.def.type           = NULL;
         tree->data.def.tags           = NULL;
         tree->data.def.tags_size      = 0;
         tree->data.def.name           = NULL;
         tree->data.def.args           = NULL;
         tree->data.def.tags_size      = 0;
         tree->data.def.value          = NULL;
         break;
      case TREE_CALL:
         tree->data.call.target        = NULL;
         tree->data.call.args          = NULL;
         tree->data.call.args_size     = 0;
         break;
      case TREE_TYPE_STR: 
         tree->data.type_str.value     = NULL; 
         break; 
      case TREE_TYPE_INT: 
         tree->data.type_int.value     = 0; 
         break;
   }

   return tree;
}

void tree_destroy(tree_t* tree) {
   free(tree);
}

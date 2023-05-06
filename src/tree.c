#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree = calloc(1, sizeof(struct TREE_STRUC));

   tree->type = type;

   char*                var_def_name      = NULL;
   struct TREE_STRUC*   var_def_val       = NULL;
   char*                var_name          = NULL;

   char*                fn_call_name      = NULL;
   struct TREE_STRUC**  fn_call_argv      = NULL;
   size_t               fn_call_argsize   = 0;

   char*                str_val           = NULL;

   struct TREE_STRUC*   subtree_val       = NULL;
   size_t               subtree_size      = 0;

   return tree;
}

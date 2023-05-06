#ifndef TREE_H
#define TREE_H


#include <stdlib.h>


typedef struct TREE_STRUC {

   enum {
      TREE_VAR_DEF,
      TREE_VAR,

      TREE_FN_DEF,
      TREE_FN_CALL,
      
      TREE_STR,

      TREE_SUBTREE,
   } type;

   char*                var_def_name;
   struct TREE_STRUC*   var_def_val;

   char*                var_name;

   char*                fn_call_name;
   struct TREE_STRUC**  fn_call_argv;
   size_t               fn_call_argsize;

   char*                str_val;

   struct TREE_STRUC*   subtree_val;
   size_t               subtree_size;

} tree_t;

tree_t* tree_init(int type);


#endif

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

   union tree_union {

      struct var_def_struc {
         char*                      name;
         struct TREE_STRUC*         val;
         int*                       is_const;
      } var_def;

      struct var_struc {
         char*                      name;
      } var;

      struct fn_def_struc {
         char*                      name;
         struct TREE_STRUC**        val;
         struct TREE_STRUC**        argv;
         size_t                     argsize;
      } fn_def;

      struct fn_call_struc {
         char*                      name;
         struct TREE_STRUC**        argv;
         size_t                     argsize;
      } fn_call;

      struct str_struc {
         char*                      val;
      } str;

      struct subtree_struc {
         struct TREE_STRUC**        val;
         size_t                     size;
      } subtree;

   } data;

} tree_t;

tree_t* tree_init(int type);


#endif

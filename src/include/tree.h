#ifndef TREE_H
#define TREE_H


#include <stdlib.h>


typedef struct PRIM_STRUC {
   int is_mutable;
   enum {
      STR,
      INT,
      //ARR,
      //FLOAT,
      //STRUCT,
      //NAMESPACE,
   } type; 

   union prim_union {
      struct str_struc {
         unsigned int len;
         char* val;
      };

      struct int_struc {
         int val;
      };
   } with_value;
} prim_t;

typedef struct TREE_STRUC {
   enum {
      TREE_PRIM,
      TREE_SUBTREE,
      TREE_DEF,
      TREE_CALL,
   } type;

   union tree_union {

      struct prim_struc {
         prim_t* val;
      } prim;

      struct subtree_struc {
         struct TREE_STRUC** val;
         size_t size;
      } subtree;

      struct def_struc {
         char* name;
         prim_t** args;
         struct subtree_struc** val;
      } def;

      struct call_struc {
         char* name;
         prim_t** args;
      } call;

   } of_type;
} tree_t;

prim_t* prim_init(int type);
tree_t* tree_init(int type);


#endif

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>


typedef struct PRIM_STRUC {
   int is_mutable;
   enum {
      STR,
      INT,
      UNKWN,
   } type; 

   union prim_union {
      struct str_struc {
         unsigned int* len;
         char* val;
      } prim_str;

      struct int_struc {
         int* val;
      } prim_int;

      struct unkwn_struc {
         void* val;
      } prim_unkwn;
   } val;
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

   } oftype;
} tree_t;

prim_t* prim_init(int type);
tree_t* tree_init(int type);


#endif

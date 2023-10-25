#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef enum {
      LEAF_TYPE_INT,
      LEAF_TYPE_STR,
} leaf_t;

typedef struct ARG_T_STRUCT {
   leaf_t type;
   char* id;
   struct ARG_T_STRUCT* nxt;
} arg_t;

typedef struct TREE_T_STRUCT {
   enum TREE_TYPE {
      TREE_TYPE_DEF,
      TREE_TYPE_CAL,
   } type;

   union {
      struct {
         leaf_t type;
         char* id;
         arg_t* arg;
         struct TREE_T_STRUCT* val;
      } tree_def;
   } data;
} tree_t;

tree_t* tree_init(int type);
void tree_destroy(tree_t*);

#endif

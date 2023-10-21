#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct TREE_STRUC {
   enum TREE_TYPE {
      TREE_TYPE_INT,
      TREE_TYPE_STR,
      TREE_TYPE_DEF,
      TREE_TYPE_CAL,
      TREE_TYPE_COND,
   } type;

   union {
      struct {
         int val;
      } tree_int_t;

      struct {
         char* val;
      } tree_str_t;

      struct {
         char* id;
      } tree_def_t;
   } data;
} tree_t;

tree_t* tree_init(int type);
void tree_destroy(tree_t*);

#endif

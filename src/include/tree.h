#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct TREE_STRUC {
   enum {
      TREE_VAR_DEF,
      //TREE_FUN_DEF,
      TREE_VAR,
      //TREE_FUN_CALL,
      //TREE_STR,
      //TREE_COMP
   } type;

   char* VAR_DEF_name;
   struct TREE_STRUC* VAR_DEF_value;

   char* VAR_name;

} TREE_t;

TREE_t* tree_init(int type);

#endif

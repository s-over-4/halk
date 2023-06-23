#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct TREE_STRUC {
   enum {
      TREE_DEF,
      TREE_CALL,
      TREE_STRING,
      TREE_INT,
   } type;

   union {
      struct def {
         char*                name;          // name of definition
         int                  mutability;    // mutability of definition
         struct TREE_STRUC*   value;         // value of definition
      };

      struct call {
         char*                target;        // name of definition being called
         struct TREE_STRUC**  args;          // arguments passed to definition
      };
   } data;
} tree_t;

#endif

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct TREE_STRUC {
   enum {
      TREE_DEF,
      TREE_CALL,
      TREE_TYPE_STR,
      TREE_TYPE_INT,
   } type;

   union {
      struct {                           // === DEFINITIONS ===
         char*                name;          // name of definition
         int                  mutability;    // mutability of definition
         struct TREE_STRUC*   value;         // value of definition
      } def;

      struct {                          // === CALLS ===
         char*                target;        // name of definition being called
         struct TREE_STRUC**  args;          // arguments passed to definition
         size_t               args_size;     // size of arguments
      } call;

                                             // === TYPES ===
      struct {                      // strings
         char*                value;
      } type_str; 

      struct {                   // integers
         int*                 value;
      } type_int;
   } data;
} tree_t;

tree_t* tree_init(int type);
void tree_destroy(tree_t*);

#endif

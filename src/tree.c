#include "include/tree.h"

TREE_t* tree_init(int type) {
   TREE_t* tree = calloc(1, sizeof(struct TREE_STRUC));

   return tree;
}

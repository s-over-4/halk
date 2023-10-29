#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct TREE {
   enum TREE_TYPE {
      TREE_TYPE_LINT,
      TREE_TYPE_LSTR,
      TREE_TYPE_TAG,
      TREE_TYPE_DARG,
      TREE_TYPE_CARG,
      TREE_TYPE_DEF,
      TREE_TYPE_CAL,
   } type;

   union TREE_DATA{

      /* literal integer */
      struct TREE_DATA_LINT {
         int val;
      } lint;

      /* literal string */
      struct TREE_DATA_LSTR {
         size_t len;
         char* val;
      } lstr;

      /* tags */
      struct TREE_DATA_TAG {
         char* val;
         struct TREE_DATA_TAG* nxt;
      } tag;

      /* definition arguments */
      struct TREE_DATA_DARG {
         struct TREE_DATA_TAG* tag;
         struct TREE_DATA_DARG* nxt;
      } darg;

      /* call arguments */
      struct TREE_DATA_CARG {
         struct TREE* val;
         struct TREE_DATA_CARG* nxt;
      } carg;
      
      /* definitions */
      struct TREE_DATA_DEF {
         struct TREE_DATA_TAG* tag;
         struct TREE_DATA_DARG* arg;
         struct TREE* val;
      } def;

      /* calls */
      struct TREE_DATA_CAL {
         char* target;
         struct TREE_DATA_CARG* arg;
      } cal;

   } data;
} tree_t;

tree_t* tree_init(int type);
void tree_destroy(tree_t* tree);

#endif

#ifndef TREE_H
#define TREE_H

#include "util.h"

/* The Abstract Syntax Tree (AST) structure. */
typedef struct TREE {
   enum TREE_TYPE {
      TREE_TYPE_BLOCK,
      TREE_TYPE_LINT,
      TREE_TYPE_LSTR,
      TREE_TYPE_TAG,
      TREE_TYPE_DARG,
      TREE_TYPE_CARG,
      TREE_TYPE_DEF,
      TREE_TYPE_CAL,
   } type;

   union TREE_DATA{
      /* Block. */
      struct TREE_DATA_BLOCK {
         /* The first expression in the block. */
         struct TREE* val;
         /* The next expression in the block. If it's'nt a block, end the block. */
         struct TREE* nxt;
      } block;

      /* Literal integer. */
      struct TREE_DATA_LINT {
         int val;
      } lint;

      /* Literal string. */
      struct TREE_DATA_LSTR {
         size_t len;
         char* val;
      } lstr;

      /* Tags. */
      struct TREE_DATA_TAG {
         char* val;
         struct TREE_DATA_TAG* nxt;
      } tag;

      /* Definition arguments. */
      struct TREE_DATA_DARG {
         struct TREE_DATA_TAG* tag;
         struct TREE_DATA_DARG* nxt;
      } darg;

      /* Call arguments. */
      struct TREE_DATA_CARG {
         struct TREE* val;
         struct TREE_DATA_CARG* nxt;
      } carg;
      
      /* Definitions. */
      struct TREE_DATA_DEF {
         struct TREE_DATA_TAG* tag;
         struct TREE_DATA_DARG* arg;
         struct TREE* val;
      } def;

      /* Calls. */
      struct TREE_DATA_CAL {
         char* target;
         struct TREE_DATA_CARG* arg;
      } cal;

   } data;
} tree_t;

/* Create a new AST. */
tree_t* tree_init(int type);
/* Destroy the AST. */
void tree_destroy(tree_t* tree);

/* TODO: Implement a better target organization structure that's better for searching. */
typedef struct TREE_TARG {
   tree_t* tree;
   struct TREE_TARG* nxt;
} tree_targ_t;

/* Create a new target. */
tree_targ_t* tree_targ_init(tree_t* tree);
/* 
   Destroy a target.
   - Frees all subsequent targets in `nxt`.
   - Does not free the `tree`.
*/
void tree_targ_destroy(tree_targ_t* targ);

#endif

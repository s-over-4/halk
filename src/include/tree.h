#ifndef TREE_H
#define TREE_H

#include "util.h"

typedef enum TREE_TYPE {
      TREE_TYPE_BLOCK,
      TREE_TYPE_EXPR,
      TREE_TYPE_LINT,
      TREE_TYPE_LSTR,
      TREE_TYPE_TAG,
      TREE_TYPE_DARG,
      TREE_TYPE_CARG,
      TREE_TYPE_DEF,
      TREE_TYPE_CAL,
} tree_type_t;

/* The Abstract Syntax Tree (AST) structure. */
typedef struct TREE {
   tree_type_t type;

   union TREE_DATA{
      /* Block. */
      struct TREE_DATA_BLOCK {
         /* The first expression in the block. */
         struct TREE* val;
         /* 
            The next block in the linked list.
            - If it's `NULL`, it's the end of the block.
         */
         struct TREE* nxt;
      } block;

      /* Expression. */
      struct TREE_DATA_EXPR {
         /* The contents of the expression. */
         struct TREE* val;
      } expr;

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

/* Print a tree. */
void tree_print(tree_t* tree, int nest);

#endif

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
   TREE_TYPE_CALL
} tree_type_t;

/* The Abstract Syntax Tree (AST) structure. */
typedef struct TREE {
   tree_type_t type;

   struct TREE* parent;

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
         struct TREE* val; /* ??? */
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
         struct TREE* nxt; /* TAG */
      } tag;

      /* Definition arguments. */
      struct TREE_DATA_DARG {
         struct TREE* tag; /* TAG */
         struct TREE* nxt; /* DARG */
      } darg;

      /* Call arguments. */
      struct TREE_DATA_CARG {
         struct TREE* val; /* EXPR */
         struct TREE* nxt; /* CARG */
      } carg;
      
      /* Definitions. */
      struct TREE_DATA_DEF {
         struct TREE* tag; /* TAG */
         struct TREE* arg; /* DARG */
         struct TREE* val; /* EXPR */
      } def;

      /* Calls. */
      struct TREE_DATA_CALL {
         char* target;
         struct TREE* arg; /* CARG */
      } call;
   } data;
} tree_t;

/* Create a new AST. */
tree_t* tree_init(tree_type_t type, tree_t* parent);
/* Destroy the AST (if it exists). */
void tree_destroy(tree_t* tree);

/*
   Compare two trees. For testing.
   Returns 1 if the same, otherwise 0.
*/
int tree_cmp(tree_t* tree_0, tree_t* tree_1);

/* Print a tree. */
void tree_print(tree_t* tree, int nest);

#endif

#ifndef TREE_H
#define TREE_H

#include "util.h"

typedef enum TREE_TYPE {
   TREE_TYPE_BLOCK   = 0,
   TREE_TYPE_EXPR    = 1,  // Deprecated.
   TREE_TYPE_LINT    = 2,
   TREE_TYPE_LSTR    = 3,
   TREE_TYPE_TAG     = 4,
   TREE_TYPE_DARG    = 5,
   TREE_TYPE_CARG    = 6,
   TREE_TYPE_DEF     = 7,
   TREE_TYPE_CALL    = 8,
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

void tree_rm(tree_t* t);
// void tree_append(tree_t** dest, tree_t* t);

tree_t* tree_copy_out(tree_t* tree);

/*
   Compare two trees. For testing.
   Returns 1 if the same, otherwise 0.
*/
int tree_cmp(tree_t* tree_0, tree_t* tree_1);

// Swaps a tree for another.
void tree_swp_call(tree_t* t0, tree_t* t1);

// Determines if a tree_type_t matches a string.
int tree_type_str(tree_type_t tree_type, char* str);

// Returns a string for a tree type.
char* tree_type2str(tree_type_t tree_type);

/* Print a tree. */
void tree_print(tree_t* tree, int nest);

#endif

#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree;

   tree = emalloc(sizeof(struct TREE));

   tree->type = type;
   
   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         tree->data.block.val = NULL;
         tree->data.block.nxt = NULL;
         break;
      case TREE_TYPE_LINT:
         tree->data.lint.val = 0;
         break;
      case TREE_TYPE_LSTR:
         tree->data.lstr.len = 0;
         break;
      case TREE_TYPE_TAG:
         tree->data.tag.val = NULL;
         tree->data.tag.nxt = NULL;
         break;
      case TREE_TYPE_DARG:
         tree->data.darg.tag = NULL;
         tree->data.darg.nxt = NULL;
         break;
      case TREE_TYPE_CARG:
         tree->data.carg.val = NULL;
         tree->data.carg.nxt = NULL;
         break;
      case TREE_TYPE_DEF:
         tree->data.def.tag = NULL;
         tree->data.def.arg = NULL;
         tree->data.def.val = NULL;
         break;
      case TREE_TYPE_CAL:
         tree->data.cal.target = NULL;
         tree->data.cal.arg = NULL;
         break;
   }

   return tree;
}

void tree_destroy(tree_t* tree) {
   free(tree);
}

void tree_print(tree_t* tree, int nest) {
   char* spaces;
   int i;

   for (spaces = ecalloc(nest + 1, sizeof(char)), i = 0; i < nest; spaces[i++] = ' ');
   spaces[i] = '\0';

#define NEST(TEXT) log_raw("%s" TEXT "\n", spaces);

   if (!tree) {
      NEST("NULL");
      return;
   }

   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         NEST("[block]");
         NEST(" - val:");
            tree_print(tree->data.block.val, nest + 3);
         NEST(" - nxt:");
            tree_print(tree->data.block.nxt, nest + 3);
         break;
      case TREE_TYPE_LINT:
         log_raw("%s[lint]: %d\n", spaces, tree->data.lint.val);
         break;
      case TREE_TYPE_LSTR:
         log_raw("%s[lstr]: %s\n", spaces, tree->data.lstr.val);
         break;
      case TREE_TYPE_TAG:
      case TREE_TYPE_DARG:
      case TREE_TYPE_CARG:
      case TREE_TYPE_DEF:
      case TREE_TYPE_CAL:
         NEST("??");
         break;
   }

}

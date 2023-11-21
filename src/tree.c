#include "include/tree.h"

tree_t* tree_init(int type) {
   tree_t* tree;

   tree = emalloc(sizeof(tree_t));

   tree->type = type;
   
   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         tree->data.block.val = NULL;
         tree->data.block.nxt = NULL;
         break;
      case TREE_TYPE_EXPR:
         tree->data.expr.val = NULL;
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
   if (!tree) { return; }

   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         tree_destroy(tree->data.block.val);
         tree_destroy(tree->data.block.nxt);
         break;
      case TREE_TYPE_EXPR:
         tree_destroy(tree->data.expr.val);
         break;
      case TREE_TYPE_LINT:
         break;
      case TREE_TYPE_LSTR:
         free(tree->data.lstr.val);
         break;
      case TREE_TYPE_TAG:
         free(tree->data.tag.val);
         tree_destroy(tree->data.tag.nxt);
         break;
      case TREE_TYPE_DARG:
         free(tree->data.darg.tag);
         tree_destroy(tree->data.darg.nxt);
         break;
      case TREE_TYPE_CARG:
         free(tree->data.carg.val);
         tree_destroy(tree->data.carg.nxt);
         break;
      case TREE_TYPE_DEF:
         free(tree->data.def.tag);
         free(tree->data.def.arg);
         tree_destroy(tree->data.def.val);
         break;
      case TREE_TYPE_CAL:
         free(tree->data.cal.target);
         tree_destroy(tree->data.cal.arg);
         break;
   }

   free(tree);
}

void tree_print(tree_t* tree, int nest) {
   char* spaces;
   int i;

   /* Aaahhh. */
   for(i=0,spaces=ecalloc(nest+1,sizeof(char)),spaces[nest]='\0';i<=nest-1;spaces[i++]=' ');

   #define NEST(TEXT) log_raw("%s"TEXT"\n",spaces);
   #define NEST2(TEXT) log_raw("%s"TEXT,spaces);

   if (!tree) {
      NEST("NULL");
      goto tree_print_exit;
   }

   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         NEST("[block]");
         NEST("val:");
            tree_print(tree->data.block.val, nest + 1);
         NEST("nxt:");
            tree_print(tree->data.block.nxt, nest + 1);
         break;
      case TREE_TYPE_EXPR:
         NEST("[expression]");
         NEST("val:");
            tree_print(tree->data.expr.val, nest + 1);
         break;
      case TREE_TYPE_LINT:
         NEST("[lint]");
         NEST("val:");
            log_raw("%s %d\n", spaces, tree->data.lint.val);
         break;
      case TREE_TYPE_LSTR:
         NEST("[lstr]");
         NEST("val:");
            log_raw("%s %s\n", spaces, tree->data.lstr.val);
         NEST("len:");
            log_raw("%s %d\n", spaces, tree->data.lstr.len);
         break;
      case TREE_TYPE_TAG:
      case TREE_TYPE_DARG:
      case TREE_TYPE_CARG:
      case TREE_TYPE_DEF:
      case TREE_TYPE_CAL:
         NEST("???");
         break;
   }

   tree_print_exit: free(spaces); return;
}

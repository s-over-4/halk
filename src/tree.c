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
         tree->data.lstr.val = NULL;
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
      case TREE_TYPE_CALL:
         tree->data.call.target = NULL;
         tree->data.call.arg = NULL;
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
         tree_destroy(tree->data.darg.tag);
         tree_destroy(tree->data.darg.nxt);
         break;
      case TREE_TYPE_CARG:
         tree_destroy(tree->data.carg.val);
         tree_destroy(tree->data.carg.nxt);
         break;
      case TREE_TYPE_DEF:
         tree_destroy(tree->data.def.tag);
         tree_destroy(tree->data.def.arg);
         tree_destroy(tree->data.def.val);
         break;
      case TREE_TYPE_CALL:
         free(tree->data.call.target);
         tree_destroy(tree->data.call.arg);
         break;
   }

   free(tree);
}

void tree_print(tree_t* tree, int nest) {
   char* spaces;
   int ncolor;
   char* color;
   char* bcolor;
   int i;

   /* Aaahhh. */
   for(i=0,spaces=ecalloc(nest+1,sizeof(char)),spaces[nest]='\0';i<=nest-1;spaces[i++]=' ');
   ncolor=31+nest%6;
   color=malloc(9*sizeof(char));
   bcolor=malloc(11*sizeof(char));
   sprintf(color,"\x1b[%dm",ncolor);
   sprintf(bcolor,"\x1b[%d;1m",ncolor);

   #define NEST0(TEXT) log_raw("%s%s"TEXT"\x1b[0m\n",bcolor,spaces);
   #define NEST1(TEXT) log_raw("%s%s"TEXT"\x1b[0m\n",color,spaces);
   #define NEST2(TEXT) log_raw("%s \x1b[39;49;4m%s\x1b[0m\n",spaces,TEXT);
   #define NEST3(TEXT) log_raw("%s \x1b[39;49;4m%d\x1b[0m\n",spaces,TEXT);

   if (!tree) { NEST2("NULL"); goto end; }

   switch (tree->type) {
      case TREE_TYPE_BLOCK:
         NEST0("[block]");
         NEST1("val:");
            tree_print(tree->data.block.val, nest + 1);
         NEST1("nxt:");
            tree_print(tree->data.block.nxt, nest + 1);
         break;
      case TREE_TYPE_EXPR:
         NEST0("[expression]");
         NEST1("val:");
            tree_print(tree->data.expr.val, nest + 1);
         break;
      case TREE_TYPE_LINT:
         NEST0("[lint]");
         NEST1("val:");
            NEST3(tree->data.lint.val);
         break;
      case TREE_TYPE_LSTR:
         NEST0("[lstr]");
         NEST1("val:");
            NEST2(tree->data.lstr.val);
         NEST1("len:");
            NEST3(tree->data.lstr.len);
         break;
      case TREE_TYPE_CALL:
         NEST0("[call]");
         NEST1("target:");
            NEST2(tree->data.call.target);
         NEST1("arg:")
            tree_print(tree->data.call.arg, nest + 1);
         break;
      case TREE_TYPE_CARG:
         NEST0("[carg]");
         NEST1("val:");
            tree_print(tree->data.carg.val, nest + 1);
         NEST1("nxt:");
            tree_print(tree->data.carg.nxt, nest + 1);
         break;
      case TREE_TYPE_DEF:
         NEST0("[def]");
         NEST1("tag:");
            tree_print(tree->data.def.tag, nest + 1);
         NEST1("arg:");
            tree_print(tree->data.def.arg, nest + 1);
         NEST1("val:");
            tree_print(tree->data.def.val, nest + 1);
         break;
      case TREE_TYPE_TAG:
         NEST0("[tag]");
         NEST1("val:");
            NEST2(tree->data.call.target);
         NEST1("nxt:");
            tree_print(tree->data.tag.nxt, nest + 1);
         break;
      case TREE_TYPE_DARG:
         NEST0("[darg]");
         NEST1("tag:");
            tree_print(tree->data.darg.tag, nest + 1);
         NEST1("nxt:");
            tree_print(tree->data.darg.nxt, nest + 1);
         break;
      default:
         log_err("%d", __LINE__);
   }

   end:
      free(spaces);
      free(color);
      free(bcolor);
      return;
}

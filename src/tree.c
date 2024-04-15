#include "include/tree.h"

tree_t* tree_init(tree_type_t type, tree_t* parent) {
   tree_t* tree;

   tree = emalloc(sizeof(tree_t));

   tree->type = type;

   tree->parent = parent;
   
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

   // Stop calls from being double freed.
   if (tree->parent && tree->type == TREE_TYPE_CALL) {
      tree_t* treep = tree->parent;
      switch (treep->type) {
         case TREE_TYPE_BLOCK:
            treep->data.block.val = NULL;
            break;
         case TREE_TYPE_EXPR:
            treep->data.expr.val = NULL;
            break;
         case TREE_TYPE_CARG:
            treep->data.carg.val = NULL;
            break;
         case TREE_TYPE_DEF:
            treep->data.def.val = NULL;
            break;
         default:
            break;
      }
   }

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

tree_t* tree_copy_out(tree_t* tree) {
   tree_t* newt = tree_init(tree->type, tree->parent);
   memcpy(&newt->data, &tree->data, sizeof(newt->data));
   return newt;
}

int tree_cmp(tree_t* tree_0, tree_t* tree_1) {
   if ((tree_0 && !tree_1) || (!tree_0 && tree_1)) { return 0; }  /* Only 1 is defined (failure). */
   if (!tree_0 && !tree_1) { return 1; }  /* Both are undefined (success). */
   if (tree_0->type != tree_1->type) { return 0; } /* Types do not match (failure). */

   switch (tree_0->type) {
      case TREE_TYPE_BLOCK:
         return tree_cmp(tree_0->data.block.val, tree_1->data.block.val) &&
            tree_cmp(tree_0->data.block.nxt, tree_1->data.block.nxt);
         break;
      case TREE_TYPE_EXPR:
         return tree_cmp(tree_0->data.expr.val, tree_1->data.expr.val);
         break;
      case TREE_TYPE_LINT:
         return tree_0->data.lint.val == tree_1->data.lint.val;
         break;
      case TREE_TYPE_LSTR:
         return strcmp(tree_0->data.lstr.val, tree_1->data.lstr.val) == 0;
         break;
      case TREE_TYPE_TAG:
         return (strcmp(tree_0->data.tag.val, tree_1->data.tag.val) == 0) &&
            tree_cmp(tree_0->data.tag.nxt, tree_1->data.tag.nxt);
         break;
      case TREE_TYPE_DARG:
         return tree_cmp(tree_0->data.darg.tag, tree_1->data.darg.tag) &&
            tree_cmp(tree_0->data.darg.nxt, tree_1->data.darg.nxt);
         break;
      case TREE_TYPE_CARG:
         return tree_cmp(tree_0->data.carg.val, tree_1->data.carg.val) &&
            tree_cmp(tree_0->data.carg.nxt, tree_1->data.carg.nxt);
         break;
      case TREE_TYPE_DEF:
         return tree_cmp(tree_0->data.def.tag, tree_1->data.def.tag) &&
            tree_cmp(tree_0->data.def.arg, tree_1->data.def.arg) &&
            tree_cmp(tree_0->data.def.val, tree_1->data.def.val);
         break;
      case TREE_TYPE_CALL:
         return (strcmp(tree_0->data.call.target, tree_1->data.call.target) == 0) &&
            tree_cmp(tree_0->data.call.arg, tree_1->data.call.arg);
         break;
      default:
         LOG_WAR("Unknown tree type.");
   }

   return 0;
}

void tree_rm(tree_t* t) {
   tree_t* parent = t->parent;

   t->parent = NULL;

   switch (parent->type) {
      case TREE_TYPE_BLOCK:
         if (parent->data.block.val == t) parent->data.block.val = NULL;
         else parent->data.block.nxt = NULL;
         break;
      case TREE_TYPE_EXPR: // Deprecated?
         parent->data.expr.val = NULL;
         break;
      case TREE_TYPE_TAG:
         parent->data.tag.nxt = NULL;
         break;
      case TREE_TYPE_DARG:
         if (parent->data.darg.tag == t) parent->data.darg.tag = NULL;
         else parent->data.darg.nxt = NULL;
         break;
      case TREE_TYPE_CARG:
         if (parent->data.carg.val == t) parent->data.carg.val = NULL;
         else parent->data.carg.nxt = NULL;
         break;
      case TREE_TYPE_DEF:
         if (parent->data.def.tag == t) parent->data.def.tag = NULL;
         else if (parent->data.def.arg == t) parent->data.def.arg = NULL;
         else parent->data.def.val = NULL;
         break;
      case TREE_TYPE_CALL:
         parent->data.call.arg = NULL;
         break;
      default:
         LOG_WAR("Fscked state reached.");
         break;
   }
}

void tree_swp_call(tree_t* t0, tree_t* t1) {
   tree_t* parent = t0->parent;

   tree_rm(t0);

   t1->parent = parent;

   switch (parent->type) {
      case TREE_TYPE_BLOCK:
         parent->data.block.val = t1;
         break;
      case TREE_TYPE_EXPR:
         parent->data.expr.val = t1;
         break;
      case TREE_TYPE_CARG:
         parent->data.carg.val = t1;
         break;
      case TREE_TYPE_DEF:
         parent->data.def.val = t1;
         break;
      default:
         break;
   }
}

/*
   Every time I think there's a problem with the parser, it turns out it's 
   just this stupid tree print function. Now it works. Never touching it 
   again. Ever.
*/
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
void tree_print(tree_t* tree, int nest) {
   char*sp;int nc, i;char*c;char*bc;for(i
   =0,sp=ecalloc(nest+1,sizeof(char)),sp[
   nest]='\0';i<=nest-1;sp[i++]=' ');nc=0
   +0x1f+nest%6;c=malloc(9*sizeof(char));
   ;bc=malloc(11*sizeof(char));sprintf(c,
   "\x1b[%dm",nc);sprintf(bc,"\x1b[%d;1m"
   ,nc);NULL;NULL;0x0;0;0;0;0;NULL;0x0;0;
   #define NEST0(T)LOG_RAWF("%s%s"T"\x1b"\
   "[0m -> %d\n",bc,sp,tree->parent?tree->parent->type:-1)
   #define NEST1(T)LOG_RAWF("%s%s"T"\x1b"\
   """""""""""""""""""""""""[0m\n",c,sp);
   #define NEST2(T)LOG_RAWF("%s \x1b[39;"\
   """""""""""""""49;4m%s\x1b[0m\n",sp,T)
   #define NEST3(T)LOG_RAWF("%s \x1b[39;"\
   """""""""""""""49;4m%d\x1b[0m\n",sp,T)
   if (!tree) { NEST2("NULL"); goto end;}
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
         LOG_ERRF("%d", __LINE__);
   }

   end:
      free(sp);
      free(c);
      free(bc);
      return;
}
#pragma GCC diagnostic warning "-Wunused-value"
#pragma GCC diagnostic warning "-Wmisleading-indentation"

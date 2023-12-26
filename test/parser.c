#include "include/test.h"
#include "../src/include/pp.h"
#include "../src/include/lexer.h"
#include "../src/include/tree.h"
#include "../src/include/parser.h"

unsigned int TESTS_RUN = 0, TESTS_PASSED = 0;

int main(int argc, char** argv) {
   tree_t* tree_0;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   tree_0 = tree_init(TREE_TYPE_BLOCK);
      tree_t* treep_00 = tree_0->data.block.val = tree_init(TREE_TYPE_EXPR);
         tree_t* treep_01 = treep_00->data.expr.val = tree_init(TREE_TYPE_DEF);
            tree_t* treep_02 = treep_01->data.def.tag = tree_init(TREE_TYPE_TAG);
               treep_02->data.tag.val = "int";
               tree_t* treep_03 = treep_02->data.tag.nxt = tree_init(TREE_TYPE_TAG);
                  treep_03->data.tag.val = "f";
                  treep_03->data.tag.nxt = NULL;
            treep_01->data.def.arg = NULL;
            tree_t* treep_04 = treep_01->data.def.val = tree_init(TREE_TYPE_EXPR);
               tree_t* treep_05 = treep_04->data.expr.val = tree_init(TREE_TYPE_BLOCK);
                  tree_t* treep_06 = treep_05->data.block.val = tree_init(TREE_TYPE_EXPR);
                     tree_t* treep_07 = treep_06->data.expr.val = tree_init(TREE_TYPE_CALL);
                        treep_07->data.call.target = "a";
                        tree_t* treep_08 = treep_07->data.call.arg = tree_init(TREE_TYPE_CARG);
                           tree_t* treep_09 = treep_08->data.carg.val = tree_init(TREE_TYPE_EXPR);
                              tree_t* treep_10 = treep_09->data.expr.val = tree_init(TREE_TYPE_CALL);
                                 treep_10->data.call.target = "b";
                                 treep_10->data.call.arg = NULL;
                           treep_08->data.carg.nxt = NULL;
                  tree_t* treep_11 = treep_05->data.block.nxt = tree_init(TREE_TYPE_BLOCK);
                     tree_t* treep_12 = treep_11->data.block.val = tree_init(TREE_TYPE_EXPR);
                        tree_t* treep_13 = treep_12->data.expr.val = tree_init(TREE_TYPE_CALL);
                           treep_13->data.call.target = "c";
                           tree_t* treep_14 = treep_13->data.call.arg = tree_init(TREE_TYPE_CARG);
                              tree_t* treep_15 = treep_14->data.carg.val = tree_init(TREE_TYPE_EXPR);
                                 tree_t* treep_16 = treep_15->data.expr.val = tree_init(TREE_TYPE_CALL);
                                    treep_16->data.call.target = "d";
                                    treep_16->data.call.arg = NULL;
                              treep_14->data.carg.nxt = NULL;
                     treep_11->data.block.nxt = NULL;
      tree_0->data.block.nxt = NULL;

   /*
   
   [block]
      

   */

   char src_0[] = "" \
      ":int:f = {" \
      "a.b;" \
      "c.d"
      "}";

   pp = pp_init(src_0);
   pp_run(pp);

   lexer = lexer_init(pp->psrc);
   lexer_run(lexer);

   parser = parser_init(lexer->tokenl);
   parser_run(parser);

   ASSERT(tree_cmp(tree_0, parser->tree));

   pp_destroy(pp);
   parser_destroy(parser);
   lexer_destroy(lexer);

   TEST_REPORT;

   return 0;
}

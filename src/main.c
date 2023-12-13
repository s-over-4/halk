#include <stdio.h>
#include <stdlib.h>

#include "include/test.h"

#include "include/util.h"
#include "include/source.h"
#include "include/token.h"
#include "include/pp.h"
#include "include/lexer.h"
#include "include/parser.h"

int main(int argc, char* argv[]) {
   char*    src;     /* the source "code" */
   pp_t*    pp;
   lexer_t* lexer;
   parser_t* parser;

   /* get source */
   src = source_get(argv[1]); 
   log_dbg("source gotten");
   log_inf("source: %s", src);

   ASSERT(src);

   /* create pre-processor */
   pp = pp_init(src);
   log_dbg("preprocessor created");

   /* pre-process source */
   pp_run(pp);
   free(src);
   src = pp->psrc;
   log_inf("pre-processed source: %s", pp->psrc);
   /* destroy pre-processor */
   pp_destroy(pp);
   log_dbg("preprocessor ran");

   /* create lexer */
   lexer = lexer_init(src);
   log_dbg("lexer created");

   /* run lexer */
   lexer_run(lexer);
   log_dbg("lexer ran");

   /* Create the parser from the lexer's tokens. */
   parser = parser_init(lexer->tokenl);
   parser_run(parser);
   tree_print(parser->tree, 0);

   /* Clean up parser stuff. */
   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   free(src);

   TEST_REPORT;

   return 0;
}

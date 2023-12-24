#include "include/main.h"

#ifdef TEST
unsigned int TESTS_RUN;
unsigned int TESTS_PASSED;
#endif

int main(int argc, char* argv[]) {
   char*    src;
   pp_t*    pp;
   lexer_t* lexer;
   parser_t* parser;

   /* get source */
   src = source_get(argv[1]); 
   log_dbg("source gotten");
   log_inf("source: %s", src);

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

   /* Print the lexer's tokens. */
   token_print(lexer->tokenl);

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

   return 0;
}

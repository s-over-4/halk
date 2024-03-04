#include "include/main.h"
#include "include/doer.h"

/* FIXME: Segfaults ~30% of the time. No idea why. Thx future self <3. */
int main(int argc, char* argv[]) {
   char* src;
   pp_t* pp;
   lexer_t* lexer;
   parser_t* parser;

   /* Get source. */
   src = source_get(argv[1]); 
   LOG_INFF("Source: %s", src);

   /* Create pre-processor. */
   pp = pp_init(src);
   LOG_DBG("Preprocessor created.");

   /* Pre-process source. */
   pp_run(pp);
   free(src);
   src = pp->psrc;
   LOG_INFF("pre-processed source: %s", pp->psrc);
   /* destroy pre-processor */
   pp_destroy(pp);
   LOG_DBG("preprocessor ran");

   /* create lexer */
   lexer = lexer_init(src);
   LOG_DBG("lexer created");

   /* run lexer */
   lexer_run(lexer);
   LOG_DBG("lexer ran");

   /* Print the lexer's tokens. */
   token_print(lexer->tokenl);

   /* Create the parser from the lexer's tokens. */
   parser = parser_init(lexer->tokenl);
   parser_run(parser);
   tree_print(parser->tree, 0);

   doer_t* doer = doer_init(parser->tree);
   doer_do_block(doer);
   target_print(doer->targets);

   /* Clean up. */
   doer_destroy(doer);
   token_destroy(lexer->tokenl);
   lexer_destroy(lexer);
   tree_destroy(parser->tree);
   parser_destroy(parser);
   free(src);

   return 0;
}

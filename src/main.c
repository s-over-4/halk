#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/hlkt.h"
#include "include/source.h"
#include "include/token.h"
#include "include/pp.h"
#include "include/lexer.h"

int main(int argc, char* argv[]) {
   char*    src;     /* the source "code" */
   pp_t*    pp;
   lexer_t* lexer;

   /* get source */
   src = source_get(argv[1]); 
   HLKT_ASS(src);
   log_dbg("source gotten");
   log_inf("source: %s", src);

   /* create pre-processor */
   pp = pp_init(src);
   HLKT_ASS(pp);
   log_dbg("preprocessor created");

   /* pre-process source */
   pp_run(pp);
   free(src);
   src = pp->psrc;
   log_dbg(pp->psrc);
   /* destroy pre-processor */
   pp_destroy(pp);
   HLKT_ASS(src);
   log_dbg("preprocessor ran");

   /* create lexer */
   lexer = lexer_init(src);
   HLKT_ASS(lexer);
   HLKT_ASS(lexer->src == src);
   log_dbg("lexer created");

   /* run lexer */
   lexer_run(lexer);
   log_dbg("lexer ran");

   /* clean up lexer stuff */
   if (lexer->tokenl) { token_destroy(lexer->tokenl); } /* temp until parser eats tokens */
   lexer_destroy(lexer);
   free(src);

   HLKT_LOG();

   return 0;
}

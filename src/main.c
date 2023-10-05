#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/token.h"
#include "include/pp.h"
#include "include/lexer.h"
#include "include/source.h"
#include "include/hlkt.h"

int main(int argc, char* argv[]) {
   char*    src;     /* the source "code" */
   pp_t*    pp;
   lexer_t* lexer;

   /* get source */
   src = source_get(argv[1]); 
   HLKT_ASS(src);
   log_inf("source gotten");

   /* create pre-processor */
   pp = pp_init(src);
   HLKT_ASS(pp);
   log_inf("preprocessor created");

   /* pre-process source */
   pp_run(pp);
   free(src);
   src = pp->psrc;
   HLKT_ASS(src);
   log_inf("preprocessor ran");

   /* create lexer */
   lexer = lexer_init(src);
   HLKT_ASS(lexer);
   log_inf("lexer created");

   /* run lexer */
   lexer_run(lexer);
   log_inf("lexer ran");

   /* clean up */
   pp_destroy(pp);
   lexer_destroy(lexer);
   token_destroy(lexer->tokenl);
   free(src);

   HLKT_LOG();

   return 0;
}

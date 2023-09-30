#include <stdio.h>
#include <stdlib.h>

#include "include/util.h"
#include "include/token.h"
#include "include/pp.h"
#include "include/lexer.h"
#include "include/source.h"
#include "include/hlkt.h"

int main(int argc, char* argv[]) {
   char*    source;

   lexer_t* lexer;
   pp_t*    pp;

   source = source_get(argv[1]); 
   HLKT_ASS(source);
   log_inf("source gotten");
   log_inf("source: %s", source);

   pp = pp_init(source);
   HLKT_ASS(pp);
   log_inf("preprocessor created");

   pp_run(pp);
   free(source);
   source = pp->psrc;
   pp_destroy(pp);
   HLKT_ASS(source);
   log_inf("preprocessor ran");
   log_inf("preprocessed source: %s", source);

   /*
   lexer = lexer_init(source);
   HLKT_ASS(lexer);
   log_inf("lexer created");

   lexer_run(lexer);

   lexer_destroy(lexer);
   */
   free(source);
   /*free(pp->psrc);*/


   HLKT_LOG();

   return 0;
}

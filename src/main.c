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
   /*lexer_t* lexer;*/
   /*int      in_file;*/
   pp_t*    pp;

   source = source_get(argv[1]); 

   pp = pp_init(source);
   HLKT_ASS(pp);
   log_inf("preprocessor created");

   /*
   lexer = lexer_init(source);
   HLKT_ASS(lexer);
   log_inf("lexer created");

   log_inf("BEGIN INPUT");
   log_raw(lexer->content);
   log_inf("END INPUT");

   in_file = 1;
   */

   pp_run(pp);

   log_raw("%s\n%s", source, pp->psrc);

   // clean up
   /*lexer_destroy(lexer);*/
   pp_destroy(pp);

   free(source);

   HLKT_LOG();

   return 0;
}

#include <stdio.h>
#include <stdlib.h>


#include "include/log.h"
#include "include/lexer.h"
// #include "include/tree.h"
// #include "include/parser.h"


int main(int argc, char* argv[]) {
   FILE *fsource;
   long fsource_size;
   char *source;

      fsource = fopen ("examples/hello.halk", "rb");
   if (!fsource) { 
      log_err("Source file not found");
      exit(1); 
   };

   fseek(fsource, 0L, SEEK_END);
   fsource_size = ftell(fsource);
   rewind(fsource);

   source = calloc(1, fsource_size + 1);

   if (!source) { 
      fclose(fsource); 
      log_err("Memory allocation failed");
      exit(1); 
   }

   if (1 != fread(source, fsource_size, 1, fsource)) {
      fclose(fsource); 
      free(source);
      log_err("Could not read source file");
      exit(1);
   }

   log_inf("Source file loaded");

   lexer_t* lexer = lexer_init(source);
   log_inf("Lexer created");

   log_inf("== BEGIN INPUT ==");
   log_inf(lexer->content);
   log_inf("=== END INPUT ===");

   token_t* token = NULL;

   while ((token = lexer_get_next_token(lexer)) != NULL) {
      printf("===\ntoken type: %d:\ntoken value: || %s ||\n===\n", token->type, token->value);
   }

   //parser_t* parser = parser_init(lexer);
   //log_inf("Parser created");

   //tree_t* tree = parser_parse(parser);
   //log_inf("Tree root created");

   //printf("TYPE: [%d]\n", tree->type);
   //printf("SIZE: [%d]\n", tree->data.subtree.size);

   fclose(fsource);

   log_inf("Source file closed");

   return 0;
}

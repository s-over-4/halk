#include <stdio.h>
#include "include/lexer.h"

int main(int argc, char* argv[]) {
   lexer_t* lexer = lexer_init(
      "[a simple test script]\nlet it = \"Hello, World!\";\nsay it;"
   );

   printf("\n=== INPUT =======\n%s\n=== END INPUT ===\n", lexer->content);

   token_t* token = NULL;

   while ((token = lexer_get_next_token(lexer)) != NULL) {
      printf("===\ntoken type: %d\ntoken value: %s\n===\n", token->type, token->value);
   }

   return 0;
}

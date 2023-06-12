#include <stdlib.h>

#include "include/token.h"


// token constructor
token_t* token_init(int type, char* val) {
   token_t* token = calloc(1, sizeof(struct TOKEN_STRUC));
   token->type = type;
   token->value = val;

   return token;
}

int char_could_start_keyword(char* character) {
   for (int i = 0; i < TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS_LEN; ++ i) {
      if (TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS[i] == *character) {
         return 1;
      }
   }

   return 0;
}

int char_could_split_keyword(char* character) {
   if (char_could_start_keyword(character)) {
      return 1;
   } else {
      for (int i = 0; i < TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS_LEN; ++ i) {
         if (TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS[i] == *character) {
            return 1;
         }
      }

      return 0;
   }
}

int char_could_start_int(char* character) {
   for (int i = 0; i < 10; ++ i) {
      if (TOKEN_CHAR_FIRST_CHAR_INT[i] == *character) {
         return 1;
      }
   }

   return 0;
}

int char_can_ignore(char* character) {
   for (int i = 0; i < TOKEN_CHAR_IGNORE_LEN; ++ i) {
      if (TOKEN_CHAR_IGNORE[i] == *character) {
         return 1;
      }
   }

   return 0;
}

#include <stdlib.h>

#include "include/token.h"

// token constructor
token_t* token_init(int type, char* val) {
   token_t* token = calloc(1, sizeof(struct TOKEN_STRUC));
   token->type = type;
   token->value = val;

   return token;
}

char* token_get_type(int type) {
   switch (type) {
      case TOKEN_KEYWORD:
         return "TOKEN_KEYWORD";
         break;
      case TOKEN_PRIM_STR:
         return "TOKEN_PRIM_STR";
         break;
      case TOKEN_PRIM_INT:
         return "TOKEN_PRIM_INT";
         break;
      case TOKEN_COMM:
         return "TOKEN_COMM";
         break;
      case TOKEN_STMNT_END:
         return "TOKEN_EXPR_END";
         break;
      case TOKEN_LGROUP:
         return "TOKEN_LGROUP";
         break;
      case TOKEN_RGROUP:
         return "TOKEN_RGROUP";
         break;
      case TOKEN_DIRECTIVE:
         return "TOKEN_DIRECTIVE";
         break;
      case TOKEN_FN_APPLY:
         return "TOKEN_FN_APPLY";
         break;
      case TOKEN_LIST_DELIM:
         return "TOKEN_LIST_DELIM";
         break;
      case TOKEN_DEF_TAG:
         return "TOKEN_DEF_TAG";
         break;
      case TOKEN_BLOCK_START:
         return "TOKEN_BLOCK_START";
         break;
      case TOKEN_BLOCK_END:
         return "TOKEN_BLOCK_END";
         break;
      case TOKEN_NAMESPACE_DELIM:
         return "TOKEN_NAMESPACE_DELIM";
         break;
      case TOKEN_ARRAY_START:
         return "TOKEN_ARRAY_START";
         break;
      case TOKEN_ARRAY_END:
         return "TOKEN_ARRAY_END";
         break;
      case TOKEN_DEF_SET:
         return "TOKEN_DEF_SET";
         break;
      case TOKEN_UNKNOWN:
         return "TOKEN_UNKNOWN";
         break;
      case TOKEN_EOF:
         return "TOKEN_EOF";
         break;
      default:
         return "???";
   }
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


int token_char_quote(char c) { return (c != '\''); }
int token_char_grave(char c) { return (c != '`'); }
int token_char_pound(char c) { return (c != '#'); }
int token_char_colon(char c) { return (c != ':'); }
int token_char_kywrd(char c) { return (char_could_split_keyword(&c)); }

void token_destroy(token_t* token) {
   free(token->value);
   free(token);
}

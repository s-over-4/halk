#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


#include "include/log.h"
#include "include/lexer.h" 
#include "include/token.h"


lexer_t* lexer_init(char* content) {
   lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUC));

   lexer->content = content;
   lexer->i = 0;
   lexer->c = content[lexer->i];

   return lexer;
}

void lexer_destroy(lexer_t* lexer) {
   free(lexer->content);
   free(lexer);
}

void lexer_next(lexer_t* lexer) {
   if (LEXER_VALID) {
      lexer->i += 1;
      lexer->c = lexer->content[lexer->i]; 
   }
}

void lexer_pass(lexer_t* lexer) {
   while (char_can_ignore(&lexer->c)) {
      lexer_next(lexer);
   }
}

token_t* lexer_get_next_token(lexer_t* lexer) {
   while (LEXER_VALID) {

      if (char_can_ignore(&lexer->c)) { 
         lexer_pass(lexer); 
      }

      if (char_could_start_keyword(&lexer->c)) { 
         return lexer_get_keyword(lexer); 
      }

      switch (lexer->c) {
         case '\'':
            return lexer_get_string(lexer); 
            break;
         case '`': 
            return lexer_get_comment(lexer); 
            break;
         case ';':
            return lexer_next_token(
                  lexer,
                  token_init(
                     TOKEN_EXPR_END,
                     lexer_get_c_as_string(lexer)
                     )
                  );
            break;
         case '=':
            return lexer_get_def_const(lexer); break;
         case '-':
            return lexer_get_def_mut(lexer); break;
         case '(': return lexer_next_token(
            lexer,
            token_init(
               TOKEN_LGROUP,
               lexer_get_c_as_string(lexer)
            )
         ); break;
         case ')': return lexer_next_token(
            lexer,
            token_init(
               TOKEN_RGROUP,
               lexer_get_c_as_string(lexer)
            )
         ); break;
         case '#':
            return lexer_get_directive(lexer); break;
         case '.': return lexer_next_token(
             lexer,
             token_init(
                TOKEN_FN_APPLY,
                lexer_get_c_as_string(lexer)
                )
             ); break;
         case ',': return lexer_next_token(
             lexer,
             token_init(
                TOKEN_LIST_DELIM,
                lexer_get_c_as_string(lexer)
                )
             ); break;
         case ':': return lexer_next_token(
             lexer,
             token_init(
                TOKEN_VAR_DEF_ARGS_DELIM,
                lexer_get_c_as_string(lexer)
                )
             ); break;
         case '{': return lexer_next_token(
             lexer,
             token_init(
                TOKEN_BLOCK_DELIM_START,
                lexer_get_c_as_string(lexer)
                )
             ); break;
         case '}': return lexer_next_token(
             lexer,
             token_init(
                TOKEN_BLOCK_DELIM_END,
                lexer_get_c_as_string(lexer)
                )
             ); break;
         case '\0': return token_init(TOKEN_EOF, lexer_get_c_as_string(lexer)); break;
         default:
            log_err("Unrecognized token");
            exit(1);
      }
   }

   return NULL;
}

token_t* lexer_next_token(lexer_t* lexer, token_t* token) {
   lexer_next(lexer);

   return token;
}

char* lexer_get_c_as_string(lexer_t* lexer) {
   char* str = calloc(2, 1 * sizeof(char));
   str[0] = lexer->c;
   str[1] = '\0';
   
   return str;
}

// TODO: abstract away this kind of thing
token_t* lexer_get_array(lexer_t* lexer) {
   lexer_next(lexer);   // skip opening [
   char* array_so_far = calloc(1, sizeof(char));
   array_so_far[0] = '\0';

   while (lexer->c != ']') {
      char* current = lexer_get_c_as_string(lexer);
      array_so_far = realloc(
         array_so_far,
         (strlen(array_so_far) + strlen(current) * sizeof(char))
      );

      strcat(array_so_far, current);
      lexer_next(lexer);
   }

   lexer_next(lexer);   // skip over closing ]

   return token_init(TOKEN_STR, array_so_far); // return the collected array
}

token_t* lexer_get_string(lexer_t* lexer) {
   lexer_next(lexer);
   char* str_so_far = calloc(1, sizeof(char));
   str_so_far[0] = '\0';

   while (lexer->c != '\'') {
      char* current = lexer_get_c_as_string(lexer);
      str_so_far = realloc(
            str_so_far, 
            (strlen(str_so_far) + strlen(current) * sizeof(char))
      );

      strcat(str_so_far, current);
      lexer_next(lexer);
   }

   lexer_next(lexer);   // skip over closing '

   return token_init(TOKEN_STR, str_so_far); // return the collected string
}

token_t* lexer_get_comment(lexer_t* lexer) {
   lexer_next(lexer);

   char* comment_so_far = calloc(1, sizeof(char));

   while (lexer->c != '`') {
      char* current = lexer_get_c_as_string(lexer);
      comment_so_far = realloc(
            comment_so_far, 
            (strlen(comment_so_far) + strlen(current) * sizeof(char))
      );

      strcat(comment_so_far, current);
      lexer_next(lexer);
   }

   lexer_next(lexer);   // skip over closing `

   return token_init(TOKEN_COMM, comment_so_far);
}

token_t* lexer_get_directive(lexer_t* lexer) {
   lexer_next(lexer);
   char* directive_so_far = calloc(1, sizeof(char));
   directive_so_far[0] = '\0';

   while (lexer->c != ';') {
      char* current = lexer_get_c_as_string(lexer);
      directive_so_far = realloc(
         directive_so_far, 
         (strlen(directive_so_far) + strlen(current) * sizeof(char))
      );

      strcat(directive_so_far, current);
      lexer_next(lexer);
   }

   lexer_next(lexer);   // skip over closing ;

   return token_init(TOKEN_DIRECTIVE, directive_so_far);
}

token_t* lexer_get_keyword(lexer_t* lexer) {
   char* keyword_so_far = calloc(1, sizeof(char));
   keyword_so_far[0] = '\0';
   while (char_could_split_keyword(&lexer->c)) {
      char* current = lexer_get_c_as_string(lexer);
      keyword_so_far = realloc(
         keyword_so_far,
         (strlen(keyword_so_far) + strlen(current) * sizeof(char))
      );

      strcat(keyword_so_far, current);
      lexer_next(lexer);
   }

   return token_init(TOKEN_KEYWORD, keyword_so_far);
}

token_t* lexer_get_def(lexer_t* lexer) {
   char* def_so_far = calloc(1, sizeof(char));
   def_so_far[0] = '\0';
   while (lexer->c != '=') {
      char* current = lexer_get_c_as_string(lexer);
      def_so_far = realloc(
         def_so_far,
         (strlen(def_so_far) + strlen(current) * sizeof(char))
      );

      strcat(def_so_far, current);
      lexer_next(lexer);
   }

   return token_init(TOKEN_DEF, def_so_far);
}

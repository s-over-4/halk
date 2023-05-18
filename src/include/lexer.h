#ifndef LEXER_H
#define LEXER_H


#include "token.h"


typedef struct LEXER_STRUC {
   char c;           // current character in content
   unsigned int i;   // index of c
   char* content;    // the code itself
} lexer_t;


// constructor / destroyer
extern lexer_t* lexer_init(char* content);
extern void lexer_destroy(lexer_t* lexer);

// advance the lexer
extern void lexer_next(lexer_t* lexer);
extern void lexer_pass(lexer_t* lexer);
extern token_t* lexer_get_next_token(lexer_t* lexer);
extern token_t* lexer_next_token(lexer_t* lexer, token_t* token);
extern char* lexer_get_c_as_string(lexer_t* lexer);

// collectors
extern token_t* lexer_get_array(lexer_t* lexer);
extern token_t* lexer_get_string(lexer_t* lexer);
extern token_t* lexer_get_comment(lexer_t* lexer);

// def collectors
extern token_t* lexer_get_directive(lexer_t* lexer);
extern token_t* lexer_get_keyword(lexer_t* lexer);
extern token_t* lexer_get_def(lexer_t* lexer);

// <mut:?><type:><name>=<value?>
   // get the definition
   extern token_t* lexer_get_def(lexer_t* lexer);
   // looks for mut: or immut:
   extern token_t* lexer_get_def_mutability(lexer_t* lexer);
   // get the type of the definition, with syntax <type>:
   extern token_t* lexer_get_def_type(lexer_t* lexer);
   // get the name of the definition
   extern token_t* lexer_det_def_name(lexer_t* lexer);
   // calls either get_def_var or get_def_fn
   extern token_t* lexer_get_def_deftype(lexer_t* lexer);

// get a var def
extern token_t* lexer_get_def_var(lexer_t* lexer);
// get the var value
extern token_t* lexer_get_var_value(lexer_t* lexer);

// get a fn def
extern token_t* lexer_get_fn_def(lexer_t* lexer);
// get the fn args -- calls get get_def_mut and get_def_type and get_def_name
// for each
extern token_t* lexer_get_fn_args(lexer_t* lexer);
// get the fn body
extern token_t* lexer_get_fn_body(lexer_t* lexer);


#endif

#ifndef PP_H
#define PP_H

#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "syntax.h"

/* TODO */
typedef struct MACRO_STRUC {
   char* id;
   char* val;
} macro_t;

/* 
   preprocessor struct

   TODO: keep track of macros
*/
typedef struct PP_STRUC {
   /* original source */
   char* src;

   /* pre-processed source */
   char* psrc;

   /* what the preprocessor is looking at right now */
   enum PP_STATE {
      PP_STATE_REG,  /* regular */
      PP_STATE_STR,  /* string */
      PP_STATE_COM,  /* comment */
      PP_STATE_ESC,  /* escaped character in string */
      /* PP_STATE_MCO, */  /* macro */
   } state;
} pp_t;

/* creates a new preprocessor from some source code */
pp_t* pp_init(char*);

/* destroys the preprocessor **but not the pre-processed source** */
void pp_destroy(pp_t*);

/* copy over the current character from src to psrc */
void pp_cpy_char(pp_t*);

void pp_do_reg(pp_t*);
void pp_do_str(pp_t*);
void pp_do_com(pp_t*);

/* run the preprocessor */
void pp_run(pp_t*);

#endif


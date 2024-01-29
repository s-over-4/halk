#ifndef PP_H
#define PP_H

#include "util.h"
#include "syntax.h"

/* TODO */
typedef struct MACRO_STRUC {
   char* id;
   char* val;
} macro_t;

/* 
   The preprocessor struct.

   TODO: Keep track of macros.
*/
typedef struct PP_STRUC {
   /* Original source. */
   char* src;

   /* Pre-processed source. */
   char* psrc;

   /* What the preprocessor is looking at right now. */
   enum PP_STATE {
      PP_STATE_REG,  /* Regular. */
      PP_STATE_STR,  /* String. */
      PP_STATE_COM,  /* Comment. */
      PP_STATE_ESC   /* Escaped character in string. */
      /* PP_STATE_MCO, */  /* Macro. */
   } state;
} pp_t;

/* Creates a new preprocessor from some source code. */
pp_t* pp_init(char*);

/*
   Destroys a preprocessor.
   - Does not free the pre-processed source.
*/
void pp_destroy(pp_t*);

/* Copy over the current character from src to psrc. */
void pp_cpy_char(pp_t*);

void pp_do_reg(pp_t*);
void pp_do_str(pp_t*);
void pp_do_com(pp_t*);

/* Run the preprocessor. */
void pp_run(pp_t*);

#endif

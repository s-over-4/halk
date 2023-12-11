#include "include/pp.h"

pp_t* pp_init(char* src) {
   pp_t* pp;

   pp = ecalloc(1, sizeof(pp_t));

   pp->src = src;
   pp->psrc = (char*) emalloc(1);
   pp->psrc[0] = '\0';

   pp->state = PP_STATE_REG;

   return pp;
}

void pp_destroy(pp_t* pp) {
   free(pp);
}

void pp_cpy_char(pp_t* pp) {
   int plen = strlen(pp->psrc);
   pp->psrc = erealloc(pp->psrc, (plen + 2) * sizeof(char));

   pp->psrc[plen] = *pp->src;
   pp->psrc[plen + 1] = '\0';
}

void pp_do_reg(pp_t* pp) {
   switch (*pp->src) {
      case SYNTAX_COMMENT_DELIM:
         pp->state = PP_STATE_COM; 
         break;
      case SYNTAX_STR_DELIM:
         pp_cpy_char(pp);
         pp->state = PP_STATE_STR;
         break;
      case ' ': 
      case '\n':
      case '\r':
      case '\t':
         /* skip whitespace */
         break;

      default:
         pp_cpy_char(pp);
   }
}

void pp_do_str(pp_t* pp) {
   if (pp->state == PP_STATE_ESC) {
      pp_cpy_char(pp);
      pp->state = PP_STATE_STR;
   } else {
      if (*pp->src == SYNTAX_ESC) {
         pp_cpy_char(pp);
         pp->state = PP_STATE_ESC;
      } else if (*pp->src == SYNTAX_STR_DELIM) {
         pp_cpy_char(pp);
         pp->state = PP_STATE_REG;
      }
      else {
         pp_cpy_char(pp);
      }
   }
}

void pp_do_com(pp_t* pp) {
   if (*pp->src == SYNTAX_COMMENT_DELIM) {
      pp->state = PP_STATE_REG;
   }

   /* let pp_run skip chars in comments */
}

void pp_run(pp_t* pp) {
   while (*pp->src) {
      switch (pp->state) {
         case PP_STATE_REG:
            pp_do_reg(pp);
            break;
         case PP_STATE_STR:
         case PP_STATE_ESC:
            pp_do_str(pp);
            break;
         case PP_STATE_COM:
            pp_do_com(pp);
            break;
      }

      pp->src ++;
   }
}

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "util.h"

#define STACK_MAXLEN 256

typedef struct STACK {
   int sp;  /* Index of first unused element of val. */
   void* val[STACK_MAXLEN];
} stack_t;

stack_t* stack_init();
void stack_destroy(stack_t*);

void stack_push(stack_t* stack, void* val);
void* stack_pop(stack_t* stack);
size_t stack_len(stack_t* stack);

void stack_print(stack_t* stack);

#endif

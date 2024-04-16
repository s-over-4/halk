#include "include/stack.h"

// Not actually used anywhere, might be name collision on clang.

stack_t* stack_init() {
   stack_t* stack = emalloc(sizeof(stack_t));
   
   stack->sp = 0;
   for (int i = 0; i < STACK_MAXLEN; stack->val[i++] = 0);
   
   return stack;
}

void stack_destroy(stack_t* stack) {
   free(stack);
}

void stack_push(stack_t* stack, void* val) {
   stack->val[stack->sp++] = val;
}

void* stack_pop(stack_t* stack) {
   void* tmpval;

   tmpval = stack->val[--stack->sp];
   stack->val[stack->sp] = NULL;

   return tmpval;
}

size_t stack_len(stack_t* stack) {
   return stack->sp - 1;
}

void stack_print(stack_t* stack) {
   LOG_INFF("stack_print(): %p", stack);
   for (int i = stack_len(stack) - 1; i >= 0; --i) {
      LOG_INFF("%d: %p", i, stack[i]);
   }
}

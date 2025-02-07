
#ifndef STACK_H
#define STACK_H

#include "element.h"
#include "types.h"

typedef struct _Stack Stack;

Stack * stack_init ();
void stack_free(Stack* stack);
Status stack_push(Stack* stack, const Element* pe);
Element * stack_pop(Stack* stack);
Element * stack_top(const Stack* stack);
Bool stack_isEmpty(const Stack* stack);
Bool stack_isFull(const Stack* stack);
int stack_print(FILE* f, const Stack* stack);
Status reverseWords (const char *strin);

#endif /* STACK_H */

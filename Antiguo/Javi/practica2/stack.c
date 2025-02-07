

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "element.h"

#define MAXSTACK 1024

struct _Stack{
  int top;
  Element* item[MAXSTACK];
};

Stack * stack_init (){
  Stack* ps=NULL;
  int i;

  ps=(Stack*)malloc(sizeof(Stack));
  if(ps==NULL)
    return NULL;

  for(i=0;i<MAXSTACK;i++){
    ps->item[i]=NULL;
  }

  ps->top=-1;
  return ps;
}


void stack_free(Stack * stack){
  int i;
  if(!stack)
    return;

  for(i=0;i<MAXSTACK;i++){
    element_free(stack->item[i]);
    stack->item[i]=NULL;
  }

  free(stack);
  stack=NULL;
  return;
}


Status stack_push(Stack* stack, const Element* pe){
  Element* aux=NULL;
  if(!stack||!pe||stack_isFull(stack)==TRUE)
    return ERROR;

  aux=element_copy(pe);
  stack->top++;
  stack->item[stack->top]=aux;
  return OK;
}


Element * stack_pop(Stack* stack){
  Element* aux=NULL;
  if(!stack||stack_isEmpty(stack)==TRUE)
    return NULL;

  aux=stack->item[stack->top];
  stack->item[stack->top]=NULL;
  stack->top--;
  return aux;
}



Element * stack_top(const Stack* stack){
  if(!stack)
    return NULL;

  return stack->item[stack->top];
}


Bool stack_isEmpty(const Stack* stack){
  if(!stack)
    return FALSE;

  if(stack->top==-1)
    return TRUE;

  return FALSE;
}


Bool stack_isFull(const Stack* stack){
  if(!stack)
    return FALSE;

  if(stack->top==MAXSTACK-1)
    return TRUE;

  return FALSE;
}


int stack_print(FILE* f, const Stack* stack){
  int i,aux=0;

  if(!f||!stack)
    return -1;

  for(i=stack->top;i==0;i--){
    element_print(stdout,stack->item[i]);
    aux++;
  }
  
  return aux;
}

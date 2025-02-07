#include <stdlib.h>
#include <stdio.h>
#include "stack.h"



int main(int argc, char *argv[]){
  char* aux;
  Stack* stack=NULL;
  Element* el=NULL;
  char array[3]={'a','b','c'};
  int i;

  stack=stack_init();
  el=element_init();

  if(stack==NULL||el==NULL)
    return 1;

  for(i=0;i<3;i++){
    aux=&array[i];
    element_setInfo(el,aux);
    stack_push(stack,el);
  }

  element_free(el);
  stack_free(stack);
  return 1;
}

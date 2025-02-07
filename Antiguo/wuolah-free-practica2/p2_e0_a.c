
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"


#define MAX 3


int main(int argc, char** argv){
  Stack* s=NULL;
  char array[MAX]={'a','b','c'};
  int i;


  s=stack_init(char_free,char_copy,char_print);

  if(s==NULL)
    return 1;

  for(i=0;i<MAX;i++){
    stack_push(s,&array[i]);
  }

  stack_print(stdout,s);
  printf("Stack size: %ld\n",stack_size(s));

  while(stack_isEmpty(s)==FALSE){
    printf("El elemento extraido:");
    char_print(stdout,stack_top(s));
    char_free(stack_pop(s));
    printf("\n");
  }

  printf("Stack size: %ld\n",stack_size(s));
  stack_free(s);
  return 1;
}

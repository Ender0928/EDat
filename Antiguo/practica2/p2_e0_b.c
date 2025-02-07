
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"
#include "node.h"

#define MAX 100

int main(int argc, char** argv){
  Node* node=NULL;
  Stack* nodes=NULL;
  Stack* string=NULL;

  nodes=stack_init(node_free,node_copy,node_print);

  if(nodes==NULL)
    return 1;

  string=stack_init(string_free,string_copy,string_print);

  if(string==NULL)
    return 1;

  node=node_init();

  if(node==NULL)
    return 1;

  node_setName(node,"first");
  node_setId(node,111);
  node_setLabel(node,WHITE);
  node_setNConnect(node,0);

  if(stack_push(nodes,node)==ERROR)
    return 1;

  if(stack_push(string,node_getName(node))==ERROR)
    return 1;

  node_setName(node,"second");
  node_setId(node,222);
  node_setLabel(node,WHITE);
  node_setNConnect(node,0);

  if(stack_push(nodes,node)==ERROR)
    return 1;

  if(stack_push(string,node_getName(node))==ERROR)
    return 1;


  printf("Print stack nodes:\n");
  stack_print(stdout,nodes);
  printf("Print stack string:\n");
  stack_print(stdout,string);

  node_free(node);

  printf("Poping nodes....\n");
  while(stack_isEmpty(nodes)==FALSE){
    node=stack_pop(nodes);
    node_print(stdout,node);
    node_free(node);
  }

  printf("\n");
  printf("Poping nodes-names....\n");
  while(stack_isEmpty(string)==FALSE){
    string_print(stdout,stack_top(string));
    string_free(stack_pop(string));
    printf(" ");
  }

  printf("\n");
  stack_free(nodes);
  stack_free(string);
  return 1;
}

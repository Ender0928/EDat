
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#define MAX 100




int main(int argc,char *argv[]){
  FILE* f;
  char file_name[MAX];
  char delimitador[] = " ";
  char* toks = NULL;

  if (argc < 2) {
    fprintf(stderr, "Utiliza: %s <file_name>\n", argv[0]);
    return 1;
  }

  if (argc > 2){
    fprintf(stderr, "demasiados argumentos\n");
    return 1;
  }

  if(argc == 2){
    strcpy(file_name, &argv[1][0]);
    f = fopen(file_name, "w");
    if(f == NULL){
      fprintf(stdout, "error al abriendo el archivo\n");
      return 1;
    }
  }

  fprintf(stdout,"Input: %s ",file_name);
  fprintf(stdout,"\n");
  fprintf(stdout,"Output: ");
  toks=strtok(file_name,delimitador);

  if(toks!=NULL){
    while(toks!=NULL){
      if(reverseWords(toks)==ERROR){
        printf("error al invertir las palabras\n");
        return 1;
      }
      toks=strtok(NULL,delimitador);
    }
  }

  fprintf(stdout,"\n");
  fclose(f);
  return 1;
}



Status reverseWords (const char *strin){
  int i;
  Stack* stack=NULL;
  Element* element=NULL;
  stack=stack_init();
  element=element_init();

  if(stack==NULL||element==NULL){
    printf("error al inicializar la pila\n");
    return ERROR;
  }

  for(i=0;i<strlen(strin);i++){
  if(element_setInfo(element,&strin[i])==NULL){
    printf("error al hacer element_set\n");
    return 1;
    }

    if(stack_push(stack,element)==ERROR){
      printf("error al insertar los elementos en la pila\n");
      return 1;
    }

    stack_print(stdout,stack);
  }

  while(stack_isEmpty(stack)==FALSE){
    stack_print(stdout,stack);
    element_free(stack_pop(stack));
  }


  fprintf(stdout," ");
  element_free(element);
  stack_free(stack);
  return OK;
}

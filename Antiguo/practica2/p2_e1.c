
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"


#define MAX 100


Status reverseWords (char *strout, const char *strin);

int main(int argc,char *argv[]){
  FILE* f;
  char file_name[MAX];
  char reverse[MAX];
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
      if(reverseWords(reverse,toks)==ERROR){
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


Status reverseWords (char *strout, const char *strin){
  Stack* stack=NULL;
  int i;
  stack=stack_init(char_free,char_copy,char_print);

  if(stack==NULL){
    printf("error al inicializar la pila\n");
    return ERROR;
  }

  for(i=0;i<strlen(strin);i++){
    if(stack_push(stack,&strin[i])==ERROR){
      printf("error al insertar los elementos en la pila\n");
      return ERROR;
    }
  }

  i=0;

  while(stack_isEmpty(stack)==FALSE){
    strout[i]=char_print(stdout,stack_top(stack));
    char_free(stack_pop(stack));
    i++;
  }

  fprintf(stdout, " ");
  stack_free(stack);
  return OK;
}

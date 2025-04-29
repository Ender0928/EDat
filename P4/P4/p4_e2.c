#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "search_queue.h"
#include "types.h"
#include "vertex.h"

#define MAX_WORD 255

void program_exit(FILE *f_in, FILE *f_out, SearchQueue *sq, char *str){
  if(f_in!=NULL)
    fclose(f_in);

  if(f_out!=NULL)
    fclose(f_out);

  if(sq!=NULL){
    while(search_queue_isEmpty(sq)!=TRUE){
      str= (char*)search_queue_pop(sq);
      free(str);
    }
    search_queue_free(sq);
  }

  return;
}

int main(int argc, char **argv) {
  FILE *f_in=NULL, *f_out=NULL;
  SearchQueue *sq;
  char data[MAX_WORD] = "";
  char *str=NULL;

  if (argc < 2)
    return -1;

  if (!argv[1] || !argv[2])
    return -1;

  if(!(sq = search_queue_new(string_print, string_cmp))){
    return -1;
  }

  if (!(f_in = fopen(argv[1], "r"))){
    program_exit(f_in, f_out, sq, str);
    return -1;
  }

  if (!(f_out = fopen(argv[2], "w"))){
    program_exit(f_in, f_out, sq, str);
    return -1;
  }

  while (fgets(data, MAX_WORD, f_in)) {
    str = (char *)malloc(MAX_WORD * sizeof(char));
    
    if (!str){
      program_exit(f_in, f_out, sq, str);
      return -1;
    }

    if (!strcpy(str, data)){
      program_exit(f_in, f_out, sq, str);
      return -1;
    }

    if(search_queue_contains(sq,str)==TRUE) 
      free(str);/*Since if the element is contained it is not inserted, we have to free it*/

    else{
      if (search_queue_push(sq, (void *)str) == ERROR){
        program_exit(f_in, f_out, sq, str);
        return -1;
      }
    }


  }
  search_queue_print(f_out, sq);

  program_exit(f_in, f_out, sq, str);
  return 0;
}
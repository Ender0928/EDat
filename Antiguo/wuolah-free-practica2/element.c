

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "element.h"

struct _Element{
  char *a;
};

Element* element_init(){
  Element* new=(Element*)malloc(sizeof(Element));

  if(new==NULL)
    return NULL;

  new->a=NULL;

  return new;
}


void element_free(Element * element){
  if(!element)
    return;

  free(element);
  element=NULL;
  return;
}


Element* element_setInfo(Element * element,const void* el){
  if(!element||!el)
    return NULL;

  element->a=(char*)el;
  return element;
}


void* element_getInfo(Element * element){
  if(!element)
    return NULL;

  return element->a;
}

Element* element_copy(const Element* el){
  Element* aux=NULL;

  aux=element_init();

  if(!el||aux==NULL)
    return NULL;

  if(element_setInfo(aux,el->a)==NULL){
    element_free(aux);
    return NULL;
  }

  return aux;
}


Bool element_equals(const Element* el1, const Element* el2){
  if(!el1||!el2)
    return FALSE;

  if(el1->a==el2->a)
    return TRUE;

  return FALSE;
}


int element_print(FILE* f, const Element* element){
  if(!f||!element)
    return -1;

  fprintf(f,"%s",element->a);
  return 1;
}

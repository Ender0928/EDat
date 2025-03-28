#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* In list.c */
typedef struct _NodeList {
  void *data;
  struct _NodeList *next;
} NodeList;

struct _List {
  NodeList *last;
};

NodeList *node_new() {
  NodeList *pn = NULL;
  pn = (NodeList *)malloc(sizeof(NodeList));
  if (!pn) {
    return NULL;
  }
  pn->data = NULL;
  pn->next = NULL;
  return pn;
}

List *list_new() {
  List *l;
  if ((l = (List *)malloc(sizeof(List))) == NULL)
    return NULL;
  l->last = NULL;

  return l;
}

Bool list_isEmpty(const List *pl) {
  if (pl == NULL) {
    return TRUE;
  }
  if (pl->last == NULL) {
    return TRUE;
  }
  return FALSE;
}

Status list_pushFront(List *pl, void *e) {
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL) {
    return ERROR;
  }
  pn = node_new();
  if (pn == NULL) {
    return ERROR;
  }
  pn->data = e;
  if (list_isEmpty(pl)) {
    pn->next = pn;
    pl->last = pn;
  } else {
    pn->next = pl->last->next;
    pl->last->next = pn;
  }
  return OK;
}

Status list_pushBack(List *pl, void *e) {
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL) {
    return ERROR;
  }
  pn = node_new();
  if (pn == NULL) {
    return ERROR;
  }
  pn->data = e;
  if (list_isEmpty(pl) == TRUE) {
    pn->next = pn;
    pl->last = pn;
  } else {
    pn->next = pl->last->next;
    pl->last->next = pn;
    pl->last = pn;
  }
  return OK;
}

void *list_popFront(List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty(pl) == TRUE) {
    return NULL;
  }
  pn = pl->last->next;
  pe = pn->data;
  if (pl->last->next == pl->last) {
    pl->last = NULL;
  } else {
    pl->last->next = pn->next;
  }
  free(pn);
  return pe;
}

void *list_popBack(List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;
  if (pl == NULL || list_isEmpty(pl) == TRUE) {
    return NULL;
  }
  if (pl->last->next == pl->last) {
    pe = pl->last->data;
    free(pl->last);
    pl->last = NULL;
    return pe;
  }
  pn = pl->last;
  while (pn->next != pl->last) {
    pn = pn->next;
  }
  pe = pl->last->data;
  pn->next = pl->last->next;
  free(pl->last);
  pl->last = pn;
  return pe;
}

void list_free(List *pl) {
  NodeList *pn = NULL;
  int tam, i;
  if (pl == NULL) {
    return;
  }
  tam= list_size(pl);
  for(i=0;i<tam;i++) {
    pn = pl->last;
    pl->last = pn->next;
    free(pn->data);
    free(pn);
  }
  free(pl);
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order) {
  NodeList *pn = NULL, *pm = NULL;
  int i;
  int tam;
  Bool found=FALSE;

  if (!pl || !e || !f || order == 0) {
    return ERROR;
  }
  
  pn = node_new();
  if (pn == NULL) {
    return ERROR;
  }

  pn->data = (void *)e;

  if (list_isEmpty(pl) == TRUE) {
    pn->next = pn;
    pl->last = pn;
    return OK;
  }

  tam=list_size(pl);
  pm=pl->last;
  /*Searches where to insert the new node*/
  for(i=0; i< tam; i++){
    if (order < 0) {
      if(f(pm->data, pn->data) >= 0 && f(pm->next->data, pn->data) <= 0 ){
        found=TRUE;
        break;
      }
      pm=pm->next;
    }
    else {
      if(f(pm->data, pn->data) <= 0 && f(pm->next->data, pn->data) >= 0 ){
        found=TRUE;
        break;
      }
      pm=pm->next;
    }
  }

  /*If it is not found that leave us with two options, is either bigger or smaller that all 
  the elements in the list*/
  if(found==FALSE){
    if (order > 0) {
      if(f(pm->data, pn->data) < 0)
        list_pushBack(pl, e);
      else
        list_pushFront(pl, e); 
    }
    else {
      if(f(pm->data, pn->data) > 0)
        list_pushBack(pl, e);
      else
        list_pushFront(pl, e);
       
    }
    free(pn);
    return OK;
  }
  
  pn->next= pm->next;
  pm->next= pn;
  
  return OK;
}


size_t list_size(const List *pl) {
  NodeList *pn;
  long i = 0;
  if (!pl) {
    return -1;
  }

  pn = pl->last;

  /*Ya que el bucle es un do while, primero tenemos que ver si la lista está vacía para que no de segmentation fault*/
  if(list_isEmpty(pl)==TRUE){
    return 0;
  }

  do {
    i++;
    pn = pn->next;
  } while (pl->last != pn);

  return i;
}

  

int list_print(FILE * fp, const List *pl, P_ele_print f) {   
  NodeList *n;
  int i = 0, var;
  if (!fp || !pl || !f )
    return -1;

  i+=fprintf(fp, "SIZE: %ld\n", list_size(pl));

  if(list_isEmpty(pl)==TRUE){
    return i;
  }

  n = pl->last->next;
  /*From front to rear*/
  do{
    if((var = f(fp, n->data))<0){
      return var;
    }
    i += fprintf(fp," ");
    i += var; 
    n = n->next;
  } while (n != pl->last->next);
  fprintf(fp,"\n");
  
  return i;
} 

  

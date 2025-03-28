/**
 * @file  delivery.c
 * @author Profesores EDAT
 * @date 10 March 2023
 * @version 1.0
 * @brief Library to manage ADT Delivery
 *
 * @details
 *
 * @see
 */

#include <string.h>
#include <stdlib.h>
#include "delivery.h"

struct _Delivery {
  char *name;
  char *product_name;
  Queue *plan;
};

Delivery *delivery_init (char *name, char *productName){
	Delivery *d;

  if (!name || !productName){
    return NULL;
  }

	d = (Delivery*) malloc (sizeof(Delivery));
	if (!d){
    return NULL;
  }

  d->name = (char*) calloc(strlen(name)+1, sizeof(char));
  if (d->name == NULL){
    free(d);
    return NULL;
  }
  strcpy(d->name, name);
  
  d->product_name = (char*) calloc(strlen(productName)+1, sizeof(char));
  if (d->product_name == NULL){
    free(d->name);
    free(d);
    return NULL;
  }
  strcpy(d->product_name, productName);

  d->plan = queue_new();
  if (d->plan == NULL){
    free(d->name);
    free(d->product_name);
    free(d);
    return NULL;
  }

	return d;
}

void delivery_free (void *p){
  Delivery *d;

  if (p == NULL){
    return;
  }
  
  d = (Delivery*) p;

  free(d->name);
  free(d->product_name);
  queue_free(d->plan);
  free(d);
}

void delivery_free_products (Delivery *d, p_element_free ffree) {
  if (!(d)) {
    return;
  }

  while (queue_isEmpty(d->plan) == FALSE) {
    ffree(queue_pop(d->plan));
  }

  return;
}

const char *delivery_getName (const Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->name;
}

const char *delivery_getProductName (const Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->product_name;
}

Queue *delivery_getPlan (Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->plan;
}

Status delivery_add(FILE *pf, Delivery *d, void *p, p_element_print f){
  if(!pf|| !d|| !p|| !f)
    return ERROR;
  
  if(!queue_push(d->plan, p))
    return ERROR;

  fprintf(pf, "Adding:");
  f(pf, p);
  fprintf(pf, " to delivery: %s\n", d->name);
  
  return OK;
}

Status delivery_run_plan(FILE *pf, Delivery *d, p_element_print fprint, p_element_free ffree){
  void *v;
  Status s=ERROR;
  if(!pf|| !d|| !fprint|| !ffree)
    return ERROR;
  
  fprintf(pf, "Running delivery plan for queue:\n");
  queue_print(pf,d->plan, fprint);

  for(int i=0;(v=queue_pop(d->plan))!=NULL; i++){
    fprintf(pf, "Delivering %s requested by %s to", d->product_name, d->name);
    fprint(pf, v);
    fprintf(pf, "\n");
    ffree(v);
    s=OK;
  }

  return s;
}

int delivery_cmp (const void *p1, const void *p2){
  int c = 0;
  Delivery *d1, *d2;

  if ((p1 == NULL) || (p2 == NULL)){
    return c;
  }
  
  d1 = (Delivery*) p1;
  d2 = (Delivery*) p2;
  
  c = strcmp(d1->name, d2->name);
  if (c == 0){
    c = strcmp(d1->product_name, d2->product_name);
    if (c == 0){
      c = queue_size(d1->plan) - queue_size(d2->plan);
    }
  }
  
  return c;
}

void *delivery_copy (const void *src){
  Delivery *d, *trg;
  int plan_size, i;
  void *e;
  
  if (src == NULL){
    return NULL;
  }
  
  d = (Delivery*) src;
  trg = delivery_init(d->name, d->product_name);
  
  plan_size = queue_size(d->plan);
  for (i = 0; i<plan_size; i++){
    e = queue_pop(d->plan);
    queue_push(trg->plan, e);
    queue_push(d->plan, e);
  }
  
  return trg;
}

int delivery_print (FILE *pf, const void *p, p_queue_ele_print f){
  Delivery * d;
  int n=0;

  if ((pf == NULL) || (p == NULL)){
    return -1;
  }

  d = (Delivery*) p;
  n += fprintf(pf, "%s delivers %s\n", d->name, d->product_name);
  n += queue_print(pf, d->plan, f);

  return n;
}



Delivery* build_delivery(FILE * pf){
  Delivery *d;
  Vertex *v;
  char a[WRD], b[WRD];
  int tam;

  if(!pf)
    return NULL;
  
  if(fscanf(pf,"%s%s", a, b)!=2){
    return NULL;
  }

  if(!(d=delivery_init(a, b)))
    return NULL;

  if(fscanf(pf,"%d", &tam)!=1){
    delivery_free(d);
    return NULL;
  }

  for(int i=0;i<tam; i++){
    fscanf(pf,"%s %s",a, b);
    strcat(a," ");
    strcat(a, b);
    strcat(a," ");
    strcat(a,"state:0");
    if(!(v=vertex_initFromString(a)))
       return NULL;

    if(!(vertex_setIndex(v,0))){
      vertex_free(v);
      return NULL;
    } 

    if(!delivery_add(stdout, d, v, vertex_print)){
      vertex_free(v);
      return NULL;
    }
  }

  return d;
}

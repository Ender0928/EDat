#include "sorted_queue.h"
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------
SortedQueue *squeue_new() {
  return queue_new();  
}

//--------------------------------------------------------------------------
void squeue_free(SortedQueue *q) {
  queue_free(q);
}

/**
 * @brief  Inserta un elemento en la cola ordenada.
 *
 * TO-DO: Incluye aqui el pseudocodigo del algoritmo implementado.
 * 
 * @param q, puntero a la cola.
 * @param ele, puntero al elemento a insertar.
 * @param pcmp, puntero a la funcion de comparacion.
 *
 * @return OK si la insercion se realiza con exito, ERROR en caso contrario.
 **/
Status squeue_push(SortedQueue *q, void *ele, p_queue_ele_cmp pcmp) {
  Status st = OK;
  size_t size;
  void *aux;
  int contador=0;
  
  if(q == NULL || !ele || !pcmp)
      return ERROR;
  
  if(squeue_isEmpty(q) == TRUE) {
    queue_push(q, ele);
    return OK;
  }

  aux = squeue_getBack(q) ;
  
  if (pcmp(ele, aux) > 0) {
    queue_push(q, ele);
    return OK;
  }

  size = squeue_size(q);
  
  while (pcmp(squeue_getFront(q), ele) < 0) {
    aux = squeue_pop(q);
    queue_push(q, aux);
    size--;

  }

  if (pcmp(queue_getFront(q), ele) != 0)
    queue_push (q, ele);

  while (pcmp(squeue_getFront(q), ele) >= 0) {
    aux = squeue_pop(q);
    queue_push(q, aux);
    contador++;
    if (contador == size) return OK;
  }

  return st;
}

//--------------------------------------------------------------------------
void *squeue_pop(SortedQueue *q) {
  return queue_pop(q);
}

//--------------------------------------------------------------------------
void *squeue_getFront(const SortedQueue *q) {
  return queue_getFront(q);
}

//--------------------------------------------------------------------------
void *squeue_getBack(const SortedQueue *q) {
  return queue_getBack(q);
}

//--------------------------------------------------------------------------
Bool squeue_isEmpty(const SortedQueue *q) {
  return queue_isEmpty(q);
}

//--------------------------------------------------------------------------
size_t squeue_size(const SortedQueue *q) {
  return queue_size(q);
}

//--------------------------------------------------------------------------
int squeue_print(FILE *fp, const SortedQueue *q, p_queue_ele_print f) {
  return queue_print(fp, q, f);
}


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
  int contador;
  
  if(q == NULL || !ele || !pcmp)
      return ERROR;
  
  if(squeue_isEmpty == TRUE)
      return ERROR;
  
  size = squeue_size(q);
  aux = squeue_getBack(q);
  
  while(0 < pcomp(aux, ele) && st == OK){
      aux = squeue_pop(q);
      st = queue_push(q, aux)
      aux = squeue_getBack(q);
      size--;
  }
  
  st = queue_push(q, ele);
  
  aux = squeue_getBack(q); 
  while(aux > ele && contador < size)
  {
      aux = squeue_pop(q);
      st = queue_push(q, aux)
      aux = squeue_getBack(q);
      contador++;
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


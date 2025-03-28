//--------------------------------------------------------------------------
// Dequeue implementation with (void *)
//--------------------------------------------------------------------------

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_DEQUEUE
#define MAX_QUEUE 8
#endif

struct _Queue {
  void *data[MAX_QUEUE];
  void **front;
  void **rear;
};
/*FUNCION PRIVADA*/
Bool _queue_isFull(const Queue *pq);

Queue *queue_new() {
  Queue *pq = NULL;
  int i;
  pq = (Queue *)malloc(sizeof(Queue));
  if (pq == NULL) {
    return NULL;
  }
  for (i = 0; i < MAX_QUEUE; i++) {
    pq->data[i] = NULL;
  }
  pq->front = &(pq->data[0]);
  pq->rear = &(pq->data[0]);
  return pq;
}

void queue_free(Queue *pq) { free(pq); }

Bool queue_isEmpty(const Queue *pq) {
  if (pq == NULL) {
    return TRUE;
  }
  if (pq->front == pq->rear) {
    return TRUE;
  }
  return FALSE;
}

Bool _queue_isFull(const Queue *pq) {
  if (pq == NULL) {
    return TRUE;
  }
  if ((pq->rear + 1 - pq->front) % MAX_QUEUE == 0) {
    return TRUE;
  }
  return FALSE;
}

Status queue_push(Queue *pq, const void *e) {
  if (pq == NULL || e == NULL || _queue_isFull(pq) == TRUE) {
    return ERROR;
  }
  *(pq->rear) = (void *)e;
  pq->rear = pq->data + (pq->rear + 1 - pq->data) % MAX_QUEUE;
  /* Alt:
  pq->rear++; if (pq->rear == pq->data + MAX_QUEUE) pq->rear = pq->data;
  */
  return OK;
}

void *queue_pop(Queue *pq) {
  void *e = NULL;
  if (pq == NULL || queue_isEmpty(pq) == TRUE) {
    return NULL;
  }
  e = *(pq->front);
  *(pq->front) = NULL;
  pq->front = pq->data + (pq->front + 1 - pq->data) % MAX_QUEUE;
  /* Alt:
  pq->front++; if (pq->front == pq->data + MAX_QUEUE) pq->front = pq->data;
  */
  return e;
}

void *queue_getFront(const Queue *pq) {
  if (pq == NULL || queue_isEmpty(pq) == TRUE) {
    return NULL;
  }
  return *(pq->front);
}

void *queue_getBack(const Queue *pq) {
  void **last_elem;
  if (pq == NULL || queue_isEmpty(pq) == TRUE) {
    return NULL;
  }
  if (pq->rear == pq->data) {
    last_elem = ((Queue *)pq)->data + MAX_QUEUE - 1;
  } else {
    last_elem = pq->rear - 1;
  }
  return *last_elem;
}

size_t queue_size(const Queue *q) {
  if (q == NULL)
    return 0;
  if (queue_isEmpty(q) == TRUE)
    return 0;
  if (q->rear == q->front)
    return MAX_QUEUE;
  return (MAX_QUEUE + q->rear - q->front) % MAX_QUEUE;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print print_elem) {
  int i, num = 0, var, tam;

  if (fp == NULL || q == NULL || print_elem == NULL) {
    return -1;
  }

  tam = queue_size(q);

  for (i = num = 0; i < tam; i++) {
    if ((var = print_elem(fp, q->data[i])) < 0)
      return -1;
    num += var;
    num += fprintf(fp, " ");
  }
  num += fprintf(fp, "\n");

  return num;
}

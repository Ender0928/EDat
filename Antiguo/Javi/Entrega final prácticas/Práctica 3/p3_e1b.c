#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "sorted_queue.h"
#include "point.h"

#define NPOINTS 5
#define MAX_RAND 20




int string_cmp(const void *s1, const void *s2) {
    return strcmp((char *)s1, (char *)s2);
}

int num_cmp(const void *i1, const void *i2) {
    int e1, e2;

    e1 = (int *) i1;
    e2 = (int *) i2;

    if (e1 < e2) return -1;
    else if (e1 > e2) return 1;
    else return 0;
}

int main (int num_arguments, const char *arg[]) {
    SortedQueue *sq=NULL;
    Point *p[NPOINTS] = {NULL};
    Point *origen = NULL;
    int f, ins, x;
    int i;

    sq = squeue_new();
    if (sq == NULL) return 1;


    for (i=0; i<NPOINTS; i++) {
        x = rand() % MAX_RAND;
        queue_push(sq, x);
    }

    ins = 12;
    
    for (i=0; f < squeue_getFront(sq); i++) {
        x = squeue_pop(sq);
        queue_push(sq, x);
    }     

    queue_push(sq, ins);


    for (i=0; f >= squeue_getFront(sq); i++) {
        x = squeue_pop(sq);
        queue_push(sq, x);
    }     

    squeue_free(sq);
    return 0;
}







//srand(time(NULL));


    /*for (i=0; i<NPOINTS; i++) {
        p[i] = point_new(rand() % MAX_RAND , rand() % MAX_RAND, BARRIER);

        if (squeue_getFront(sq) < )

    }*/
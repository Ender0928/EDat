#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "sorted_queue.h"
#include "point.h"

#define MAX_NUM 16
#define NPOINTS 10

#define MAX_RAND 20




int string_cmp(const void *s1, const void *s2) {
    return strcmp((char *)s1, (char *)s2);
}

int string_print(FILE *pf, const void *p)
{
    char *v;
    
    if(p == NULL)
        return -1;

    v = (char *)p;   
        
    return fprintf(pf, "%s ", v);
    
}

int int_cmp(const void *c1, const void *c2) {
    if (!c1 || !c2)
        return INT_MIN;
        
    return (*(int *)c1 - *(int *)c2);
}

int int_print(FILE *pf, const void *p)
{
    int *v;
    
    if(p == NULL)
        return -1;

    v = (int *)p;   
        
    return fprintf(pf, "%d ", *v);
    
}

int main (int num_arguments, const char *arg[]) {
    SortedQueue *sq=NULL;
    Point *p[NPOINTS] = {NULL};
    int x[MAX_NUM] = {7,6, 2, 5, 0, 9, 12, 11, 6, 8, 3, 7, 15, 27, 32, 2};
    int i;


    sq = squeue_new();
    if (sq == NULL) return 1;

    for(i = 0; i < MAX_NUM; i++){
        squeue_push(sq, &x[i], int_cmp);
    }

    fprintf(stdout,"\nSorted queue (integers):\n");
    squeue_print(stdout, sq, int_print);

    
    squeue_free(sq);
    

    sq = squeue_new();
    if (sq == NULL) return 1;


    p[0] = point_new(0, 0, BARRIER);
    p[1] = point_new(2, 0, BARRIER);
    p[2] = point_new(3, 5, BARRIER);
    p[3] = point_new(9, 10, BARRIER);
    p[4] = point_new(6, 5, BARRIER);
    p[5] = point_new(9, 10, BARRIER);
    p[6] = point_new(3, 3, BARRIER);
    p[7] = point_new(4, 5, BARRIER);
    p[8] = point_new(0, 2, BARRIER);
    p[9] = point_new(2, 0, BARRIER);


    for(i = 0; i < NPOINTS; i++)
        squeue_push(sq, p[i], point_cmpEuDistance);

    

    fprintf(stdout,"\nSorted queue (points):\n");
    squeue_print(stdout, sq, point_print);

    for (i=0; i<NPOINTS; i++) {
        point_free(p[i]);
    }

    squeue_free(sq);

    sq = squeue_new();
    if (sq == NULL) return 1;

    squeue_push(sq, "hola", string_cmp);
    squeue_push(sq, "adios", string_cmp);
    squeue_push(sq, "buenas", string_cmp);
    squeue_push(sq, "hola", string_cmp);
    squeue_push(sq, "kilo", string_cmp);
    squeue_push(sq, "eva", string_cmp);

    fprintf(stdout,"\nSorted queue (strings):\n");
    squeue_print(stdout, sq, string_print);

    squeue_free(sq);

    

    return 0;
}





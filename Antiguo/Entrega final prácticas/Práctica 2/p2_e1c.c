#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "point.h"
#include "stack_fDoble.h"
#define MAX_RAND 10
#define NPOINTS 100


int int_cmp(const void *c1, const void *c2) {
    if (!c1 || !c2)
        return INT_MIN;
    return -(*(int *)c1 - *(int *)c2);
}

Stack *stack_order (Stack *sin, int (*f_cmp)(const void *, const void *)) {
    Stack *s;
    void *i, *j;

    s = stack_init();

    while (stack_isEmpty(sin) == FALSE) {

        i = stack_pop(sin);
        while (stack_isEmpty(s) == FALSE && f_cmp(i, stack_top(s)) < 0) {
            j = stack_pop(s);
            stack_push(sin, j);
        }
        stack_push(s, i);
    }

    return s;
}


int main(int num_arguments, const char *arg[]){
    Point *p[NPOINTS] = {NULL};
    Point *origen = NULL;
    Stack *s = NULL, *s2 = NULL;
    int i, num;
    double d;

    srand(time(NULL));


    if(num_arguments <2){
        printf("Error, debes llamar a la funcion con el numero de puntos a crear\n");
        return -1;
    }

    num = atoi(arg[1]);

    srand(time(NULL));
    origen = point_new (0, 0, BARRIER);

    s = stack_init();

    if(!s){
        return -1;
    }

    for(i = 0; i < num; i++){
        fprintf(stdout, "\nPoint p[%d]=", i);
        p[i] = point_new(rand() % MAX_RAND , rand() % MAX_RAND, BARRIER);

        if(p[i] == NULL){
            return -1;
        }
        if(stack_push(s, p[i]) == ERROR){
            return -1;
        }

        point_print (stdout, p[i]);
        point_euDistance (p[i], origen, &d);
        fprintf (stdout, "distance: %lf", d);
    }

    fprintf(stdout,"\nOriginal Stack:\n");
    stack_print(stdout, s, point_print);

    s2 = stack_order(s, int_cmp);

    fprintf(stdout,"Ordered Stack:\n");
    stack_print(stdout, s2, point_print);

    fprintf(stdout,"Original Stack:\n");
    stack_print(stdout, s, point_print);



    for(i = 0; i < num; i++){
        point_free(p[i]);
    }

    point_free(origen);
    stack_free(s);
    stack_free(s2);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "point.h"

#define TAM 4

int main(int argc, char** argv) {
    Map *mp=NULL;
    Point *p=NULL, *o=NULL, *x[11];
    int i;

    mp = map_new(3, 4);

    printf("Map:\n");
    
    x[0]=map_insertPoint (mp, point_new(0, 0, BARRIER));
    x[1]=map_insertPoint (mp, point_new(0, 1, BARRIER));
    x[2]=map_insertPoint (mp, point_new(0, 2, BARRIER));
    x[3]=map_insertPoint (mp, point_new(0, 3, BARRIER));

    p = point_new(1, 2, OUTPUT);
    x[4]=map_insertPoint (mp, point_new(1, 0, BARRIER));
    x[5]=map_insertPoint (mp, point_new(1, 1, INPUT));
    x[6]=map_insertPoint (mp, p);
    x[7]=map_insertPoint (mp, point_new(1, 3, BARRIER));

    x[8]=map_insertPoint (mp, point_new(2, 0, BARRIER));
    x[9]=map_insertPoint (mp, point_new(2, 1, BARRIER));
    x[10]=map_insertPoint (mp, point_new(2, 2, BARRIER));
    x[11]=map_insertPoint (mp, point_new(2, 3, BARRIER));




    map_print(stdout, mp);
    printf("\n");

    map_setOutput(mp, p);
    o = map_getOutput(mp);

    printf("Get output neighboors:\n");
    
    point_print(stdout, map_getNeighboor(mp, o, 0));
    point_print(stdout, map_getNeighboor(mp, o, 1));
    point_print(stdout, map_getNeighboor(mp, o, 2));
    point_print(stdout, map_getNeighboor(mp, o, 3));

    printf("\n");

    for(i=0; i<12; i++)
        point_free(x[i]);
    
    map_free(mp);

    return 0;
}
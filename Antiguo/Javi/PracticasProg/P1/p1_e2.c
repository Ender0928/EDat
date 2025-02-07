#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "point.h"

#define TAM 4

int main(int argc, char** argv) {
    Map *mp=NULL;
    Point *p=NULL, *o=NULL;

    mp = map_new(3, 4);

    fprintf(stdout, "Map:\n");
    
    map_insertPoint (mp, point_new(0, 0, BARRIER));
    map_insertPoint (mp, point_new(0, 1, BARRIER));
    map_insertPoint (mp, point_new(0, 2, BARRIER));
    map_insertPoint (mp, point_new(0, 3, BARRIER));

    p = point_new(1, 2, OUTPUT);
    map_insertPoint (mp, point_new(1, 0, BARRIER));
    map_insertPoint (mp, point_new(1, 1, INPUT));
    map_insertPoint (mp, p);
    map_insertPoint (mp, point_new(1, 3, BARRIER));

    map_insertPoint (mp, point_new(2, 0, BARRIER));
    map_insertPoint (mp, point_new(2, 1, BARRIER));
    map_insertPoint (mp, point_new(2, 2, BARRIER));
    map_insertPoint (mp, point_new(2, 3, BARRIER));



    map_print(stdout, mp);
    fprintf(stdout, "\n");

    map_setOutput(mp, p);
    o = map_getOutput(mp);

    fprintf(stdout, "Get output neighboors:\n");
    
    point_print(stdout, map_getNeighboor(mp, o, 0));
    point_print(stdout, map_getNeighboor(mp, o, 1));
    point_print(stdout, map_getNeighboor(mp, o, 2));
    point_print(stdout, map_getNeighboor(mp, o, 3));

    fprintf(stdout, "\n");


    
    map_free(mp);

    return 0;
}
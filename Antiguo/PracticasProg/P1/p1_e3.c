/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p1_e3.c
 * Author: e462394
 *
 * Created on 22 de febrero de 2022, 12:04
 */

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"

int main(int argc, char *arg[]) 
{
    FILE *f=NULL;
    Map *mp=NULL;
    Point *o=NULL;

    if(argc < 2)
    {
        fprintf(stdout, "Error, este programa necesita un argumento para funcionar\n");
        return -1;
    }

    f=fopen(arg[1], "r");
    if (f == NULL)
        return 1;
    
    mp = map_readFromFile (f);
    
    if(f ==NULL)
        return 1;
    
    map_print(stdout, mp);
    
    fprintf(stdout, "\n");

    o = map_getOutput(mp);

    printf("Get output neighboors:\n");
    
    point_print(stdout, map_getNeighboor(mp, o, 0));
    point_print(stdout, map_getNeighboor(mp, o, 1));
    point_print(stdout, map_getNeighboor(mp, o, 2));
    point_print(stdout, map_getNeighboor(mp, o, 3));

    fprintf(stdout, "\n");

    map_free(mp);
    fclose(f);
    
    return 0; 
}


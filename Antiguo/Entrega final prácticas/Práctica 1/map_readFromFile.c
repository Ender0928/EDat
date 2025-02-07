/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "types.h"

Map *map_readFromFile(FILE *pf)
{
    Map *mp;
    int fila, columna, i, j;
    char sym;
    if(pf == NULL)
        return NULL;
    
    fscanf(pf," %d %d", &fila, &columna);
    
    mp = Map *map_new(fila, columna);
    if(mp == NULL)
        return NULL;
    
    for(i=0;i<fila;i++)
    {
        for(j=0;j<columna;j++)
        {
            point_setCoordinateX(mp->array[j][i], j);
            point_setCoordinateY(mp->array[j][i], i);
            fscanf(pf, "%c", sym);
            point_setSymbol(mp->array[j][i], sym);
        }
    }
    
    fclose(pf);
    return mp;
}

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   map.c
 * Author: javie
 *
 * Created on 21 de febrero de 2022, 18:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "map.h"
#include "point.h"
 
#define MAX_NCOLS 64 // Maximum map cols
#define MAX_NROWS 64 // Maximum map rows
#define MAX_BUFFER 64 // Maximum file line size

struct _Map {
    unsigned int nrows, ncols;
    Point *array[MAX_NROWS][MAX_NCOLS]; // array with the Map points
    Point *input, *output; // points input/output
};

/**
 * @brief  Creates a new empty Map with nrows and ncols.
 *
 * Allocates memory for a new map and initializes it to be empty 
 * (no points).
 * 
 * @param nrows, ncols Dimension of the map 
 *
 * @return A pointer to the graph if it was correctly allocated, 
 * NULL otherwise.
 **/
Map * map_new (unsigned int nrows,  unsigned int ncols) {
    Map *mp=NULL;

    mp = (Map *) malloc(sizeof(Map));
    if (mp == NULL)
        return NULL;
    
    mp->nrows = nrows;
    mp->ncols = ncols;

    return mp;
}

void map_free (Map *mp) {
    free(mp);
    
}


/**
 * @brief Inserts a point in a map.
 *
 * Insert a point in the map at the coordinates indicated by the point. 
 * The upper left corner point of the map has (0,0) coordinates.
 *
 * @param mp Pointer to the map.
 * @param p Pointer to the point to be inserted.
 *
 * @return Returns a pointer to the inserted point, NULL otherwise.
 **/
Point *map_insertPoint (Map *mp, Point *p) {
    int cX, cY;
    if (!mp || !p)
        return NULL;
    
    cX = point_getCoordinateX(p);
    cY = point_getCoordinateY(p);
    
    mp->array[cY][cX] = p;

    return mp->array[cY][cX];

}

int map_getNcols (const Map *mp) {
    if(mp == NULL)
        return -1;
    
    return mp->ncols;          
}

int map_getNrows (const Map *mp) {
    if(mp == NULL)
        return -1;
    
    return mp->nrows;          
}

Point *map_getInput (const Map *mp) {
    if(mp == NULL)
        return NULL;
    
    return mp->input;          
}

Point *map_getOutput (const Map *mp) {
    if(mp == NULL)
        return NULL;
    
    return mp->output;          
}

Point *map_getPoint (const Map *mp, const Point *p) {
    int cX, cY;

    if(!mp || !p)
        return NULL;

    cX = point_getCoordinateX(p);
    cY = point_getCoordinateY(p);
    
    return mp->array[cY][cX];          
}

Point *map_getNeighboor(const Map *mp, const Point *p, Position pos)
{   
    int cX, cY;

    cX = point_getCoordinateX(p);
    cY = point_getCoordinateY(p);

    if(mp == NULL || p == NULL)
        return NULL;

    if(pos == 0)
    { 
        return mp->array[cY+1][cX];
    }
    
    else if(pos == 1)
    {
        return mp->array[cY][cX-1];
    }
    
    else if(pos == 2)
    {
        return mp->array[cY-1][cX];
    }
    
    else if(pos == 3)
    {
        return mp->array[cY][cX+1];
    }
    
    else
    {
        return map_getPoint(mp, p);
    }
     
}

Status map_setInput(Map *mp, Point *p) {
    if (!mp || !p)
        return ERROR;
    
    mp->input = p;

    return OK;
}

Status map_setOutput (Map *mp,Point *p) {
    if (!mp || !p)
        return ERROR;
    
    mp->output = p;
    
    return OK;
}



Map *map_readFromFile(FILE *pf)
{
    Map *mp;
    int i, j;
    char sym;
    if(pf == NULL)
        return NULL;
    
    fscanf(pf," %d %d", &mp->nrows, &mp->ncols);
    
    mp = map_new(mp->nrows, mp->ncols);
    if(mp == NULL)
        return NULL;
    


    for(i=0;i<mp->nrows;i++)
    {
        for(j=0;j<mp->ncols;j++)
        {
            fscanf(pf, "%c", &sym);
            map_insertPoint(mp, point_new(j, i, sym));
        }
    }
    
    fclose(pf);
    return mp;
}

Bool map_equal (const void *_mp1, const void *_mp2) 
{
    Map *m1, *m2;
    if(_mp1 == NULL || _mp2 == NULL)
        return FALSE;
    
    m1 = (Map*)_mp1;
    m2 = (Map*)_mp2;
            
    if(m1->ncols == m2->ncols && m1->nrows == m2->nrows && m1->input == m2->input
            && m1->output == m2->output && m1->array == m2->array)
        return TRUE;
    else
        return FALSE;
}


int map_print (FILE*pf, Map *mp) {
    int i, j;

    printf("%d %d\n", mp->nrows, mp->ncols);

    for (i=0; i<mp->nrows; i++) {
        for (j=0; j<mp->ncols; j++) {
            point_print(pf, mp->array[j][i]);
        }
    }

    return i*j;
}
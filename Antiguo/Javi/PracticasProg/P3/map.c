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
#include "sorted_queue.h"

 
#define MAX_NCOLS 64 // Maximum map cols
#define MAX_NROWS 64 // Maximum map rows
#define MAX_BUFFER 64 // Maximum file line size

struct _Map {
    int nrows, ncols;
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

    if (nrows<0 || ncols<0)
        return NULL;
    
    if (nrows > 64 || ncols > 64)
        return NULL;

    mp = (Map *) malloc(sizeof(Map));
    if (mp == NULL)
        return NULL;

    
    
    mp->nrows = nrows;
    mp->ncols = ncols;

    mp->input = NULL;
    mp->output = NULL;


    return mp;
}

void map_free (Map *mp) {
    int i, j;

    for (i=0; i<mp->nrows; i++) {
        for (j=0; j<mp->ncols; j++) {
            point_free(mp->array[j][i]);
        }
    }

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

    if(pos == RIGHT) {
        if (mp->array[cY+1][cX] == NULL)
            return NULL;

        return mp->array[cY+1][cX];
    }
    
    else if(pos == UP) {
        if (mp->array[cY][cX-1] == NULL)
            return NULL;

        return mp->array[cY][cX-1];
    }
    
    else if(pos == LEFT) {
        if (mp->array[cY-1][cX] == NULL)
            return NULL;

        return mp->array[cY-1][cX];
    }
    
    else if(pos == DOWN) {
        if (mp->array[cY][cX+1] == NULL)
            return NULL;

        return mp->array[cY][cX+1];
    }
    
    else {
        return mp->array[cY][cX];
    }

    return NULL;
     
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





Map *map_readFromFile(FILE *pf) {

    Map *mp=NULL;
    Point *p = NULL;
    int i, j;
    int rows, columns;
    char sym;
    char arr[100];

    if (pf == NULL) return NULL;

    fscanf(pf, "%d %d", &rows, &columns);

    mp = map_new(rows, columns);

    fgets(arr, 1, pf);

    for(i=0; i<mp->nrows ; i++) {
        fgets(arr, mp->ncols+2, pf);
        for(j=0;j<mp->ncols; j++) {
                
            fscanf(pf, "%c", &sym);
            p = map_insertPoint(mp, point_new(i, j, sym));

            if (sym == 'i')
                map_setInput(mp, p);
            
            else if (sym == 'o')
                map_setOutput(mp, p);
        }
            
    }
    

    return mp;
}



Bool map_equal (const void *_mp1, const void *_mp2) {
    Map *m1, *m2;
    int i, j;
    Bool b;

    if(_mp1 == NULL || _mp2 == NULL)
        return FALSE;
    
    m1 = (Map*)_mp1;
    m2 = (Map*)_mp2;

    if ((m1->ncols == m2->ncols) || (m2->nrows == m2->ncols)) {

        for (i=0; i<m1->nrows; i++) {
            for (j=0; j<m2->ncols; j++) {
                if (point_equal(m1->array[i][j], m2->array[i][j]) == TRUE)
                    b = TRUE;

                else {
                    b = FALSE;
                    break;
                }
            }
        }
    }

    return b;
}




int map_print (FILE*pf, Map *mp) {
    int i, j;

    fprintf(pf, "%d %d\n", mp->nrows, mp->ncols);

    for (i=0; i<mp->nrows; i++) {
        for (j=0; j<mp->ncols; j++) {
            point_print(pf, mp->array[j][i]);
        }
    }

    return i*j;
}



/*Point * map_dfs (FILE *pf, Map *mp) {
    Stack *s = NULL;
    Point *p = NULL;
    Point *pi = NULL;
    Point *po = NULL;
    Point *pn = NULL;
    
    int i;
    
    if(pf == NULL || !mp)
        return NULL;
    
    pi = map_getInput(mp);
    if(pi == NULL)
        return NULL;
    
    po = map_getOutput(mp);
    if(po == NULL)
        return NULL;
    
    s = stack_init();
    if(s == NULL)
        return NULL;
    
    if(stack_push(s, pi)==ERROR)
        return NULL;

    while (point_equal(p, po) == FALSE && stack_isEmpty(s) == FALSE)
    {
        p = stack_pop(s);
        if(p == NULL)
            return NULL;
        
        if(point_getVisited(p) == FALSE)
        {
            if(point_setVisited(p, TRUE)==ERROR)
                return NULL;

            point_print(pf, p);
            for(i=0;i<4;i++) {
                pn = map_getNeighboor(mp, p, i);

                if(pn && point_getVisited(pn)==ERROR && point_getSymbol(pn) != BARRIER)
                    if(stack_push(s, pn)==ERROR)
                        return NULL;
                
            }
        }
    }
    stack_free(s);
    
    
    if(point_equal(p, po) == TRUE)
        return p;
    
     
    return NULL;

} */

Point * map_bfs (FILE *pf, Map *mp) {
    Queue *q = NULL;
    Point *p = NULL;
    Point *pi = NULL;
    Point *po = NULL;
    Point *pn = NULL;
    
    int i;
    
    if(pf == NULL || !mp)
        return NULL;
    
    pi = map_getInput(mp);
    if(pi == NULL)
        return NULL;
    
    po = map_getOutput(mp);
    if(po == NULL)
        return NULL;
    
    q = queue_new();
    if(q == NULL)
        return NULL;
    
    if(queue_push(q, pi)==ERROR)
        return NULL;
    
    while (point_equal(p, po) == FALSE && queue_isEmpty(q) == FALSE)
    {
        p=(Point*)queue_pop(q);
        if(p == NULL)
            return NULL;
        
        if(point_getVisited(p) == FALSE)
        {
            if((point_setVisited(p, TRUE))==ERROR)
                    return NULL;

            point_print(pf, p);
            for(i=0;i<4;i++)
            {
                pn = map_getNeighboor(mp, p, i);
                if(pn && point_getVisited(pn)==FALSE && point_getSymbol(pn) != BARRIER)
                    if(queue_push(q, pn)==ERROR)
                        return NULL;
            }
        }
    }
    
    queue_free(q);

    if(point_equal(p, po) == TRUE)
        return p;
    
    return NULL;
}
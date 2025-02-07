/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   point.c
 * Author: javie
 *
 * Created on 11 de febrero de 2022, 15:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "point.h"

struct _Point {
    int x, y;
    char symbol;
    Bool visited; // for DFS
};

Point * point_new (int x, int y, char symbol) {
    Point *v=NULL;

    v = (Point *) malloc (sizeof(Point));
    if (v==NULL)
        return NULL;
    
    v->x = x;
    v->y = y;
    v->symbol = symbol;
    
    return v;
}

void point_free (Point *p)
{
    free(p);
}

int point_getCoordinateX (const Point *p) {
    if (p==NULL)
        return INT_MAX;
    
    return p->x;
}

int point_getCoordinateY (const Point *p) {
    if (p==NULL)
        return INT_MAX;
    
    return p->y;
}

char point_getSymbol (const Point *p) {
    if (p==NULL)
        return ERRORCHAR;
    
    return p->symbol;
}

Status point_setCoordinateX (Point *p, int x) {
    if (p==NULL || x<0)
        return ERROR;
    
    p->x = x;    
    return OK;
}

Status point_setCoordinateY (Point *p, int y) 
{
    if (p==NULL || y<0)
        return ERROR;
    
    p->y = y;
    
    return OK;
}

Status point_setSymbol (Point *p, char c) 
{
    if (p==NULL || !(c))
        return ERROR;
    
    p->symbol = c;
    
    return OK;
}

Bool point_equal (const void *p1, const void *p2) {
    Point *v1, *v2;

    if(p1 == NULL || p2 == NULL)
        return FALSE;
    
    v1 = (Point *) p1;
    v2 = (Point *) p2;
    
    
    if ( v1->x == INT_MAX || v1->y == INT_MAX || v2->x == INT_MAX || v2->y == INT_MAX)
        return FALSE;
    
    if (v1->symbol == ERRORCHAR || v2->symbol == ERRORCHAR)
        return FALSE;
    
    if(v1->x == v2->x && v1->y == v2->y && v1->symbol == v2->symbol)
        return TRUE;
    
    return FALSE;
}

Point *point_hardcpy (const Point *src) {
    Point *trg=NULL;

    if (src == NULL)
        return NULL;
    
    trg = point_new(src->x, src->y, src->symbol);

    return trg;
}

int point_print(FILE *pf, const void *p)
{
    Point *v;
    
    if(p == NULL)
        return -1;

    v = (Point*)p;   
        
    return fprintf(pf, "[(%d, %d): %c] ", v->y, v->x, v->symbol);
    
}


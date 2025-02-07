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
#include <math.h>

#include "point.h"

struct _Point {
    int x, y;
    char symbol;
    Bool visited; // for DFS
};

Point * point_new (int x, int y, char symbol) {
    Point *v=NULL;

    if (x<0 || y<0 || symbol == ERRORCHAR) /*no se si se hace asi para symbol*/
        return NULL;
    

    v = (Point *) malloc (sizeof(Point));
    if (v==NULL)
        return NULL;
    
    v->x = x;
    v->y = y;
    v->symbol = symbol;
    v->visited = FALSE;
    
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
    if (p==NULL || x<0 || x == INT_MAX) /*No se si esta bien hecho lo de INT_MAX*/
        return ERROR;
    
    p->x = x;    
    return OK;
}

Status point_setCoordinateY (Point *p, int y) 
{
    if (p==NULL || y<0 || y == INT_MAX) /*No se si esta bien hecho lo de INT_MAX*/
        return ERROR;
    
    p->y = y;
    
    return OK;
}

Status point_setSymbol (Point *p, char c)  
{
    if (p==NULL || !c || c == ERRORCHAR) /* no se si esta bn, probablemente es comprobar BARRIER...*/
        return ERROR;
    
    p->symbol = c;
    
    return OK;
}

Bool point_getVisited (const Point *p)
{
    if(p == NULL)
        return FALSE;
    return p->visited;
}

Status point_setVisited (Point *p, Bool bol) /*Mirar luego*/
{
    if(p == NULL || bol == FALSE)
        return ERROR;
    
    p->visited = bol;
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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

Status point_euDistance (const Point *p1, const Point *p2, double *distance)
{
    if(!p1 || !p2)
        return ERROR;
    
    *distance = sqrt(pow((p1->x)-(p2->x),2) + pow((p1->y)-(p2->y),2));
    //*Añadir en el makefile -lm para que añada la biblioteca de math.h*//
    return OK;
}

int point_cmpEuDistance (const void *p1, const void *p2) {
    Point *o=NULL;
    double d1, d2;

    o = point_new(0, 0, BARRIER);

    if(!p1 || !p2)
        return INT_MIN;
    
    if(point_euDistance((Point*)p1, o, &d1)==ERROR)
        return INT_MIN;
    if(point_euDistance((Point*)p2, o, &d2)==ERROR)
        return INT_MIN;
    
    point_free(o);

    if ((d1-d2) < 0)
        return -1;

    if ((d1-d2) > 1)
        return 1;

    return 0;


}
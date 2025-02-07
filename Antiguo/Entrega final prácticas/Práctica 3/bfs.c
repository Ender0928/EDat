/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "map.h"
#include "point.h"
#include "stack_fDoble.h"
#include "queue.h"
#include "types.h"

Point * map_bfs (FILE *pf, Map *mp) {
    Queue *q = NULL;
    Point *p = NULL;
    Point *pi = NULL;
    Point *po = NULL;
    Point *pn = NULL;
    
    int i;
    
    if(pf == NULL || !mp)
        return NULL;
    
    pi = map_getImput(mp);
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
    
    while (p != po && queue_isEmpty(q) == FALSE)
    {
        p=(Point*)queue_pop(q);
        if(p == NULL)
            return NULL;
        
        if(point_getVisited(p) == FALSE)
        {
            if((point_setVisited(p, TRUE))==ERROR)
                    return NULL;
            point_print(pf, p);
            for(i=1;i<5;i++)
            {
                pn = map_getNeighboor(mp, p, i);
                if(pn && point_setVisited(pn)==FALSE && point_getSymbol(pn) != BARRIER)
                    if(queue_push(q, pn)==ERROR)
                        return NULL;
            }
        }
    }
    
    queue_free(q);

    if(p != po)
        return NULL;
    
    return p;
}

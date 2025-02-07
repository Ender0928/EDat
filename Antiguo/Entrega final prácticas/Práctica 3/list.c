#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct _Nodo {
	void* info;
	struct _Nodo *next;
} Nodo;

struct _List {
	Nodo *first;
        Nodo *last;
};

Nodo* nodo_new() {
	Nodo *pn = NULL; 
               
	pn = (Nodo *) malloc(sizeof(Nodo));
	if (!pn)
            return NULL;
        
	pn->info = NULL; 
	pn->next = NULL;
	return pn;
}

List *list_new()
{
    List *p = NULL;
    
    p = (List*)malloc(sizeof(List));
    if(p == NULL)
        return NULL;
    
    p->first = NULL;
    p->last = NULL;
    return p;
}

Bool list_isEmpty(const List *pl){
    if(pl == NULL)
        return TRUE;
    
    if(pl->first == NULL)
        return TRUE;
    
    return FALSE;
}

Status list_pushFront(List *pl, const void *e){
    Nodo * pn = NULL;
    if (pl == NULL || e == NULL) {
        return ERROR;
    }
    pn = nodo_new();
    if (pn == NULL) {
        return ERROR;
    }
    pn->info = (void *) e;
    
    if (list_isEmpty(pl) == TRUE) {
        pl->first = pn;
        pl->last = pn;

         return OK;        
    }
    pn->next = pl->first;
    pl->first = pn;
    
    return OK;
}

Status list_pushBack(List *pl, const void *e){
    Nodo * pn = NULL, * qn = NULL;
    if (pl == NULL || e == NULL) {
        return ERROR;
    }
    pn = nodo_new();
    if (pn == NULL) {
        return ERROR;
    }
    pn->info = (void *) e;
    
    if (list_isEmpty(pl) == TRUE) {
        pl->first = pn;
        pl->last = pn;
        
        return OK;
    }
    
    qn = pl->first;
    qn->next = pn;
    pl->last = pn;
    
    return OK;
}

void *list_popFront(List *pl){
    Nodo * pn = NULL;
    void * pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE) {
        return NULL;
    }
    pn = pl->first;
    pe = pn->info; 
    pl->first = pn->next;
    if(list_isEmpty(pl))
        pl->last = NULL;
    
    free(pn);
    
    return pe;
}

void *list_popBack(List *pl){
    Nodo *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE) {
        return NULL;
    }
    if (pl->first->next == NULL) {
        pe = pl->first->info;
        free(pl->first);
        pl->first = NULL;
        pl->last = NULL;
        
        return pe;
     
    }
    pn = pl->first;
    while (pn->next->next != NULL) {
        pn = pn->next;
    }
    pe = pn->next->info;
    free(pn -> next);
    pn->next= NULL;
    pl->last = pn;
    
    return pe;
}


void *list_getFront(List *pl){
    void * pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE) {
        return NULL;
    }
    pe = pl->first->info; 
    
    return pe;
}

void *list_getBack(List *pl){
    Nodo *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE) {
        return NULL;
    }
    if (pl->first->next == NULL) {
        pe = pl->first->info;
        
        return pe;
     
    }
    pn = pl->first;
    while (pn->next->next != NULL) {
        pn = pn->next;
    }
    pe = pn->next->info;
    
    return pe;
}

void list_free(List *pl){
    if(pl == NULL)
        return;
    
    while(list_isEmpty(pl) == FALSE)
        list_popFront(pl);
    
    free(pl);
}

int list_size(const List *pl){
    Nodo *pn = NULL;
    int size = 0;
    
    if (pl == NULL) 
        return -1;
        
    pn = pl->first;
    while (pn != NULL) {
        pn = pn->next;
        size++;       
    }
    
    return size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f){
    
}
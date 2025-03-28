#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct _Stack {
void **items;       /*!<Static array of elements*/
int top;            /*!<index of the top element in the stack*/
int capacity;       /*!<xcapacity of the stack*/
};

Stack * stack_init (){
    Stack *newStack;

    if ((newStack= (Stack*) malloc(sizeof(Stack)))==NULL)
        return NULL;

    newStack->top = 0;
    newStack->capacity = INIT_CAPACITY;
    if ((newStack->items = (void**) malloc(INIT_CAPACITY*sizeof(void*)))==NULL){
        free(newStack);
        return NULL;
    }

    for (int i = 0; i < INIT_CAPACITY; i++)
        newStack->items[i] = NULL;

    return newStack;
} 

void stack_free(Stack *s){
    free(s->items);
    free(s);
}

Status stack_push(Stack *s, const void *ele){
    if(!s||!ele)
        return ERROR;
    
    if(s->top+1 < s->capacity){
        s->items[s->top] = (void*)ele;
    }

    else{
        if(!(s->items = realloc(s->items, FCT_CAPACITY*sizeof(void*) * (s->capacity))))
            return ERROR;
        s->capacity *= FCT_CAPACITY;
        s->items[s->top] = (void*)ele;
    }

    s->top++;
    return OK;  
}

void * stack_pop (Stack *s){
    void *out;
    if(!s)
        return NULL;
    
    if(stack_isEmpty(s) == FALSE){
        out = s->items[s->top-1];
        s->items[s->top-1] = NULL;
        s->top--;
    }
    else{
        return NULL;
    }

    return out; 
}

void * stack_top (const Stack *s){
    void *out;
    if(!s)
        return NULL;
    
    if(stack_isEmpty(s) == FALSE){
        out = s->items[s->top-1];
    }
    else{
        return NULL;
    }

    return out;
}

Bool stack_isEmpty(const Stack *s){
    if(!s){
        return FALSE;
    }
    
    if(s->items[0] == NULL && s->top==0){
        return TRUE;
    }
    
    return FALSE;
}

size_t stack_size(const Stack *s){
    if(!s){
        return -1;
    }
    
    return (long)s->top;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
    int car = 0;

    if(!fp || !s || !f){
        return -1;
    }

    fprintf(fp, "SIZE: %ld\n", stack_size(s));

    for(int i = s->top; i > 0; i--){
        car += f(fp,s->items[i-1]);
        fprintf(fp, "\n");
    }

    return car;    
}

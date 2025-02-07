#include <stdio.h>
#include <string.h>

#include "stack_fDoble.h"
#include "map.h"
#include "point.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity
#define MAX_STACK 1024


struct _Stack {
    void **item; /*!<Dynamic array of elements*/
    int top; /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};

/*Stack * stack_init () {
    Stack* s=NULL;
    int i;

    s=(Stack*)malloc(sizeof(Stack));

    if(s==NULL)
        return NULL;

    for(i=0; i<MAX_STACK; i++){
        s->item[i]=NULL;
    }

    s->top=-1;
    return s;
}*/


Stack * stack_init () {
    Stack* s=NULL;
    int i;

    s=(Stack*)malloc(sizeof(Stack));
    if(s==NULL)
        return NULL;

    
    s->item = (void **) malloc(INIT_CAPACITY * sizeof(void *));

    for (i=0; i<INIT_CAPACITY; i++)
        s->item[i] = NULL;

    s->capacity = INIT_CAPACITY;
    s->top=-1;
    return s;
}

void stack_free (Stack *s) {

    free (s->item);        
    free(s);
}


Status stack_push (Stack *s, void *ele)
{
    if(s == NULL || ele == NULL)
        return ERROR;

    if(s->top == s->capacity-1)
        stack_realloc(s);
    
    s->top++;
    s->item[s->top] = ele;
    
    return OK;
}

void *stack_pop(Stack *s)
{
    void *e = NULL;
    if(!s || stack_isEmpty(s) == TRUE)
        return NULL;
    
    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;

    return e;
}

void * stack_top(const Stack *s)
{
    if(!s || stack_isEmpty(s) == TRUE)
        return NULL;
    
    return s->item[s->top];
}

Bool stack_isEmpty (const Stack *s)
{
    if(!s)
        return TRUE;
    
    if(s->top == -1)
        return TRUE;
    
    return FALSE;
}

int stack_size(const Stack *s)
{
    if(s == NULL)
        return -1;
    
    return s->capacity;
}

void stack_realloc(Stack *s)
{
    int i, new_capacity;
    
    if(s == NULL)
        return;
    
    new_capacity = s->capacity * FCT_CAPACITY;

    s->item = (void **) realloc(s->item, new_capacity * sizeof(void*));

    for(i=s->capacity; i<new_capacity; i++) 
        s->item[i] = NULL;
    
    
    s->capacity = new_capacity;

    return;
}


int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f) {
    int i;

    if(!f||!s)
        return -1;

    fprintf(fp, "SIZE: %d\n", s->top+1);

    for (i=s->top; i != -1; i--){
        f(fp,s->item[i]);
        fprintf(fp, "\n");
    }

  
  
    return i;
}
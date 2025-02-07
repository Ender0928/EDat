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


Stack * stack_init () {
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
}

void stack_free (Stack *s) {
    free(s);
}


Status stack_push (Stack *s, void *ele)
{
    if(s == NULL || ele == NULL)
        return ERROR;
    if(s->top == s->capacity-1)
    {
        stack_realloc(s);
        return ERROR;
    }
    s->top++;
    s->item[s->top] = ele;
    
    return OK;
}

void *stack_pop(Stack *s)
{
    void *e = NULL;
    
    if(!s)
        return NULL;
    
    if(s->top == s->capacity-1)
    {
        stack_realloc(s);
        return ERROR;
    }
    
    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;
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
    s->item = (void*)realloc(s->item, new_capacity);
    
    for(i=s->capacity; i<new_capacity; i++)
        s->item[i] == NULL;
    
    s->capacity = new_capacity;
}

int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f) {
  int i,j=0;

  if(!f||!s)
    return -1;

  for(i=s->top;i==0;i--){
    f(stdout,s->item[i]);
    j++;
  }
  
  return j;
}

Stack *stack_orderPoints(Stack *sin) /* Quitar */
{
    Stack *s;   
    Point *i, *j;
    
    s =stack_init();
    while(stack_isEmpty(sin)==FALSE)
    {
        i = stack_pop(sin);
        while(stack_isEmpty(s)==FALSE && point_cmpEuDistance(i, stack_top(s))< 0)
        {
            j = stack_pop(s);
            stack_push(sin, j);
        }
        stack_push(s, i);
    }
    return s;
}
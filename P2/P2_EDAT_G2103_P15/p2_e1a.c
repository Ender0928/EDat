#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "file_utils.h"

/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/
Status mergeStacks1 (Stack *sin1, Stack *sin2, Stack *sout){
    void *e;
    int *a, *b;
    Status st = OK;

    if (sin1==NULL||sin2==NULL)
    {
        st = ERROR;
    }

    do 
    {
        a=stack_top(sin1);
        b=stack_top(sin2);
        if (*a>*b)
        {
           e =stack_pop(sin1);
        }else 
           e =stack_pop(sin2);
        stack_push(sout, e);
        
    }while (stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE && st==OK );

    if (stack_isEmpty(sin1)==TRUE && st == OK)
    {
        while (stack_isEmpty(sin2)==FALSE)
        {
            e=stack_pop(sin2);
            stack_push(sout, (const void*)e);
        }
    }

    else
    {
        while (stack_isEmpty(sin1)==FALSE && st == OK)
        {
            e=stack_pop(sin1);
            stack_push(sout, (const void*)e);
        }
    }
    
    return st;
}

int main(int argc, char** argv){
    
    FILE *f1, *f2;
    int tam;
    float a;
    float *b1, *b2;
    Stack *s1=NULL, *s2=NULL, *s3=NULL;
    Status st=OK;
    if (!argv[1]|| !argv[2])
        return -1;

    if (!(f1=fopen(argv[1], "r")))
    {
        return -1;
    }

    if(!(s1=stack_init()))
    {   
        fclose(f1);
        return -1;
    }

    fscanf(f1, "%d", &tam);

    for (int i = 0; i < tam && st ==OK; i++)
    {
        fscanf(f1, "%f", &a);
        b1=float_init(a);

        if(!stack_push(s1, b1)){
            st = ERROR;
        }

    }
    fclose(f1);
    
    if (st==OK) {
        fprintf(stdout,"Ranking 0:\n");
        stack_print(stdout, s1, float_print);
    }
    
    if (!(f2=fopen(argv[2], "r")))
    {
        st = ERROR;
    }

    if((!(s2=stack_init()) && st == OK))
    {
        st = ERROR;
    }

    if (st==OK) {
        tam=0;
        fscanf(f2, "%d", &tam);
    }


    for (int i = 0; i < tam && st == OK; i++)
    {
        fscanf(f2, "%f", &a);
        b2=float_init(a);
        
        if(!stack_push(s2, b2)){
            st = ERROR;
        }

    }

    fclose(f2);

    if (st==OK) {
        fprintf(stdout, "Ranking 1:\n");
        stack_print(stdout, s2,float_print);
    }
    
    if(!(s3=stack_init())&& st == OK){
        st = ERROR;
    }
    if(!mergeStacks1(s1, s2, s3) && st == OK){
        st = ERROR;
    }

    if (st ==OK)
        fprintf(stdout, "Joint ranking:\n");
    
    if(stack_print(stdout, s3,float_print)<0){
        st = ERROR;
    }
    tam=stack_size(s3);
    for(int i=0; i<tam;i++){
        float_free(stack_pop(s3));
    }


    stack_free(s1);
    stack_free(s2);
    stack_free(s3);
    if(st==ERROR)
        return -1;
    

    return 0;
}
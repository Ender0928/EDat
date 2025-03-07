#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h" 
#include "vertex.h"
#include "file_utils.h"

/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout,P_stack_ele_cmp elem_cmp){
    void *e;

    if (sin1==NULL||sin2==NULL)
    {
        return ERROR;
    }

    do 
    {
        if (elem_cmp(stack_top(sin1), stack_top(sin2))==1) 
        {
           e =stack_pop(sin1);
        }else 
           e =stack_pop(sin2);
        stack_push(sout, e);
        
    }while (stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE );

    if (stack_isEmpty(sin1)==TRUE)
    {
        while (stack_isEmpty(sin2)==FALSE)
        {
            e=stack_pop(sin2);
            stack_push(sout, (const void*)e);
        }
    }

    else
    {
        while (stack_isEmpty(sin1)==FALSE)
        {
            e=stack_pop(sin1);
            stack_push(sout, (const void*)e);
        }
    }
    
    return OK;
}


int main(int argc, char **argv){
    int tam, j=0;
    FILE *f1, *f2;
    Stack *s1, *s2, *s3;
    Vertex *v;
    char tag[120], id[120];
    Status st = OK;

    if(!argv[1]||!argv[2]){
        return -1;
    }


    if(!(f1=fopen(argv[1], "r")))
        return -1;
    
    if(!(s1=stack_init()))
    {   
        fclose(f1);
        return -1; //si el codigo ha fallado hasta este punto, no merece la pena seguir ejecutando
    }
       
    fscanf(f1,"%d", &tam);

    for (int i = 0; i < tam && st ==OK; i++)
    {
        fscanf(f1,"%s %s",id, tag); 
        strcat(id," ");
        strcat(id,tag);
        strcat(id," ");
        strcat(id,"state:0");
        if(!(v=vertex_initFromString(id)))
            st=ERROR;

        if(!(vertex_setIndex(v,j))) 
            st=ERROR;
        j++;
        /*En la salida no había index cuando se imprimían los vertices, pero hemos decido incluirlo, ya que estaba hecho del p2_e2. Podíamos haber inicializado el index a -1
        y en el print poner una condicion que si index == -1, se imprimieran los vertices sin tener en cuenta el espacio para el index (como se hacía en la semana 1), pero hemos decidido 
        optar por esta opción*/

        if (!stack_push(s1,v)){
            st= ERROR;
        }
    }
    fclose(f1);

    if(st==OK) {
        fprintf(stdout, "Ranking 0:\n");
        stack_print(stdout, s1, vertex_print);
    }

    if(!(f2=fopen(argv[2], "r"))){
        st=ERROR;
    }

    if(!(s2=stack_init()) && st ==OK)
    {
        st=ERROR;
    }

    if (st==OK) {
        tam=0;
        fscanf(f2, "%d", &tam);
    }

    for (int i = 0; i < tam && st == OK; i++)
    {
        fscanf(f2,"%s %s",id, tag); 
        strcat(id," ");
        strcat(id,tag);
        strcat(id," ");
        strcat(id,"state:0");
        if(!(v=vertex_initFromString(id)))
            st=ERROR;

        if(!(vertex_setIndex(v,j)))
            st=ERROR;
        j++;

        if (!stack_push(s2,v)){
            st= ERROR;
        }
    }

    fclose(f2);

    if (st==OK) {
        fprintf(stdout, "Ranking 1:\n");
        stack_print(stdout, s2, vertex_print);
    }

    if(!(s3=stack_init())&& st == OK)
    {
        st=ERROR;
    }
    
    if (!mergeStacks(s1,s2,s3, vertex_cmp)&& st==OK)
    {
        st=ERROR;
    }

    if(st == OK)
        fprintf(stdout, "Joint Ranking:\n");

    if(stack_print(stdout, s3,vertex_print)<0){
        st = ERROR;
    }

    if(st==ERROR){
        if(s1!=NULL){
            tam=stack_size(s1);
            for(int i=0;i<tam;i++){
                vertex_free(stack_pop(s1));
            }
            stack_free(s1); 
        }
        if(s2!=NULL){
            tam=stack_size(s2);
            for(int i=0;i<tam;i++){
                vertex_free(stack_pop(s2));
            }
            stack_free(s2); 
        }
        if(s3!=NULL){
            tam=stack_size(s3);
            for(int i=0;i<tam;i++){
                vertex_free(stack_pop(s3));
            }
            stack_free(s3); 
        }
        return -1;
    }

    else{
        tam=stack_size(s3);
        for(int i=0;i<tam;i++){
            vertex_free(stack_pop(s3));
        }
        stack_free(s3);
        stack_free(s2);
        stack_free(s1);  
    }


return 0;

}

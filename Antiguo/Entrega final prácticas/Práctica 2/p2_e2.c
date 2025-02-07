#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"
#include "stack_fDoble.h"

int main(int argc, char *arg[]) 
{
    FILE *f=NULL;
    Map *mp=NULL;
    Point *p=NULL, *o=NULL;


    /*if(argc < 2)
    {
        printf("Error, este programa necesita un argumento para funcionar\n");
        return -1;
    }*/

    f=fopen("laberinto_1.txt", "r");
    if (f == NULL)
        return 1;
    
    mp = map_readFromFile (f);
    map_print(stdout, mp);

    if(f ==NULL)
        return 1;
    
    
    
    fprintf(stdout, "DFS traverse\n");
    
    
    fprintf(stdout, "\n");

    map_free(mp);
    return 0; 
}


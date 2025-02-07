#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "point.h"
#include "sorted_queue.h"


int main(int argc, char *arg[]) 
{
    FILE *f=NULL;
    Map *mp=NULL;


    if(argc < 2)
    {
        printf("Error, este programa necesita un argumento para funcionar\n");
        return 1;
    }

    f=fopen(arg[1], "r");
    if (f == NULL)
        return 1;
    
    mp = map_readFromFile (f);
    map_print(stdout, mp);

    if(f ==NULL)
        return 1;
    
    fprintf(stdout, "\nBFS traverse\n");
    map_bfs(stdout, mp);
    
    
    fprintf(stdout, "\n");

    map_free(mp);
    fclose(f);

    return 0; 
}


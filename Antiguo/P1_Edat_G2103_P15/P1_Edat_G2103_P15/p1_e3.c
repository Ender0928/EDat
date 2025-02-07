#include "graph.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    FILE *f;
    Graph *g=NULL;
    char cad[120];
    
    if(argv[1]==NULL)
        return 1;
    else
        strcpy(cad, argv[1]);

    if(!(g=graph_init(g)))
        return 1;
    
    if(!(f=fopen(cad,"r")))
        return 1;
    
    graph_readFromFile(f,g);

    graph_print(stdout,g);
    
    fclose(f);

    graph_free(g);
    
    return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h" 
#include "graph.h"
#include "vertex.h"
#include "file_utils.h"

int main(int argc, char **argv){
    FILE *f;
    Graph *g=NULL;
    long from, to;
    
    if(!argv[1]||!argv[2]||!argv[3])
        return -1;
    
    else{
        if(!(f=fopen(argv[1],"r")))
            return -1;
    }

    from=atol(argv[2]);
    to=atol(argv[3]);

    if(!(g=graph_init(g))){
        fclose(f);
        return -1;
    }
       
    
    if(!graph_readFromFile(f,g)){
        fclose(f);
        graph_free(g);
        return -1;     
    }

    if(!graph_print(stdout,g)){
        fclose(f);
        graph_free(g);
        return -1; 
    }

    if(!graph_depthSearch(g,from, to)){
        return -1;
    }
    
    fclose(f);
    graph_free(g);
    
    return 0;
}
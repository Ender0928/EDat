#include "graph.h"
#include <stdio.h>

int main(){
    Graph *g=NULL;
    int a, i;
    long *b;

    if(!(g=graph_init(g)))
        return ERROR;

    fprintf(stdout,"Inserting Madrid... result...: %d\n", (int)graph_newVertex(g,"id:111 tag:Madrid state:0")); 

    fprintf(stdout,"Inserting Toledo... result...: %d\n",(int)graph_newVertex(g,"id:222 tag:Toledo state:0"));

    fprintf(stdout,"Inserting edge: 222 --> 111\n");

    if(!graph_newEdge(g, 222, 111))
        return ERROR;

    fprintf(stdout,"111 --> 222?");

    if(graph_connectionExists(g, 111, 222)==TRUE)
        fprintf(stdout, " Yes\n");
    else
        fprintf(stdout, " No\n");

    fprintf(stdout,"222 --> 111?");

    if(graph_connectionExists(g, 222, 111)==TRUE)
        fprintf(stdout, " Yes\n");
    else
        fprintf(stdout, " No\n");

    if((a=graph_getNumberOfConnectionsFromId(g, 111))==-1)
        return ERROR;

    fprintf(stdout,"Number of connections from 111:%d\n", a);

    if((a=graph_getNumberOfConnectionsFromTag(g,"Toledo"))==-1)
        return ERROR;

    fprintf(stdout,"Number of connections from Toledo:%d\n", a);

    if((b=graph_getConnectionsFromTag(g, "Toledo"))==NULL)
        return ERROR;

    for(i=0; i<graph_getNumberOfConnectionsFromTag(g, "Toledo");i++){
        fprintf(stdout, "Connections form Toledo: %ld\n",b[i]);
    }
    
    fprintf(stdout, "Graph:");
    fprintf(stdout, "\n");
    
    graph_print(stdout, g);

    free(b);

    graph_free(g);

    return 0;
}


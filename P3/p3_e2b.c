#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

int main(int argc, char **argv){
    FILE *f1;
    Graph *g=NULL;
    long from, to;
    Status st = OK;

    if(!argv[1]|| !argv[2]|| !argv[3]){
        return -1;
    }
    from= atol(argv[2]);
    to= atol(argv[3]);

    if(!(f1=fopen(argv[1], "r")))
       return -1;

    if(!(g=graph_init())){
        fclose(f1);
        return -1;
    }
    if(graph_readFromFile(f1, g)==ERROR){
        fclose(f1);
        graph_free(g);
        return -1;
    }

    fclose(f1);

    st=graph_Search(g, from, to);

    graph_free(g);

    if(!st)
        return -1;
    
    return 0;
}

/*Input graph:
[100, Madrid, 0, 0]: [200, Toledo, 0, 1] [300, Segovia, 0, 2]
[200, Toledo, 0, 1]:
[300, Segovia, 0, 2]: [400, Valladolid, 0, 3] [500, Burgos, 0, 4]
[400, Valladolid, 0, 3]: [600, Palencia, 0, 5]
[500, Burgos, 0, 4]: [600, Palencia, 0, 5] [700, Santander, 0, 6]
[600, Palencia, 0, 5]: [700, Santander, 0, 6]
[700, Santander, 0, 6]:
--------DFS------------
From vertex id: 100
To vertex id: 700
Output:
[100, Madrid, 1, 0]
[300, Segovia, 1, 2]
[500, Burgos, 1, 4]
[700, Santander, 1, 6]
--------BFS------------
From vertex id: 100
To vertex id: 700
Output:
[100, Madrid, 1, 0]
[200, Toledo, 1, 1]
[300, Segovia, 1, 2]
[400, Valladolid, 1, 3]
[500, Burgos, 1, 4]
[600, Palencia, 1, 5]
[700, Santander, 1, 6]
----------------------------------------------------------------------------
Input graph:
[100, Madrid, 0, 0]: [200, Toledo, 0, 1] [300, Segovia, 0, 2]
[200, Toledo, 0, 1]:
[300, Segovia, 0, 2]: [400, Valladolid, 0, 3] [500, Burgos, 0, 4]
[400, Valladolid, 0, 3]: [600, Palencia, 0, 5]
[500, Burgos, 0, 4]: [600, Palencia, 0, 5] [700, Santander, 0, 6]
[600, Palencia, 0, 5]: [700, Santander, 0, 6]
[700, Santander, 0, 6]:
--------DFS------------
From vertex id: 100
To vertex id: 400
Output:
[100, Madrid, 1, 0]
[300, Segovia, 1, 2]
[500, Burgos, 1, 4]
[700, Santander, 1, 6]
[600, Palencia, 1, 5]
[400, Valladolid, 1, 3]
--------BFS------------
From vertex id: 100
To vertex id: 400
Output:
[100, Madrid, 1, 0]
[200, Toledo, 1, 1]
[300, Segovia, 1, 2]
[400, Valladolid, 1, 3]*/


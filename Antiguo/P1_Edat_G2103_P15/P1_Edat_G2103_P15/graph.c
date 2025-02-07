#include "graph.h"
#include "vertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX_VTX 4096
#define LEN 64


struct _Graph {
Vertex *vertices[MAX_VTX];
Bool connections[MAX_VTX][MAX_VTX];
int num_vertices;
int num_edges;
};

Graph * graph_init(){
    Graph *g;
    int i, j;

  g=malloc(sizeof(Graph));

  if(g==NULL){
    fprintf(stderr,"Error al crear el grafo");
    return NULL;
  }

  for(i=0;i<MAX_VTX;i++){
    g->vertices[i]=NULL;
        for(j=0;j<MAX_VTX;j++)
          g->connections[i][j]=FALSE;
  }
  
   g->num_edges=0;
   g->num_vertices=0;
   
  return g;
}

void graph_free(Graph *g){
  int i;
  
  if(!g)
    fprintf(stderr,"Error al liberar memoria");
  
  for(i=0;i<MAX_VTX;i++)
    vertex_free(g->vertices[i]);
  
  free(g);
}

Status graph_newVertex(Graph *g, char *desc){
  Vertex *v;
 
  if((v=vertex_initFromString(desc))==NULL)
    return ERROR;
  
  if(graph_contains(g,vertex_getId(v))==TRUE)
    return OK;
  
  g->vertices[g->num_vertices]=v;
  g->num_vertices++;

  return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest){
  if(!graph_contains(g,orig)||!graph_contains(g,dest))
    return ERROR;
  
  g->connections[orig][dest]=TRUE; 
  g->num_edges++;
  return OK;
}

Bool graph_contains(const Graph *g, long id){
  if (g==NULL)
    return FALSE;
    
    
    
  for (int i = 0; i < g->num_vertices; i++){
    if (vertex_getId(g->vertices[i])==id)
      return TRUE;
  }
        
    return FALSE;
}

int graph_getNumberOfVertices(const Graph *g){
  if (g==NULL)
    return -1;
    

return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g){
  if (g==NULL)
    return -1;


return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest){
  if (g==NULL)
    return FALSE;


  if(g->connections[orig][dest]==TRUE)
    return TRUE;

  return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
  int i, num, tam;
  if(g==NULL)
    return -1;

  tam=graph_getNumberOfVertices(g);

  for(i=num=0;i<tam; i++){
    if(graph_connectionExists(g,id,vertex_getId(g->vertices[i]))==TRUE)
      num++;
  }

  return num;
}

long *graph_getConnectionsFromId(const Graph *g, long id){
  long * tabla=NULL;
  int i, cont=0;


  if (g==NULL)
    return NULL;

  tabla= (long*) malloc(sizeof(long)*graph_getNumberOfConnectionsFromId(g, id));

  if (tabla==NULL)
    return NULL;
  
  for(i=0;i<graph_getNumberOfVertices(g); i++){
    if(graph_connectionExists(g, id,vertex_getId(g->vertices[i]))==TRUE){
      tabla[cont]=vertex_getId(g->vertices[i]);
      cont++;
    }
  }

return tabla;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
  int i, tam, num;
  long orig;
  if(g==NULL)
    return -1;

  tam=graph_getNumberOfVertices(g);

  for(i=0;i<tam;i++){
    if(!strcmp(vertex_getTag(g->vertices[i]),tag)){
      orig=vertex_getId(g->vertices[i]);
      break;
    }
  }

  for(i=num=0;i<tam; i++){
    if(graph_connectionExists(g,orig,vertex_getId(g->vertices[i]))==TRUE){
      num++;
    }
  }
  return num;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){
  long *out;
  int i,j, tam;
  long orig;

  if(g==NULL||tag==NULL)
    return NULL;

  tam=graph_getNumberOfVertices(g);

  if((out=malloc(sizeof(long)*tam))==NULL)
    return NULL;

  for(i=0;i<tam;i++){
    if(!strcmp(vertex_getTag(g->vertices[i]),tag)){
      orig=vertex_getId(g->vertices[i]);
      break;
    }
  }

  for(i=j=0;i<tam; i++){
    if(graph_connectionExists(g,orig,vertex_getId(g->vertices[i]))==TRUE){
      out[j]=vertex_getId(g->vertices[i]);
      j++;
    }
      
  }

  return out;
}

int graph_print (FILE *pf, const Graph *g){
  int i, j, car, tam;
  
if(pf==NULL||g==NULL)
  return -1;

tam= graph_getNumberOfVertices(g);

for(i=car=0;i<tam;i++){
    car+=vertex_print(pf,g->vertices[i]);
    car+=fprintf(pf,":");

    for(j=0;j<tam;j++){
      if(graph_connectionExists(g, vertex_getId(g->vertices[i]), vertex_getId(g->vertices[j]))){
        car+=vertex_print(pf,g->vertices[j]);
        car+=fprintf(pf," ");
      }
      
    }
    car+=fprintf(pf,"\n");
  }

return car;
}

Status graph_readFromFile (FILE *fin, Graph *g){ 
  int i, tam;
  long id1=0, id2=0;
  char id[120], tag[120];

  if(!fin||!g)
    return ERROR;

  fscanf(fin,"%d", &tam);

for(i=0; i<tam; i++){
  fscanf(fin,"%s %s",id, tag); 
  strcat(id," ");
  strcat(id,tag);
  strcat(id," ");
  strcat(id,"state:0");
  graph_newVertex(g,id);
}

g->num_vertices=tam;

for(i=0;fscanf(fin,"%ld %ld", &id1, &id2)==2;i++){
  graph_newEdge(g, id1, id2);
}

return OK;
}



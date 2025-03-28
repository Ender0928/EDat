#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "vertex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VTX 4096
#define LEN 64

struct _Graph {
  Vertex *vertices[MAX_VTX];
  Bool connections[MAX_VTX][MAX_VTX];
  int num_vertices;
  int num_edges;
};

/* START [Private_functions] */
int _graph_findVertexByTag(const Graph *g /*cambio*/, char *tag);
Status _graph_insertEdgeFromIndices(Graph *g, const long origIx,
                                    const long destIx);
int _graph_getNumConnections(const Graph *g, int ix);
long *_graph_getConnections(const Graph *g, int ix);
void _graph_setVertexState(Graph *g, Label l);
/* END [Private_functions] */

Graph *graph_init() {
  Graph *g;
  int i, j;

  g = malloc(sizeof(Graph));

  if (g == NULL) {
    fprintf(stderr, "Error al crear el grafo");
    return NULL;
  }

  for (i = 0; i < MAX_VTX; i++) {
    g->vertices[i] = NULL;
    for (j = 0; j < MAX_VTX; j++)
      g->connections[i][j] = FALSE;
  }

  g->num_edges = 0;
  g->num_vertices = 0;

  return g;
}

void graph_free(Graph *g) {
  int i;

  if (!g)
    fprintf(stderr, "Error al liberar memoria");

  for (i = 0; i < MAX_VTX; i++)
    vertex_free(g->vertices[i]);

  free(g);
}

Status graph_newVertex(Graph *g, char *desc) {
  Vertex *v;

  if ((v = vertex_initFromString(desc)) == NULL)
    return ERROR;

  if (graph_contains(g, vertex_getId(v)) == TRUE)
    return OK;

  g->vertices[g->num_vertices] = v;
  g->num_vertices++;

  return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest) {
  if (!graph_contains(g, orig) || !graph_contains(g, dest))
    return ERROR;

  g->connections[orig][dest] = TRUE;
  g->num_edges++;
  return OK;
}

Bool graph_contains(const Graph *g, long id) {
  if (g == NULL)
    return FALSE;

  for (int i = 0; i < g->num_vertices; i++) {
    if (vertex_getId(g->vertices[i]) == id)
      return TRUE;
  }

  return FALSE;
}

int graph_getNumberOfVertices(const Graph *g) {
  if (g == NULL)
    return -1;

  return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g) {
  if (g == NULL)
    return -1;

  return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest) {
  if (g == NULL)
    return FALSE;

  if (g->connections[orig][dest] == TRUE)
    return TRUE;

  return FALSE;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id) {
  int i, num, tam;
  if (g == NULL)
    return -1;

  tam = graph_getNumberOfVertices(g);

  for (i = num = 0; i < tam; i++) {
    if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE)
      num++;
  }

  return num;
}

long *graph_getConnectionsFromId(const Graph *g, long id) {
  long *tabla = NULL;
  int i, cont = 0;

  if (g == NULL || id == -1)
    return NULL;

  tabla =
      (long *)malloc(sizeof(long) * graph_getNumberOfConnectionsFromId(g, id));

  if (tabla == NULL)
    return NULL;

  for (i = 0; i < graph_getNumberOfVertices(g); i++) {
    if (graph_connectionExists(g, id, vertex_getId(g->vertices[i])) == TRUE) {
      tabla[cont] = vertex_getId(g->vertices[i]);
      cont++;
    }
  }

  return tabla;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag) {
  int i, tam, num;
  long orig;
  if (g == NULL)
    return -1;

  tam = graph_getNumberOfVertices(g);

  for (i = 0; i < tam; i++) {
    if (!strcmp(vertex_getTag(g->vertices[i]), tag)) {
      orig = vertex_getId(g->vertices[i]);
      break;
    }
  }

  for (i = num = 0; i < tam; i++) {
    if (graph_connectionExists(g, orig, vertex_getId(g->vertices[i])) == TRUE) {
      num++;
    }
  }
  return num;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag) {
  long *out;
  int i, j, tam;
  long orig;

  if (g == NULL || tag == NULL)
    return NULL;

  tam = graph_getNumberOfVertices(g);

  if ((out = malloc(sizeof(long) * tam)) == NULL)
    return NULL;

  for (i = 0; i < tam; i++) {
    if (!strcmp(vertex_getTag(g->vertices[i]), tag)) {
      orig = vertex_getId(g->vertices[i]);
      break;
    }
  }

  for (i = j = 0; i < tam; i++) {
    if (graph_connectionExists(g, orig, vertex_getId(g->vertices[i])) == TRUE) {
      out[j] = vertex_getId(g->vertices[i]);
      j++;
    }
  }

  return out;
}

int graph_print(FILE *pf, const Graph *g) {
  int i, j, car, tam;

  if (pf == NULL || g == NULL)
    return -1;

  tam = graph_getNumberOfVertices(g);

  for (i = car = 0; i < tam; i++) {
    car += vertex_print(pf, g->vertices[i]);
    car += fprintf(pf, ":");

    for (j = 0; j < tam; j++) {
      if (graph_connectionExists(g, vertex_getId(g->vertices[i]),
                                 vertex_getId(g->vertices[j]))) {
        car += vertex_print(pf, g->vertices[j]);
        car += fprintf(pf, " ");
      }
    }
    car += fprintf(pf, "\n");
  }

  return car;
}

Status graph_readFromFile(FILE *fin, Graph *g) {
  int i, tam;
  long id1 = 0, id2 = 0;
  char id[120], tag[120];

  if (!fin || !g)
    return ERROR;

  if(fscanf(fin, "%d", &tam)!=1)
    return ERROR;

  for (i = 0; i < tam; i++) {
    fscanf(fin, "%s %s", id, tag);
    strcat(id, " ");
    strcat(id, tag);
    strcat(id, " ");
    strcat(id, "state:0");
    if (graph_newVertex(g, id)) {
      vertex_setIndex(g->vertices[i], i);
    }
  }

  g->num_vertices = tam;

  for (i = 0; fscanf(fin, "%ld %ld", &id1, &id2) == 2; i++) {
    graph_newEdge(g, id1, id2);
  }

  return OK;
}

Status graph_depthSearch(Graph *g, long from_id, long to_id) {
  Status st = OK;
  Stack *s;
  Vertex *vf, *vt, *vo, *v;
  long *ids;

  if (!g)
    return ERROR;

  if (from_id < 0)
    return ERROR;

  if (to_id < 0)
    return ERROR;

  _graph_setVertexState(g, WHITE);

  fprintf(stdout, "From Vertex id: %ld\n", from_id);
  fprintf(stdout, "To Vertex id: %ld\n", to_id);

  vf = graph_getvertexfromid(g, from_id);
  vt = graph_getvertexfromid(g, to_id);

  if (!vf || !vt)
    return ERROR;

  s = stack_init();
  if (!s)
    return ERROR;

  stack_push(s, vf);

  fprintf(stdout, "Output:\n");

  do {
    vo = stack_pop(s);
    if (vo == vt) {
      vertex_setState(vo, BLACK);
      vertex_print(stdout, vo);
      fprintf(stdout, "\n");
      break;
    }

    else {
      if (vertex_getState(vo) == WHITE) {
        vertex_setState(vo, BLACK);

        vertex_print(stdout, vo);
        fprintf(stdout, "\n");

        ids = graph_getConnectionsFromId(g, vertex_getId(vo));

        for (int i = 0;
             i < graph_getNumberOfConnectionsFromId(g, vertex_getId(vo)); i++) {
          v = graph_getvertexfromid(g, ids[i]);
          if (vertex_getState(v) == WHITE)
            stack_push(s, v);
        }

        free(ids);
      }
    }

  } while (stack_isEmpty(s) == FALSE && st == OK);

  stack_free(s);
  return OK;
}

int _graph_findVertexByTag(const Graph *g /*cambio*/, char *tag) {
  int out = -1;
  int i, tam;

  if (g == NULL || tag == NULL)
    return -1;

  tam = graph_getNumberOfVertices(g);

  for (i = 0; i < tam; i++) {
    if (!strcmp(vertex_getTag(g->vertices[i]), tag)) {
      out = i;
      break;
    }
  }

  return out;
}

Status _graph_insertEdgeFromIndices(Graph *g, const long origIx,
                                    const long destIx) {
  long v1, v2;

  if (g == NULL || origIx == -1 || destIx == -1)
    return ERROR;

  v1 = vertex_getId(g->vertices[origIx]);
  v2 = vertex_getId(g->vertices[origIx]);

  if (v1 == -1 || v2 == -1)
    return ERROR;

  if (!(graph_newEdge(g, v1, v2)))
    return ERROR;

  return OK;
}

int _graph_getNumConnections(const Graph *g, int ix) {
  long v;
  int tam, i, num;

  if (!g || ix == -1) {
    return -1;
  }

  if ((tam = graph_getNumberOfVertices(g)) == -1 ||
      (v = vertex_getId(g->vertices[ix])) == -1) {
    return -1;
  }

  for (i = num = 0; i < tam; i++) {
    if (graph_connectionExists(g, ix, vertex_getId(g->vertices[i])) == TRUE)
      num++;
  }

  return num;
}

long *_graph_getConnections(const Graph *g, int ix) {
  return graph_getConnectionsFromId(g, vertex_getId(g->vertices[ix]));
  /*****************************************************************/
}

void _graph_setVertexState(Graph *g, Label l) {
  int i, tam;

  if (!g || l < 0 || l > 2)
    return;

  tam = graph_getNumberOfVertices(g);

  for (i = 0; i < tam; i++) {
    vertex_setState(g->vertices[i], l);
  }

  return;
}

Vertex *graph_getvertexfromid(Graph *g, long id) {
  int i, tam;
  if (!g || id == -1) {
    return NULL;
  }

  if ((tam = graph_getNumberOfVertices(g)) == -1)
    return NULL;

  for (i = 0; i < tam; i++) {
    if (id == vertex_getId(g->vertices[i])) {
      return g->vertices[i];
    }
  }

  return NULL;
}

Status graph_Search(Graph *g, long from_id, long to_id) {
  if (!g)
    return -1;
  fprintf(stdout, "Input graph:\n");
  if (graph_print(stdout, g) < 1)
    return ERROR;
  fprintf(stdout, "--------DFS--------\n\n");
  if (graph_depthSearch(g, from_id, to_id) == ERROR) {
    fprintf(stdout, "ERROR\n");
    return ERROR;
  }
  fprintf(stdout, "\n--------BFS--------\n\n");
  if (graph_breathSearch(g, from_id, to_id) == ERROR) {
    fprintf(stdout, "ERROR\n");
    return ERROR;
  }
  return OK;
}

Status graph_breathSearch(Graph *g, long from_id, long to_id) {
  Queue *q;
  int i = 0;
  Vertex *vf, *vt, *vo;
  long *ids;
  Status st = OK;

  if (!g || from_id < 0 || to_id < 0)
    return ERROR;

  if (!(q = queue_new()))
    return ERROR;

  vf = graph_getvertexfromid(g, from_id);
  vt = graph_getvertexfromid(g, to_id);
  if (!vf || !vt) {
    queue_free(q);
    return ERROR;
  }

  _graph_setVertexState(g, WHITE);

  fprintf(stdout, "From Vertex id: %ld\n", from_id);

  fprintf(stdout, "To Vertex id: %ld\n", to_id);

  fprintf(stdout, "Output:\n");

  queue_push(q, vf);

  do {
    vo = queue_pop(q);
    if (vo == vt) {
      vertex_setState(vo, BLACK);
      vertex_print(stdout, vo);
      fprintf(stdout, "\n");
      break;
    } 
    else {
      if (vertex_getState(vo) == WHITE){ 
        vertex_setState(vo, BLACK);
      
      vertex_print(stdout, vo);
      fprintf(stdout, "\n");
      ids = graph_getConnectionsFromId(g, vertex_getId(vo));

      for (i = 0; i < graph_getNumberOfConnectionsFromId(g, vertex_getId(vo));i++){
        if (!queue_push(q, graph_getvertexfromid(g, ids[i])))
          st = ERROR;
      }

      free(ids);
      }
    }

  } while (queue_isEmpty(q) == FALSE && st == OK);

  queue_free(q);
  return st;
}
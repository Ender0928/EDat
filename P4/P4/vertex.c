#include "vertex.h"
#include <string.h>

#define TAG_LENGTH 64

struct _Vertex {
  long id;
  char tag[TAG_LENGTH + 1];
  Label state;
  int index;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField(Vertex *v, char *key, char *value);

Status vertex_setField(Vertex *v, char *key, char *value) {
  if (!key || !value)
    return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr) {
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr)
    return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v)
    return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p)
      continue;

    *p = '\0';
    key = token;
    value = p + 1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/
Vertex *vertex_init() {
  Vertex *v;

  v = malloc(sizeof(Vertex));

  if (v == NULL)
    return NULL;

  v->id = 0;
  v->state = WHITE;
  strcpy(v->tag, "");
  v->index = 0;

  return v;
}

void vertex_free(void *v) {
  v = (Vertex *)v;

  free(v);
}

long vertex_getId(const Vertex *v) {
  if (v == NULL) {
    return -1;
  } else
    return v->id;
}

const char *vertex_getTag(const Vertex *v) {
  if (v == NULL) {
    return NULL;
  }
  return v->tag;
}

Label vertex_getState(const Vertex *v) {
  if (v == NULL) {
    return ERROR_VERTEX;
  }
  return v->state;
}

int vertex_getIndex(const Vertex *v) {
  if (v == NULL) {
    return ERROR_VERTEX;
  }
  return v->index;
}

int vertex_cmp(const void *v1, const void *v2) {
  Vertex *n1, *n2;
  n1 = (Vertex *)v1;
  n2 = (Vertex *)v2;

  if (v1 == NULL || v2 == NULL)
    return 0;

  if (n1->id == n2->id) {
    return strcmp(n1->tag, n2->tag);
  }

  if (n1->id < n2->id)
    return -1;

  if (n1->id > n2->id)
    return 1;

  return 0;
}

int vertex_print(FILE *pf, const void *v) {
  Vertex *n;
  n = (Vertex *)v;

  if (!v)
    return -1;

  if (n->state == WHITE) {
    return fprintf(pf, "[%ld, %s, 0, %d]", n->id, n->tag, n->index);
  }

  else if (n->state == BLACK) {
    return fprintf(pf, "[%ld, %s, 1, %d]", n->id, n->tag, n->index);
  }

  else if (n->state == ERROR_VERTEX)
    return 0;

  return 0;
}

Status vertex_setId(Vertex *v, const long id) {
  if (!v)
    return ERROR;

  v->id = id;

  return OK;
}

Status vertex_setTag(Vertex *v, const char *tag) {
  if (!v)
    return ERROR;

  strcpy(v->tag, tag);

  return OK;
}

Status vertex_setState(Vertex *v, const Label state) {
  if (!v || state < 0 || state > 2)
    return ERROR;

  v->state = state;

  return OK;
}

Status vertex_setIndex(Vertex *v, int ix) {
  if (!v)
    return ERROR;

  v->index = ix;

  return OK;
}

void *vertex_copy(const void *src) {
  Vertex *ver = NULL;
  Vertex *trg = NULL;

  ver = (Vertex *)src;

  if ((trg = vertex_init(trg)) == NULL)
    return NULL;

  vertex_setId(trg, ver->id);
  vertex_setTag(trg, ver->tag);
  vertex_setState(trg, ver->state);

  return (void *)trg;
}

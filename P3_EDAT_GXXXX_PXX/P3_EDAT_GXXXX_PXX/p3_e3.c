#include "file_utils.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *f1;
  long order;
  Status st = OK;
  int i, tam;
  List *pl = NULL, *new = NULL;
  float a;
  float *b1;

  if (!argv[1] || !argv[2])
  {
    return -1;
  }
  order = atol(argv[2]);

  if (!(f1 = fopen(argv[1], "r")))
    return -1;

  if (!(pl = list_new()))
  {
    fclose(f1);
    return -1;
  }

  fscanf(f1, "%d", &tam);

  for (i = 1; i <= tam && st == OK; i++)
  {
    fscanf(f1, "%f", &a);
    b1 = float_init(a);

    if (i % 2 == 0)
    {
      if (!list_pushFront(pl, b1))
        st = ERROR;
    }
    else
    {
      if (!list_pushBack(pl, b1))
        st = ERROR;
    }
  }
  fclose(f1);

  if (st == ERROR || list_print(stdout, pl, float_print) < 0)
    st = ERROR;

  if (st != ERROR)
  {
    if (!(new = list_new()))
      st = ERROR;
  }

  tam = (int)list_size(pl);
  fprintf(stdout, "Finished inserting. Now we extract from the beginning and insert in order:\n");

  for (i = 0; i < (tam / 2) && st == OK; i++)
  {
    if (!(b1 = list_popFront(pl)))
      st = ERROR;
    if (!list_pushInOrder(new, b1, float_cmp, order))
      st = ERROR;

    fprintf(stdout, "%f ", *b1);
  }
  fprintf(stdout, "\n");

  fprintf(stdout, "Now we extract from the end and insert in order:\n");
  while (list_isEmpty(pl) == FALSE && st == OK)
  {
    /*En el caso de listas de tamaño par hará el bucle tam/2 veces como el primero pero en listas impares tam/2+1*/
    if (!(b1 = list_popBack(pl)))
      st = ERROR;

    if (!list_pushInOrder(new, b1, float_cmp, order))
      st = ERROR;
    fprintf(stderr, "%f ", *b1);
  }
  fprintf(stdout, "\n");
  free(pl);

  if (st == ERROR || list_print(stdout, new, float_print) < 0)
    st = ERROR;

  list_free(new);

  if (!st)
    return -1;

  return 0;
}

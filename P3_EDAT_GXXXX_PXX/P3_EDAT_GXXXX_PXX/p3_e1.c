#include "delivery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *f1;
  Delivery *d;
  Status st = OK;

  if (!argv[1]) {
    return -1;
  }

  if (!(f1 = fopen(argv[1], "r")))
    return -1;

  if (!(d = build_delivery(f1)))
    st = ERROR;

  fclose(f1);

    if(!delivery_run_plan(stdout, d, vertex_print, vertex_free))
      st = ERROR;
  
  delivery_free(d);

  if (!st)
    return -1;

  return 0;
}

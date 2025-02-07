#include <stdio.h>
#include <stdlib.h>
#include "point.h"

#define TAM 4

int main(int argc, char** argv) {
    Point *p[TAM];

    p[0] = point_new(0, 0, BARRIER);
    p[1] = point_new(1, 0, BARRIER);

    point_print(stdout, p[0]);
    point_print(stdout, p[1]);
    fprintf(stdout, "\n");

    printf("¿Equal points p[0] and p[1]? ");
    if (point_equal(p[0], p[1]) == FALSE)
        fprintf(stdout, "No\n");
    else
        fprintf(stdout, "Yes\n");


    p[2] = point_hardcpy(p[0]);
    if (p[2] == NULL)
        return 1;
    
    fprintf(stdout, "Creating p[2]: ");
    point_print(stdout, p[2]);
    fprintf(stdout, "\n");

    fprintf(stdout, "¿Equal points p[0] and p[2]? ");
    if (point_equal(p[0], p[2]) == FALSE)
        fprintf(stdout, "No\n");
    else
        fprintf(stdout, "Yes\n");
    

    point_setSymbol(p[2], SPACE);
    fprintf(stdout, "Modifying p[2]: ");
    point_print(stdout, p[2]);
    fprintf(stdout, "\n");

    fprintf(stdout, "¿Equal points p[0] and p[2]? ");
    if (point_equal(p[0], p[2]) == FALSE)
        fprintf(stdout, "No\n");
    else
        fprintf(stdout, "Yes\n");


    p[3] = p[0];
    fprintf(stdout, "Assign p[3] = p[0]\n");

    point_setSymbol(p[3], OUTPUT);
    fprintf(stdout, "Modifying p[3]: ");
    point_print(stdout, p[3]);
    fprintf(stdout, "\n");


    point_print(stdout, p[0]);
    point_print(stdout, p[1]);
    point_print(stdout, p[2]);
    point_print(stdout, p[3]);

    fprintf(stdout, "\n");

    point_free(p[0]);
    point_free(p[1]);
    point_free(p[2]);

    return 0;
}
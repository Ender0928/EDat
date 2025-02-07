#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "point.h"

#define NPOINTS 5
#define MAX_RAND 10

int main() {
    Point *p[NPOINTS] = {NULL};
    Point *origen;
    int i, j, pcmp;
    double d;

    // set the random seed
    srand(time(NULL));
    // coordinate origin point
    origen = point_new (0, 0, BARRIER);
    for (i=0; i < NPOINTS; i++) {
        // point with random coordinates
        p[i] = point_new(rand() % MAX_RAND , rand() % MAX_RAND, BARRIER);
        if (p[i] == NULL)
            return 1;

        fprintf(stdout, "Point: ");    
        point_print (stdout, p[i]);

        point_euDistance (p[i], origen, &d);
        fprintf (stdout, "Euclidean distance: %lf\n", d);
    }

    for (i=0; i<NPOINTS; i++) {
        for (j=i; j<NPOINTS; j++) {
            pcmp = point_cmpEuDistance(p[i], p[j]);
            fprintf(stdout, "p[%d] < p[%d]", i, j);

            if (pcmp == 0)
                fprintf(stdout, " False\n");

            else if (pcmp > 0)
                fprintf(stdout, " False\n");
            
            else if (pcmp < 0)
                fprintf(stdout, " True\n");
            
            else
                return 1;
        }
    }

    point_free(origen);

    for (i=0; i<NPOINTS; i++)
        point_free(p[i]);

    // .....the code continue....
}
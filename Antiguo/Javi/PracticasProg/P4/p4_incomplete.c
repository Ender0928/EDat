#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"


BSTree * tree_read_points_from_file(FILE * pf);


int main (int argc, char *argv[]){
    FILE * pf=NULL;
    BSTree * t;
    void *min, *max, *elem, *elem2;

    pf = fopen ("tree_example.txt", "r");
    if (pf == NULL) return 1;
    t = tree_read_points_from_file(pf);
    
    min = tree_find_min(t);
    if (min == NULL) return 1;

    max =  tree_find_max(t);
    if (max == NULL) return 1;

    fprintf(stdout, "Punto más pequeño: ");
    point_print(stdout, min);
    fprintf(stdout, "\n");

    fprintf(stdout, "Punto más grande: ");
    point_print(stdout, max);
    fprintf(stdout, "\n");

    
    fprintf(stdout, "\n");

    if (tree_contains(t, min) == TRUE)
        fprintf(stdout, "Sí, el elemento esta en el arbol\n");
    else
        fprintf(stdout, "No, el elemento no esta en el arbol\n");


    

    elem2 = (Point *) point_new(4, 2, '+');
    tree_remove(t, elem2);

    fprintf(stdout, "Nuevo punto: ");
    point_print(stdout, elem2);

    if (tree_contains(t, elem2) == TRUE)
        fprintf(stdout, "Sí, el elemento esta en el arbol\n");
    else
        fprintf(stdout, "No, el elemento no esta en el arbol\n");


    elem = (Point *) point_new(3, 2, '+');
    tree_remove(t, elem);

    fprintf(stdout, "\n");




    point_free(elem);
    point_free(elem2);

    fclose(pf);
    tree_destroy(t);
    return 0;
}


BSTree * tree_read_points_from_file(FILE * pf){
    BSTree * t;
    int nnodes=0, i;
    Status st = OK;
    int x, y;
    char symbol;
    Point * p;

    if (!pf){
        return NULL;
    }

    /* Read number of nodes */
    if (fscanf(pf, "%d\n", &nnodes) != 1){
        return NULL;
    }

    /* Create tree */
    t = tree_init(point_print, point_cmpEuDistance);
    if(!t){
        return NULL;
    }

    /* Read nodes */
    for (i=0; i<nnodes && st==OK ;i++){
        if(fscanf(pf, "%d %d %c", &x, &y, &symbol)!=3){
            return NULL;
        }
        p=point_new(x, y, symbol);
        if(!p){
            tree_destroy(t);
            return NULL;
        }

        st=tree_insert(t, p); 
        if(st==ERROR){
            tree_destroy(t);
            point_free(p);
            return NULL;      
        }
        

    }


    return t;






}
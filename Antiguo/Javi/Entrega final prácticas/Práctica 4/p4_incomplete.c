#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"


BSTree * tree_read_points_from_file(FILE * pf);


int main (int argc, char *argv[]){
    BSTree *tree;
    Point *min, *max;
    FILE *pf;

    pf = fopen("tree_example.txt", "r");
    if (pf == NULL) return 1;

    tree = tree_read_points_from_file(pf);
    if (tree == NULL) {
        fprintf(stdout, "No se ha podido crear el árbol\n");
        return 1;
    }

    tree_inOrder(stdout, tree);/*

    min = (Point *) tree_find_min(tree);
    if (min == NULL) return 1;

    max = (Point *) tree_find_max(tree);
    if (max == NULL) return 1;

    fprintf(stdout, "Punto más pequeño: ");
    point_print(stdout, min);
    fprintf(stdout, "\n");

    fprintf(stdout, "Punto más grande: ");
    point_print(stdout, max);
    fprintf(stdout, "\n");*/

    tree_destroy(tree);
    fclose(pf);

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
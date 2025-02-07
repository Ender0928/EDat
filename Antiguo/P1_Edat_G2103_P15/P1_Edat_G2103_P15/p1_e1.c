#include <stdio.h>

#include "vertex.h"
#include "types.h"

int main(int argc, char** argv){
Vertex *v1, *v2, *v3;

if(!(v1=vertex_initFromString("id:10 tag:one state:0")))
    return 1;

if(!(v2=vertex_initFromString("id:20 tag:two state:1"))){
    vertex_free(v1);
    return 1;
}
    

if(vertex_print(stdout, v1)==-1)
    return 1;
if(vertex_print(stdout, v2)==-1)
    return 1;

fprintf(stdout,"\n");

fprintf(stdout,"Equal? ");

if(!vertex_cmp(v1, v2))
    fprintf(stdout,"Yes\n");
else
    fprintf(stdout,"No\n");

fprintf(stdout,"Vertex 2 tag: %s\n", vertex_getTag(v2));

if(!(v3=(Vertex*) vertex_copy(v1))){
    vertex_free(v1);
    vertex_free(v2);
    return 1;
}
    

fprintf(stdout,"Vertex 3 id: %ld\n", vertex_getId(v3));

vertex_print (stdout, v1);
vertex_print (stdout, v3);
fprintf(stdout,"\n");

fprintf(stdout,"Equal? ");

if(!vertex_cmp(v1, v3))
    fprintf(stdout,"Yes\n");
else
    fprintf(stdout,"No\n");

vertex_free(v1);
vertex_free(v2);
vertex_free(v3);
    
return 0;

}


CC=gcc
CFLAGS= -c -Wall -pedantic -g

# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' ( dependencias)
########################################################################


p4_incomplete: p4_incomplete.o bstree_incomplete.o point.o
	$(CC) -o $@ $^ -lm -pthread

point.o: point.c point.h types.h
	gcc -c $< -lm -pthread

p4_incomplete.o: p4_incomplete.c bstree.h point.h
	$(CC) $(CFLAGS) $<


bstree_incomplete.o: bstree_incomplete.c bstree.h
	$(CC) $(CFLAGS) $<





.PHONY: clean
clean:
	rm -f *.o

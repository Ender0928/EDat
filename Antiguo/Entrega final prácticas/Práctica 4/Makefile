CC=gcc
CFLAGS= -c -Wall -pedantic -g


p4_incomplete: p4_incomplete.o bstree_incomplete.o point.o
	$(CC) -o p4_incomplete p4_incomplete.o bstree_incomplete.o point.o -lm -pthread

point.o: point.c point.h types.h
	gcc -c point.c -lm -pthread

p4_incomplete.o: p4_incomplete.c bstree.h point.h
	$(CC) $(CFLAGS) p4_incomplete.c


bstree_incomplete.o: bstree_incomplete.c bstree.h
	$(CC) $(CFLAGS) bstree_incomplete.c










clean:
	rm -f *.o

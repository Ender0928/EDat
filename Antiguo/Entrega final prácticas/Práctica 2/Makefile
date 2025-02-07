CC=gcc
CFLAGS= -c -Wall -pedantic -g
LFLAGS= -lm -L. -lstack_fDoble
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' ( dependencias)
########################################################################
p2_e1b: p2_e1b.o  point.o libstack_fDoble.a 
	$(CC) -o p2_e1b p2_e1b.o point.o $(LFLAGS)

p2_e1b.o: p2_e1b.c point.h types.h stack_fDoble.h
	$(CC) $(CFLAGS) p2_e1b.c



p2_e1a: p2_e1a.o point.o
	gcc -o p2_e1a p2_e1a.o point.o -lm -pthread

p2_e1c: p2_e1c.o point.o stack_fDoble.o
	gcc -o p2_e1c p2_e1c.o point.o stack_fDoble.o -lm -pthread

p2_e2: p2_e2.o point.o map.o libstack_fDoble.a 
	gcc -o p2_e2 p2_e2.o point.o map.o $(LFLAGS)

p2_e2.o: p2_e2.c point.h map.h stack_fDoble.h
	$(CC) $(CFLAGS) p2_e2.c


p2_e1a.o: p2_e1a.c point.h
	gcc -c p2_e1a.c



p2_e1c.o: p2_e1c.c point.h stack_fDoble.h
	gcc -c p2_e1c.c


point.o: point.c point.h 
	gcc -c point.c -lm -pthread

map.o: map.c map.h stack_fDoble.h
	gcc -c map.c


stack_fDoble.o: stack_fDoble.c stack_fDoble.h
	gcc -c stack_fDoble.c;





clean:
	rm -f *.o







runv1a:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p2_e1a

runv1b:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p2_e1b

runv1c:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p2_e1c

runv2:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p2_e2

CC=gcc
CFLAGS= -c -Wall -pedantic -g
LFLAGS= -lm -L. -lstack_fDoble
LFLAGS2 = -lm -L. -lqueue


all: p2_e1a p2_e1b p2_e1c p2_e2

p2_e1a: p2_e1a.o point.o
	$(CC) -o $@ $^ -lm -pthread

p2_e1b: p2_e1b.o  point.o libstack_fDoble.a 
	$(CC) -o $@ p2_e1b.o point.o $(LFLAGS)

p2_e1c: p2_e1c.o point.o libstack_fDoble.a 
	$(CC) -o $@ p2_e1c.o point.o $(LFLAGS)


p2_e2: p2_e2.o point.o map.o libstack_fDoble.a 
	$(CC) -o $@ p2_e2.o point.o map.o $(LFLAGS)




# Para el ejercicio 3, se han de ejecutar los ejercicios que usen la pila con una "S" delante

Sp2_e1b: p2_e1b.o point.o stack_fDoble.o
	$(CC) -o $@ $^ -lm

Sp2_e1c: p2_e1c.o point.o stack_fDoble.o
	$(CC) -o $@ $^  -lm

Sp2_e2: p2_e2.o point.o map.o stack_fDoble.o
	$(CC) -o $@ $^  -lm

	



p2_e1a.o: p2_e1a.c point.h
	$(CC) $(CFLAGS) $<

p2_e1b.o: p2_e1b.c point.h types.h stack_fDoble.h
	$(CC) $(CFLAGS) $<

p2_e1c.o: p2_e1c.c point.h stack_fDoble.h
	$(CC) $(CFLAGS) $<

p2_e2.o: p2_e2.c point.h map.h stack_fDoble.h
	$(CC) $(CFLAGS) $<




point.o: point.c point.h 
	$(CC) $(CFLAGS) $< -lm -pthread

map.o: map.c map.h stack_fDoble.h
	$(CC) $(CFLAGS) $<


stack_fDoble.o: stack_fDoble.c stack_fDoble.h
	$(CC) $(CFLAGS) $<;



vp2_e1a:
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a

vp2_e1b:
	@echo ">>>>>>Running p2_e1b 4 points with valgrind"
	valgrind --leak-check=full ./p2_e1b 4

vp2_e1c:
	@echo ">>>>>>Running p2_e1c 4 points with valgrind"
	valgrind --leak-check=full ./p2_e1c 4

vp2_e2:
	@echo ">>>>>>Running p2_e2 laberinto_1.txt with valgrind"
	valgrind --leak-check=full ./p2_e2 laberinto_1.txt



.PHONY: clean

clean:
	rm -f *.o


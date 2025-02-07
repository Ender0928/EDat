CC = gcc 
CFLAGS = -c -Wall -pedantic -g



all: p1_e1 p1_e2 p1_e3


p1_e1: p1_e1.o point.o
	$(CC) -o $@ $^

p1_e2: p1_e2.o map.o point.o
	$(CC) -o $@ $^

p1_e3: p1_e3.o map.o point.o
	$(CC) -o $@ $^


p1_e1.o: p1_e1.c point.h
	$(CC) $(CFLAGS) $<

p1_e2.o: p1_e2.c map.h 
	$(CC) $(CFLAGS) $<

p1_e3.o: p1_e3.c map.h point.h
	$(CC) $(CFLAGS) $<


point.o: point.c point.h
	$(CC) $(CFLAGS) $<

map.o: map.c map.h point.h
	$(CC) $(CFLAGS) $<



vp1_e1:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p1_e1

vp1_e2:
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full ./p1_e2

vp1_e3:
	@echo ">>>>>>Running p1_e3 laberinto_1.txt with valgrind"
	valgrind --leak-check=full ./p1_e3 laberinto_1.txt



.PHONY: clean

clean:
	rm -f *.o

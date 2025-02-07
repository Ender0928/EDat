p1_e1: p1_e1.o point.o
	gcc -o p1_e1 p1_e1.o point.o

p1_e2: p1_e2.o map.o point.o
	gcc -o p1_e2 p1_e2.o map.o point.o

p1_e3: p1_e3.o map.o point.o
	gcc -o p1_e3 p1_e3.o map.o point.o

p1_e1.o: p1_e1.c point.h
	gcc -c p1_e1.c

p1_e2.o: p1_e2.c map.h point.h
	gcc -c p1_e2.c

p1_e3.o: p1_e3.c map.h point.h
	gcc -c p1_e3.c

point.o: point.c point.h
	gcc -c point.c

map.o: map.c map.h point.h
	gcc -c map.c





runv1:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p1_e1

runv2:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p1_e2

runv3:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./p1_e3




clean:
	rm -f *.o

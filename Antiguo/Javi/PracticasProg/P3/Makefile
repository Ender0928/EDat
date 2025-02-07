CC=gcc
CFLAGS= -c -Wall -pedantic -g
LFLAGS= -lm -L. -lstack_fDoble
LFLAGS2 = -lm -L. -lqueue




all: p3_e1b p3_e2

p3_e1b: p3_e1b.o point.o sorted_queue.o libqueue.a
	$(CC) -o p3_e1b p3_e1b.o point.o sorted_queue.o $(LFLAGS2)

p3_e2: p3_e2.o point.o map.o libqueue.a 
	$(CC) -o $@ p3_e2.o point.o map.o $(LFLAGS2) 




sorted_queue.o: sorted_queue.c sorted_queue.h 
	$(CC) $(CFLAGS) $<


Qp3_e1b: p3_e1b.o point.o sorted_queue.o queue.o list.o
	$(CC) -o $@ $^ -lm



p3_e1b.o: p3_e1b.c point.h sorted_queue.h 
	$(CC) $(CFLAGS) $<

p3_e2.o: p3_e2.c point.h map.h sorted_queue.h
	$(CC) $(CFLAGS) $<




queue.o: queue.c queue.h list.h
	$(CC) $(CFLAGS) $<

list.o: list.c list.h
	$(CC) $(CFLAGS) $<
	


point.o: point.c point.h 
	$(CC) $(CFLAGS) $< -lm -pthread

map.o: map.c map.h sorted_queue.h
	$(CC) $(CFLAGS) $<






.PHONY: clean

clean:
	rm -f *.o

########################################################

CC=gcc
CFLAGS= -ggdb -Wall
EJS = p2_e1a p2_e1b p2_e2 p2_e1a_bis p2_e1b_bis p2_e2_bis

########################################################

OBJECTSP2E1A = p2_e1a.o libstack.a
OBJECTSP2E1B = p2_e1b.o vertex.o libstack.a
OBJECTSP2E2	 = p2_e2.o graph.o vertex.o libstack.a
OBJECTSP2E31A = p2_e1a.o stack.o file_utils.o vertex.o
OBJECTSP2E31B = p2_e1b.o stack.o file_utils.o vertex.o
OBJECTSP2E32 = p2_e2.o graph.o vertex.o file_utils.o stack.o
########################################################

all: $(EJS) clear

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) 

p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B) 

p2_e2: $(OBJECTSP2E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2) 

p2_e1a_bis: $(OBJECTSP2E31A)
	$(CC) $(CFLAGS) -o p2_e1a_bis $(OBJECTSP2E31A) 

p2_e1b_bis: $(OBJECTSP2E31B)
	$(CC) $(CFLAGS) -o p2_e1b_bis $(OBJECTSP2E31B)  

p2_e2_bis: $(OBJECTSP2E32)
	$(CC) $(CFLAGS) -o p2_e2_bis $(OBJECTSP2E32)  

p2_e1a.o: p2_e1a.c 
	$(CC) $(CFLAGS) -c p2_e1a.c

p2_e1b.o: p2_e1b.c vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c

p2_e2.o: p2_e2.c graph.h vertex.h
	$(CC) $(CFLAGS) -c p2_e2.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h 
	$(CC) -c -o $@ $< $(CFLAGS)

file_utils.o: file_utils.c 
	$(CC) -c -o $@ $< $(CFLAGS)

libstack.a: stack.o file_utils.o
	$(AR) rcs $@ $^

# Por si se quisiera crear solo la biblioteca
libs: libstack.a

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

# Por si también se quisiera borrar la biblioteca libstack actual
remove:
	rm -rf *.o $(EJS)libstack.a







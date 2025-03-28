########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p3_e1 p3_e2a p3_e2b p3_e3
FLIBS= -lqueue -L.
########################################################
OBJECTSP3E1 = p3_e1.o delivery.o vertex.o 
OBJECTSP3E2A= p3_e2a.o delivery.o vertex.o queue.o 
OBJECTSP3E2B = p3_e2b.o graph.o vertex.o queue.o stack.o
OBJECTSP3E3 = p3_e3.o list.o file_utils.o
########################################################

all: $(EJS) clear

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP3E1) $(FLIBS)

p3_e2a: $(OBJECTSP3E2A)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP3E2A) -L.

p3_e2b: $(OBJECTSP3E2B)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP3E2B) -L.

p3_e3: $(OBJECTSP3E3)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP3E3) -L.
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

runv: all
#Basic Tests
	@echo ">>>>>>Running valgrind p3_e1"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e1 requests.txt
	@echo " "
	@echo ">>>>>>Running valgrind p3_e2a"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2a requests.txt
	@echo " "
	@echo ">>>>>>Running valgrind p3_e2b 100 400"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2b city_graph.txt 100 400
	@echo " "
	@echo ">>>>>>Running valgrind p3_e2b 100 700"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e2b city_graph.txt 100 700
	@echo " "
	@echo ">>>>>>Running valgrind p3_e3 1"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e3 grades.txt 1
	@echo " "
	@echo ">>>>>>Running valgrind p3_e3 -1"
	valgrind --leak-check=full --track-origins=yes -s ./p3_e3 grades.txt -1

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)












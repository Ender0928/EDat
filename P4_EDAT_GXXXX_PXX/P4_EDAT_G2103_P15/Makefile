include Makefile_ext
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p4_e1 p4_e2 
FLIBS= -L.
########################################################
OBJECTSP4E1 = p4_e1.o bstree.o vertex.o 
OBJECTSP4E2 = p4_e2.o bstree.o vertex.o file_utils.o search_queue.o
########################################################

all: 	$(EJS) clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP4E1) $(FLIBS)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSP4E2) $(FLIBS)
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
runv_e1: p4_e1
	valgrind --leak-check=full ./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" normal
	@echo ""
	valgrind --leak-check=full ./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" sorted
	@echo ""
	valgrind --leak-check=full ./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" normal
	@echo ""
	valgrind --leak-check=full ./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" sorted

runv_e2: p4_e2
	valgrind --leak-check=full ./p4_e2 ./data/data_string_10.txt ./out/data_string_10.out
	@echo ""
	valgrind --leak-check=full ./p4_e2 ./data/data_string_1K.txt ./out/data_string_1K.out
	@echo ""
	valgrind --leak-check=full ./p4_e2 ./data/data_string_2K.txt ./out/data_string_2K.out

clear:
	rm -rf *.o 

clear_files:
	rm -rf ./out/*.out 

clean:
	rm -rf *.o $(EJS)

clean_all:
	rm -rf *.o ./out/*.out $(EJS)




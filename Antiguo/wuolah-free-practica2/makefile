CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
LIBS = -lm -pthread

all: p2_e0_a p2_e0_b p2_e1 p2_e3_a p2_e3_b

p2_e0_a:p2_e0_a.o libstack_fp.a
	$(CC) -op2_e0_a p2_e0_a.o $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e0_b:p2_e0_b.o node.o libstack_fp.a
	$(CC) -op2_e0_b p2_e0_b.o node.o $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1:p2_e1.o libstack_fp.a
	$(CC) -op2_e1 p2_e1.o  $(LDFLAGS) $(LDLIBS) $(LIBS)


p2_e3_a:p2_e3_a.o stack.o element.o
	$(CC) -op2_e3_a p2_e3_a.o stack.o element.o

p2_e3_b:p2_e3_b.o stack.o element.o
	$(CC) -op2_e3_b p2_e3_b.o stack.o element.o

node.o: node.c node.h
	$(CC) -c node.c $(CFLAGS) $(IFLAGS)

graph.o: graph.c graph.h
	$(CC) -c graph.c $(CFLAGS) $(IFLAGS)

stack.o: stack.c stack.h element.h
	$(CC) -c stack.c $(CFLAGS)

element.o:element.c element.h types.h
		$(CC) -c element.c $(CFLAGS)

p2_e0_a.o:p2_e0_a.c stack_fp.h stack_types.h
	$(CC) -c p2_e0_a.c $(CFLAGS) $(IFLAGS)

p2_e0_b.o:p2_e0_b.c node.h stack_fp.h stack_types.h
	$(CC) -c p2_e0_b.c $(CFLAGS) $(IFLAGS)

p2_e1.o:p2_e1.c stack_fp.h
	$(CC) -c p2_e1.c $(CFLAGS) $(IFLAGS)

p2_e3_a.o:p2_e3_a.c stack.h element.h
	$(CC) -c p2_e3_a.c $(CFLAGS)

p2_e3_b.o:p2_e3_b.c stack.h element.h
	$(CC) -c p2_e3_b.c $(CFLAGS)



clean:
	@echo "borrando..."
	rm -rf *.o p2_e0_a p2_e0_b p2_e1 p2_e3_a p2_e3_b

CFLAGS=-W -Wall

all: stack

stack: stack.o iterator.o
	gcc $(CFLAGS) -o stack stack.o

clean:
	rm -f *.o stack

stack.o: stack.c stack.h iterator.h
iterator.o: iterator.c iterator.h

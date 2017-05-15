CFLAGS=-W -Wall

all: bstree

bstree: bstree.o
	gcc $(CFLAGS) -o bstree bstree.o

clean:
	rm -f *.o bstree

bstree.o: bstree.c bstree.h
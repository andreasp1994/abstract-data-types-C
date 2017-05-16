CFLAGS=-W -Wall

all: arraylist

arraylist: arraylist.o
	gcc $(CFLAGS) -o arraylist arraylist.o

clean:
	rm -f *.o arraylist

arraylist.o: arraylist.c arraylist.h
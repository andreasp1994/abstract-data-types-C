CFLAGS=-W -Wall

all: set

set: set.o
	gcc $(CFLAGS) -o set set.o

clean:
	rm -f *.o set

set.o: set.c set.h
CFLAGS=-W -Wall

all: map

map: map.o
	gcc $(CFLAGS) -o map map.o

clean:
	rm -f *.o map

map.o: map.c map.h
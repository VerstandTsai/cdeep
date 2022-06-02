CC = gcc
CFLAGS = -std=c99 -Wall -O3
LIBS = -lm

all: test.o deep.o matrix.o
	$(CC) test.o deep.o matrix.o -o test $(LIBS)

test.o: test.c deep.h
	$(CC) $(CFLAGS) -c test.c

deep.o: deep.c deep.h
	$(CC) $(CFLAGS) -c deep.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm -f test *.o


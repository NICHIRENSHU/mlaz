#This is makefile yeaah
CC=clang
CFLAGS=-I.
brum_all: main.c subirane.c
	$(CC) -o brum  -Wall -static  main.c subirane.c -pthread
brum_main: main.c
	$(CC) -o brum  -Wall -static  main.c
brum_o: main.o subirane.o
	$(CC) -o brum  -Wall -static  main.c subirane.c -lpthread
clean:
	rm -f brum main.o subirane.o


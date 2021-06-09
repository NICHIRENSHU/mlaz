#This is makefile yeaah
CC=gcc
CFLAGS=-I.
brum_all: main.c subirane.c
	$(CC) -o brum  -Wall -static  main.c subirane.c -pthread
brum_main: main.c
	$(CC) -o brum  -Wall -static  main.c
brum_o: main.o subirane.o
	$(CC) -o brum  -Wall -static  main.c subirane.c -lpthread
brum_evtest: main.c subirane.c evtest.c
	$(CC) -o brum  -Wall -static  main.c subirane.c evtest.c -pthread
clean:
	rm -f brum main.o subirane.o


CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o coloracao.o
	$(CC) $(CFLAGS) -o main main.o coloracao.o

main.o: main.c coloracao.h
	$(CC) $(CFLAGS) -c main.c

coloracao.o: coloracao.c coloracao.h
	$(CC) $(CFLAGS) -c coloracao.c

clean:
	rm -f *.o main main.exe
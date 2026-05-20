CC = gcc
CFLAGS = -Wall -Wextra -O2

all: benchmark

benchmark: main.o sorts.o utils.o
	$(CC) $(CFLAGS) -o benchmark main.o sorts.o utils.o

main.o: main.c sorts.h utils.h
	$(CC) $(CFLAGS) -c main.c

sorts.o: sorts.c sorts.h
	$(CC) $(CFLAGS) -c sorts.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o benchmark
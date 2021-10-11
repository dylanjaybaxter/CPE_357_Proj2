CC = gcc
CFLAGS = -Wall -g -ansi
LD = gcc
LDFLAGS = -g
all: fw main.o rlw.o hash.o

fw: rlw.o hash.o main.o
	$(LD) $(LDFLAGS) -o fw rlw.o hash.o main.o
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
rlw.o : rlw.c rlw.h
	$(CC) $(CFLAGS) -c -o rlw.o rlw.c
hash.o : hash.c hash.h
	$(CC) $(CFLAGS) -c -o hash.o hash.c
clean: fw
	rm rlw.o hash.o main.o
test: fw
	./fw -n 8 test.txt > testOut.txt
	~pn-cs357/demos/fw -n 8 test.txt > testSol.txt
	diff -s  testOut.txt testSol.txt
debug: fw
	gdb fw

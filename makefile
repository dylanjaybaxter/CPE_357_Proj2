CC = gcc
CFLAGS = -Wall -g -pg -ansi
LD = gcc
LDFLAGS = -g -pg
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
	diff -s testOut.txt testSol.txt
testman:
	./fw -n35000 /usr/share/man*/* > outme.txt
	~pn-cs357/demos/fw -n35000 /usr/share/man*/* > outsol.txt
	diff -s outme.txt outsol.txt
testwap:
	./fw -n35000 WAP.txt > WAPO.txt
	~pn-cs357/demos/fw -n35000 WAP.txt > WAPI.txt
	diff -s WAPO.txt WAPI.txt
debug: fw
	gdb fw

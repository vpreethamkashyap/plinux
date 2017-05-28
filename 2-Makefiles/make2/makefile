# MAKEFILE DEMO

TARGET=prog
OFLAG=-o
CFLAG=-c
CC=gcc

prog: prog.c myhead.h add.o mean.o mul.o sub.o
	$(CC) $(OFLAG) prog prog.c add.o mean.o mul.o sub.o

add.o: add.c myhead.h
	$(CC) $(CFLAG)  add.c

mean.o: mean.c myhead.h
	$(CC) $(CFLAG)  mean.c
	
mul.o: mul.c
	$(CC) $(CFLAG)  mul.c
	
sub.o: sub.c
	$(CC) $(CFLAG)  sub.c
	
clean:
	rm -f prog
	rm -f add.o
	rm -f mean.o
	rm -f mul.o
	rm -f sub.o

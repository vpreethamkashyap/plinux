TARGET1=add 
TARGET2=mean 
TARGET3=sub 
OFLAG=-o
CFLAG=-c
CC=gcc

ALL:$(TARGET1) $(TARGET3) $(TARGET2)

$(TARGET1) : myhead.h add.o main_add.c
	$(CC) $(OFLAG)  $(TARGET1) main_add.c add.o

$(TARGET2): myhead.h mean.o  main_mean.c
	$(CC) $(OFLAG) $(TARGET2) mean.o main_mean.c

$(TARGET3): myhead.h sub.o main_sub.c
	$(CC) $(OFLAG) $(TARGET3) sub.o main_sub.c

add.o: add.c
	$(CC) $(CFLAG)  add.c
mean.o: mean.c
	$(CC) $(CFLAG)  mean.c
sub.o: sub.c
	$(CC) $(CFLAG)  sub.c
clean:
	rm -f add mean sub
	rm -f add.o
	rm -f mean.o
	@rm -f mul.o
	@rm -f sub.o

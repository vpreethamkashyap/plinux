# Used For Arm Linux Compiler

#CC=arm-none-linux-gnueabi-gcc
# used for inbuilt GCC compiler
CC = gcc -ggdb3

CFLAGS := -I.
SRCS:= $(shell ls *.c)
OBJS= $(SRCS:.c=.o)

TARGET := daemon 

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) -lsqlite3
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

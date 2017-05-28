OFLAGS=-o
CFLAGS=-c
CC=gcc -pthread #-std=gnu99 -Wall

TARGET = entity
SRCS := $(shell find . -name '*.c')
OBJS= $(SRCS:.c=.o)

.PHONY: all objs

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lsqlite3

%.o: %.c 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM -MP $< >> $@ 

clean:
	rm -rf $(OBJS)  $(TARGET)

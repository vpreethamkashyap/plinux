OFLAG=-o
CFLAG=-c
CC=gcc -pthread #-std=gnu99 -Wall

APP = entity
SRCS := $(shell find . -name '*.c')
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

INCLUDES = -I.
CFLAGS = -c

.PHONY: all objs

all: $(APP)

$(APP):$(OBJS)
	$(CC) -o $@ $(OBJS) -lsqlite3

%.d:%.c
	$(CC) -MM -MP $< >> $@ 

objs: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJS)  $(APP) $(DEPS) 
	rm -rf obj

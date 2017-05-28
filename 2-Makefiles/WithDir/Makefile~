
all: createbin createexec # prog add.o sub.o mul.o mean.o


createbin: 
	mkdir -p Bin

createexec:
	cc -o Bin/prog prog.c add.c sub.c mul.c mean.c

# Insted You can also use normal procedure of creating all the object code

clean:
	rm -rf Bin
	rm -rf *.o


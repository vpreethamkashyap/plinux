#K_SRC=/lib/modules/`uname -r`/build
#K_SRC=${HOME}/easyarm/work/linux-3.2
#K_SRC=/home/naveen/work/openboard_AM335x/kernel/linux-3.2
K_SRC=/home/naveen/work/wega/phyBOARD-WEGA-AM335x/Linux/PD14.0.0/src/kernel/linux-3.2

#obj-m += modsimp.o
#obj-m += modsimp2.o

obj-m += obled.o
all:
	make -C ${K_SRC} M=${PWD} modules
clean:
#	rm -f modsimp.ko modsimp.o modsimp.d*
	rm -f obled.ko obled.o obled.d* *~ *.order *.mod.o *.symvers *.mod.c 

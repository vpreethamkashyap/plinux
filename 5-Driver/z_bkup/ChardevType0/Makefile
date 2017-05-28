obj-m  := chr_drv_skel.o
#obj-m  := usage.o

KDIR = /lib/modules/`(uname -r)`/build

all :
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean :
			rm -rf  *.o,.ko,mo*,*.mod.c


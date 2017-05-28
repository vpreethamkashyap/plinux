ifeq ($(FOO),ARM) 

# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)
$(info ************  Make file ARM step 2 ************)
$(info ***********************************************)
	KERNEL_SOURCE := /home/tsp/tlinux/mylinux/Tools/Kernel/linux-4.4
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else
$(info ************  Make file ARM step 1 ************)
$(info ***********************************************)
	src-m := $(notdir $(wildcard ${SUBDIRS}/*.c))
	src-mod := $(notdir $(wildcard ${SUBDIRS}/*.mod.c))
	src-m := $(filter-out ${src-mod}, ${src-m})
	obj-m := $(src-m:.c=.o)

endif
else	
$(info ***********************************************)
$(info ************  Make file X86 step 1 ************)
$(info ***********************************************)		
	obj-m :=tasklet.o
	KERNEL_SOURCE= /lib/modules/$(shell uname -r)/build	
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean




#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

static int __init init_kmod(void)
{
	printk("Kernel Module Registered\n");
	return 0;
}

static void __exit cleanup_kmod(void)
{
	printk("Kernel Module Unregistered");
}

module_init(init_kmod);
module_exit(cleanup_kmod);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tarun");
MODULE_DESCRIPTION("Kernel Module");


/*
 *
 *    .c 		converted to 	*.o
 *    .o 		converted to 	*.mod.o
 *    mod.o 	converted to 	*.ko
	CC [M]  /home/tsp/tlinux/git/tlinux/5-Driver/a_basics/0/kernel_module.o
	Building modules, stage 2.
	************  Make file ARM step 1 ************
	***********************************************
	MODPOST 1 modules
	CC      /home/tsp/tlinux/git/tlinux/5-Driver/a_basics/0/kernel_module.mod.o
	LD [M]  /home/tsp/tlinux/git/tlinux/5-Driver/a_basics/0/kernel_module.ko
 *
 *
 * */

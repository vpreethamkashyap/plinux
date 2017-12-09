#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

// Global variable for the mydev device number
#define CHAR_DEV_NAME 			"First_char_driver"
static dev_t mydev; 


/*********************************************************************************
 * Function:			my_module_init
 * Description:			Initialize the Driver
 * 
 * List of Function:  	MKDEV();
 * 						register_chrdev_region();
 * 						cdev_alloc();
 * 						cdev_init();
 * 						cdev_add();
 *
 *


Open this Fun def from geany linux/fs/char_dev.c

 * alloc_chrdev_region() - register a range of char device numbers
 * @dev: output parameter for first assigned number
 * @baseminor: first of the requested range of minor numbers
 * @count: the number of minor numbers required
 * @name: the name of the associated device or driver
 *
 * Allocates a range of char device numbers.  The major number will be
 * chosen dynamically, and returned (along with the first minor number)
 * in @dev.  Returns zero or a negative error code.

	int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,
			const char *name)

 ********************************************************************************/
 
static int __init my_module_init(void) 
{
	int ret;
	printk(KERN_INFO "Hii module registered");
	
	if ((ret = alloc_chrdev_region(&mydev, 0, 3, CHAR_DEV_NAME)) < 0)
	{
		return ret;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(mydev), MINOR(mydev));
	return 0;
}

static void __exit my_module_exit(void)
{
	unregister_chrdev_region(mydev, 3);
	printk(KERN_INFO "Hii module unregistered");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tarun");
MODULE_DESCRIPTION("Character Driver");

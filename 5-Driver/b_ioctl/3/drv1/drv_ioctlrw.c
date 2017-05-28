#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/device.h>
#include "../../../b_ioctl/3/drv1/ioctl_data.h"

#define CHAR_DEV_NAME 		"Ioctl_rw_node"
#define SUCCESS 					0

dev_t mydev;
struct cdev *c_dev;
static struct class *cl;

int count = 1;

static struct my_data my_data = 
{
    .i = -100,
    .x = 100,
    .s = "Linux Kernel",
};

/*********************************************************************************
 * Function:			char_dev_open
 * Description:		Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *inode,struct file  *file)
{
	static int counter = 0;
	counter++;
	printk(KERN_INFO "Number of times open() was called: %d\n", counter);
	printk (KERN_INFO " MAJOR number = %d, MINOR number = %d\n",imajor (inode), iminor (inode));
	printk(KERN_INFO "Process id of the current process: %d\n",current->pid );
	printk (KERN_INFO "ref=%d\n", module_refcount(THIS_MODULE));
	return SUCCESS;
}

/*********************************************************************************
 * Function:			char_dev_release
 * Description:		Releasse the Driver
 ********************************************************************************/
static int char_dev_release(struct inode *inode,struct file *file)
{
	return SUCCESS;
}

/*********************************************************************************
 * Function:			chrdev_ioctl
 * Description:		 
 ********************************************************************************/
static long chrdev_ioctl (struct file *fp, unsigned int cmd, unsigned long arg)
{
	int size, rc, direction;
	void __user *ioargp = (void __user *)arg;  
	
	if (_IOC_TYPE (cmd) != IOCTL_MAGIC)
	{
		printk (KERN_INFO " got invalid case, CMD=%d\n", cmd);
		return -EINVAL;
	}

	direction = _IOC_DIR (cmd);
	size = _IOC_SIZE (cmd);

	switch (direction) 
	{
		case _IOC_WRITE:
			printk(KERN_INFO  " reading = %d bytes from user-space and writing to device\n",size);
			rc = copy_from_user (&my_data, ioargp, size);
			printk(KERN_INFO "my_data.i = %d\n    (int)my_data.x = %ld\n    my_data.s = %s\n",my_data.i, my_data.x, my_data.s);
		return rc;

		case _IOC_READ:
			printk (KERN_INFO  " reading device and writing = %d bytes to user-space\n", size);
			printk (KERN_INFO  "my_data.i = %d\n    (int)my_data.x = %ld\n    my_data.s = %s\n",my_data.i, my_data.x, my_data.s);
			rc = copy_to_user (ioargp, &my_data, size);
		return rc;

		default:
			printk (KERN_INFO " got invalid case, CMD=%d\n", cmd);
		return -EINVAL;
	}
}

/*********************************************************************************
 * Function:			file_operations
 * Description:		file  operations
 ********************************************************************************/
static struct file_operations char_dev_fops = 
{
	.owner = THIS_MODULE,
	.unlocked_ioctl = chrdev_ioctl,
	.open = char_dev_open,
	.release = char_dev_release,
};

/*********************************************************************************
 * Function:			char_dev_init
 * Description:		Initialize the Driver
 ********************************************************************************/
static __init int char_dev_init(void)
{
	int ret;

	if (alloc_chrdev_region (&mydev, 0, count, CHAR_DEV_NAME) < 0) 
	{
		printk (KERN_ERR "failed to reserve major/minor range\n");
		return -1;
	}

	if (!(c_dev = cdev_alloc ()))
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		unregister_chrdev_region (mydev, count);
		return -1;
	}
	
	cdev_init(c_dev,&char_dev_fops);
	ret=cdev_add(c_dev,mydev,count);
	if( ret < 0 ) 
	{
		printk(KERN_INFO "Error registering device driver\n");
		cdev_del (c_dev);
		unregister_chrdev_region (mydev, count); 	
		return -1;
	}

	cl = class_create (THIS_MODULE, "VIRTUAL");
	device_create (cl, NULL, mydev, NULL, "%s", "Ioctl_rw_node");
	printk(KERN_INFO"\nDevice Registered: %s\n",CHAR_DEV_NAME);
	printk (KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));
	return 0;
}

/*********************************************************************************
 * Function:			char_dev_exit
 * Description:		Exit from Driver
 ********************************************************************************/
static __exit void  char_dev_exit(void)
{
	device_destroy (cl, mydev);
	class_destroy (cl);
	cdev_del(c_dev);
	unregister_chrdev_region(mydev,1);
	printk(KERN_INFO "\n Driver unregistered \n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);
MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

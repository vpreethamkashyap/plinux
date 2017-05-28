#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/device.h>
#include <linux/slab.h>
#include "../../../b_ioctl/2/drv2/ioctl_data.h"

#define CHAR_DEV_NAME 	"ioctl_var"
#define SUCCESS 0

int count = 1;

dev_t mydev;
struct cdev *c_dev;
static struct class *cl;

/*********************************************************************************
 * Function:			char_dev_open
 * Description:		Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *inode,struct file  *file)
{
	static int counter = 0;
	counter++;
	printk(KERN_INFO "Number of times open() was called: %d\n", counter);
	printk (KERN_INFO "MAJOR number = %d, MINOR number = %d\n",imajor (inode), iminor (inode));
	printk(KERN_INFO "Process id of the current process: %d\n",current->pid );
	printk (KERN_INFO "Ref=%d\n", module_refcount(THIS_MODULE));
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
static inline long chrdev_ioctl (struct file *fp, unsigned int cmd, unsigned long arg)
{
	int i, rc, direction;
	int size;
	char *buffer;
	void __user *ioargp = (void __user *)arg;

	// make sure it is a valid command 
	if (_IOC_TYPE (cmd) != IOCTL_MAGIC)
	{
		printk (KERN_WARNING " got invalid case, CMD=%d\n", cmd);
		return -EINVAL;
	}

	// get the size of the buffer and kmalloc it 
	size = _IOC_SIZE (cmd);
	buffer = kmalloc ((size_t) size, GFP_KERNEL);
	if (!buffer) 
	{
		printk (KERN_ERR "Kmalloc failed for buffer\n");
		return -ENOMEM;
	}

	printk (KERN_ERR "fill it with X \n");
	memset (buffer, 'X', size);	
	direction = _IOC_DIR (cmd);

	switch (direction) 
	{
		case _IOC_WRITE:
			printk(KERN_INFO " reading = %d bytes from user-space and writing to device\n", size);
			rc = copy_from_user (buffer, ioargp, size);
			printk (KERN_INFO "_IOC_WRITE command copy_from_user to kernel = %d\n", rc);
		break;

		case _IOC_READ:
			printk (KERN_INFO " reading device and writing = %d bytes to user-space\n", size);
			rc = copy_to_user (ioargp, buffer, size);
			printk (KERN_INFO "_IOC_READ from kernel & copy_to_user = %d\n", rc);
		break;
		
		default:
			printk (KERN_WARNING " got invalid case, CMD=%d\n", cmd);
		return -EINVAL;
	}
	
	for (i = 0; i < size; i++)
	{
		printk (KERN_INFO "%c", buffer[i]);
	}
	printk (KERN_INFO "\n");

	if (buffer)
		kfree (buffer);
		
	return rc;
}

/********************************************************************************
 * Function:			char_dev_fops
 * Description:		File operations
 ********************************************************************************/
static struct file_operations char_dev_fops = 
{
	.owner = THIS_MODULE,
	.unlocked_ioctl = chrdev_ioctl,
	.open = char_dev_open,
	.release = char_dev_release,
};

/********************************************************************************
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
	device_create (cl, NULL, mydev, NULL, "%s", "ioctl_var");
	printk(KERN_INFO"\nDevice Registered: %s\n",CHAR_DEV_NAME);
	printk (KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));

	return 0;
}

/********************************************************************************
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
MODULE_AUTHOR("TARUN");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

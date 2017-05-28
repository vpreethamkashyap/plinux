#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

/* Add your variables here */

static dev_t mydev;
static struct cdev c_dev;

/*********************************************************************************
 * Function:			char_dev_open
 * Description:			Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: In open\n");
	/* Add code here */
	return 0;
}

/*********************************************************************************
 * Function:			char_dev_release
 * Description:			Releasse the Driver
 ********************************************************************************/
static int char_dev_release(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: In close\n");
	/* Add code here */
	return 0;
}

/*********************************************************************************
 * Function:			char_dev_read
 * Description: 		Read from Driver
 * unsigned long copy_to_user (void __user *to,const void *from,unsigned long  	n);
 * Copy data from kernel space to user space.
 * Returns number of bytes that could not be copied. On success, this will be zero. 
 ********************************************************************************/
static ssize_t char_dev_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: In read - Buf: %p; Len: %zd; Off: %Ld\nData:\n", buf, len, *off);
	/* Add code here */
	return 0 /* read cnt */;
}

/*********************************************************************************
 * Function:			char_dev_write
 * Description:			Writes to Driver
 * 
 * unsigned long copy_from_user(void *to,const void __user *from,unsigned long n); 
 * Copy data from user space to kernel space.
 * Returns number of bytes that could not be copied. On success, this will be zero. 
 ********************************************************************************/
static ssize_t char_dev_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	int i;
	char t;

	printk(KERN_INFO "Driver: In write - Buf: %p; Len: %zd; Off: %Ld\nData:\n", buf, len, *off);
	printk(KERN_INFO);
	for (i = 0; i < len; i++)
	{
		if (copy_from_user(&t, buf + i, 1))
		{
			return -EFAULT;
		}
		printk("%02X(%c) ", t, t);
	}
	printk("\n");
	/* Add code here */

	return len /* wrote cnt */;
}

/*********************************************************************************
 * Function:			char_dev_fops
 * Description:			File operations
 ********************************************************************************/
static struct file_operations char_dev_fops =
{
	.owner = THIS_MODULE,
	.open = char_dev_open,
	.release = char_dev_release,
	.read = char_dev_read,
	.write = char_dev_write
};

/*********************************************************************************
 * Function:			module_init
 * Description:			Initialize the Driver
 * 
 * List of Function:	alloc_chrdev_region();
 * 						cdev_alloc();
 * 						cdev_init();
 * 						cdev_add();			
 ********************************************************************************/
int __init init_module()
{
	int ret;
	printk(KERN_INFO "Hello Universe\n");
	if ((ret = alloc_chrdev_region(&mydev, FIRST_MINOR, MINOR_CNT, "null")) < 0)
	{
		return ret;
	}

	printk(KERN_INFO "(Major, Minor): (%d, %d)\n", MAJOR(mydev), MINOR(mydev));
	cdev_init(&c_dev, &char_dev_fops);
	if ((ret = cdev_add(&c_dev, mydev, MINOR_CNT)) < 0)
	{
		unregister_chrdev_region(mydev, MINOR_CNT);
		return ret;
	}	
	return 0;
}

/*********************************************************************************
 * Function:			module_exit
 * Description:			Exit from Driver
 ********************************************************************************/
void __exit cleanup_module()
{
	cdev_del(&c_dev);
	unregister_chrdev_region(mydev, MINOR_CNT);
	printk(KERN_INFO "Bye Universe\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TARUN");
MODULE_DESCRIPTION("First Character Driver");

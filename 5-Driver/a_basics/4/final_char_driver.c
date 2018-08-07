#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t mydev;
static struct cdev *c_dev;
static struct class *cl;

static char character_value = 'A';

/*********************************************************************************
 * Function:			char_dev_open
 * Description:			Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "char_drv_dynamic open operation invoked \n");
	return 0;
}

/*********************************************************************************
 * Function:			char_dev_release
 * Description:			Releasse the Driver
 ********************************************************************************/
static int char_dev_release(struct inode *i, struct file *f)
{
	printk(KERN_INFO "char_drv_dynamic open operation released \n");
	return 0;
}

/*********************************************************************************
 * Function:			char_dev_read
 * Description: 		Read from Driver
 ********************************************************************************/
static ssize_t char_dev_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	/** try to understand the offset this read will work only once if you want to work continues then make off  = 0 in write **/       
       
	if (*off == 0)
	{
		if (raw_copy_to_user(buf, &character_value, 1))
		{
			return -EFAULT;
		}
		//*off += 1;
		printk(KERN_INFO "char_drv_read offset is null \n");
		return 1;
	}
	else
	{
		printk(KERN_INFO "char_drv_read offset is not null \n");
		return 0;
	}
}
/*********************************************************************************
 * Function:			char_dev_write
 * Description:			Writes to Driver
 ********************************************************************************/
static ssize_t char_dev_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	if (raw_copy_from_user(&character_value, buf, 1))
	{
	 	return -EFAULT;
	}	
	printk(KERN_INFO "char_dev_write done \n");
	return len;
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
static int __init my_module_init(void)
{
	int ret,count=1;
	struct device *dev_ret;

	if ((ret = alloc_chrdev_region(&mydev, FIRST_MINOR, MINOR_CNT, "final_driver")) < 0)
	{
		return ret;
	}
	if (!(c_dev = cdev_alloc ()))
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		unregister_chrdev_region (mydev, count);
		return -1;
 	}
	cdev_init(c_dev, &char_dev_fops);
	if ((ret = cdev_add(c_dev, mydev, MINOR_CNT)) < 0)
	{
		unregister_chrdev_region(mydev, MINOR_CNT);
		return ret;
	}
	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
	{
		cdev_del(c_dev);
		unregister_chrdev_region(mydev, MINOR_CNT);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, mydev, NULL, "mychar%d", FIRST_MINOR)))
	{
		class_destroy(cl);
		cdev_del(c_dev);
		unregister_chrdev_region(mydev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}
	return 0;
}

/*********************************************************************************
 * Function:			my_module_exit
 * Description:			Exit from Driver
 ********************************************************************************/
static void __exit my_module_exit(void)
{
	device_destroy(cl, mydev);
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(mydev, MINOR_CNT);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TARUN");
MODULE_DESCRIPTION("A Character Driver");

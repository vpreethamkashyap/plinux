#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define MAJORNO 				300
#define MINORNO  				0
#define CHAR_DEV_NAME 			"cdev_static"
#define MAX_LENGTH 				4000
#define SUCCESS 				0

static char char_device_buf[MAX_LENGTH];
struct cdev *c_cdev;
dev_t mydev;
int count = 1,inuse_u32 = 0;


/*********************************************************************************
 * Function:			char_dev_open
 * Description:			Opens the Driver
 * FUNCTION  Invoke: 	This function will be ionvoked by user application
 ********************************************************************************/
static int char_dev_open(struct inode *inode,struct file  *file)
{
	printk(KERN_INFO "Open operation invoked \n");
	
	/* Check Driver is in use or not */
	if(inuse_u32)
	{
		printk(KERN_INFO "\nDevice busy %s\n",CHAR_DEV_NAME);
		return -EBUSY;
	}	
	
	inuse_u32 = 1;
	return SUCCESS;		
}

/*********************************************************************************
 * Function:			char_dev_release
 * Description:			Releasse the Driver
 ********************************************************************************/
static int char_dev_release(struct inode *inode, struct file *file)
{
	inuse_u32=0;
	return SUCCESS;
}

/*********************************************************************************
 * Function:			char_dev_write
 * Description:			Writes to Driver
 ********************************************************************************/
static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes = lbuf - raw_copy_from_user (char_device_buf, buf, lbuf);
	*ppos += nbytes;
	printk (KERN_INFO "\n Rec'vd data from app %s , nbytes=%d\n",char_device_buf,nbytes);
	return nbytes;
}

/*********************************************************************************
 * Function:			char_dev_read
 * Description: 		Read from Driver
 ********************************************************************************/
static ssize_t char_dev_read(struct file *file, char *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes = lbuf - raw_copy_to_user (buf, char_device_buf, lbuf);
	*ppos += nbytes;
	printk (KERN_INFO "\n sent data to app %s , nbytes=%d\n",buf,nbytes);
	return nbytes;
}

/*********************************************************************************
 * Function:			char_dev_fops
 * Description:			File operations
 ********************************************************************************/
static struct file_operations char_dev_fops = 
{
	.owner 		= THIS_MODULE,
	.write 		= char_dev_write,
	.open 		= char_dev_open,
	.release 	= char_dev_release,
	.read 		= char_dev_read
};

/*********************************************************************************
 * Function:			my_module_init
 * Description:			Initialize the Driver
 * 
 * List of Function:  	MKDEV();
 * 						register_chrdev_region();
 * 						cdev_alloc();
 * 						cdev_init();
 * 						cdev_add();

int register_chrdev_region(dev_t from, unsigned count, const char *name)

 * register_chrdev_region() - register a range of device numbers
 * @from: the first in the desired range of device numbers; must include
 *        the major number.
 * @count: the number of consecutive device numbers required
 * @name: the name of the device or driver.
 *
 * Return value is zero on success, a negative error code on failure.

cdev_alloc() - allocate a cdev structure
 *
 * Allocates and returns a cdev structure, or NULL on failure.


struct cdev *cdev_alloc(void)

 ********************************************************************************/
static int __init my_module_init(void)
{
	int ret;
	
	mydev = MKDEV(MAJORNO,MINORNO);
	register_chrdev_region(mydev,count,CHAR_DEV_NAME); 
	
	if (!(c_cdev = cdev_alloc ())) 
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		unregister_chrdev_region (mydev, count);
		return -1;
 	}
 	


	cdev_init(c_cdev,&char_dev_fops);
	ret	= cdev_add(c_cdev,mydev,count);
	
	if(ret < 0) 
	{
		printk("Error registering device driver\n");
		return ret;
	}

	printk(KERN_INFO"\nDevice Registered with this owner %s\n",c_cdev->owner->name);

	printk(KERN_INFO"\nDevice Registered %s\n",CHAR_DEV_NAME); 	
	printk (KERN_INFO " char_driver_static Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));
	memset(char_device_buf,'\0',MAX_LENGTH);
	return 0;
}

/*********************************************************************************
 * Function:			my_module_exit
 * Description:			Exit from Driver
 ********************************************************************************/
static void __exit my_module_exit(void)
{	
	cdev_del(c_cdev);
	unregister_chrdev_region(mydev,1);
	printk(KERN_INFO "\n Driver unregistered \n");
}

module_init(my_module_init);
module_exit(my_module_exit);
MODULE_AUTHOR("TARUN");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");


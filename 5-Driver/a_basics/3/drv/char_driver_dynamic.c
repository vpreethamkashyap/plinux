#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/slab.h>

#define CHAR_DEV_NAME 					"char_driver_dynamic_new"
#define MAX_LENGTH 						4000
#define SUCCESS 						0
#define FIRST_MINOR 0
#define MINOR_CNT 1

static char *char_device_buf;
struct cdev *c_cdev;
static struct class *cl;
dev_t mydev;

/*********************************************************************************
 * Function:			char_dev_open
 * Description:			Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *inode,struct file  *file)
{
	printk(KERN_INFO "char_drv_dynamic open operation invoked \n");
	return SUCCESS;
}

/*********************************************************************************
 * Function:			char_dev_release
 * Description:			Releasse the Driver
 ********************************************************************************/
static int char_dev_release(struct inode *inode,struct file *file)
{
	return SUCCESS;
}

/*********************************************************************************
 * Function:			char_dev_write
 * Description:			Writes to Driver
 * 
 * unsigned long copy_from_user(void *to,const void __user *from,unsigned long n); 
 * Copy data from user space to kernel space.
 * Returns number of bytes that could not be copied. On success, this will be zero. 
 ********************************************************************************/
static ssize_t char_dev_write(struct file *file,const char *buf,size_t lbuf,loff_t *ppos)
{
	int nbytes; 			
	printk(KERN_INFO "Rec'vd from App data");
	
	/** to, from ,how many bytes  **/
	nbytes = lbuf - raw_copy_from_user( char_device_buf + *ppos, buf, lbuf ); 
	*ppos += nbytes;
	printk(KERN_INFO "%s of length %d \n",char_device_buf, nbytes);
	return nbytes;
}

/*********************************************************************************
 * Function:			char_dev_read
 * Description: 		Read from Driver
 * unsigned long copy_to_user (void __user *to,const void *from,unsigned long  	n);
 * Copy data from kernel space to user space.
 * Returns number of bytes that could not be copied. On success, this will be zero. 
 ********************************************************************************/
static ssize_t char_dev_read(struct file *file, char *buf, size_t lbuf, loff_t *ppos)
{
	printk(KERN_INFO "lbuf %d \n ",lbuf);
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
 * List of Function:	alloc_chrdev_region();
 * 						cdev_alloc();
 * 						cdev_init();
 * 						cdev_add();			
 ********************************************************************************/
static __init int my_module_init(void)
{
	int ret,count=1;

	struct device *dev_ret;

	if (alloc_chrdev_region (&mydev, 0, count, CHAR_DEV_NAME) < 0) 
	{
		printk (KERN_ERR "failed to reserve major/minor range\n");
		return -1;
	}

	if (!(c_cdev = cdev_alloc ())) 
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		unregister_chrdev_region (mydev, count);
		return -1;
 	}

	cdev_init(c_cdev,&char_dev_fops);
	ret = cdev_add(c_cdev,mydev,count);
	if( ret < 0 ) 
	{
		printk(KERN_INFO "Error registering device driver\n");
		cdev_del (c_cdev);
		unregister_chrdev_region (mydev, count); 	
		return -1;
	}
	
	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
	{
		cdev_del(c_cdev);
		unregister_chrdev_region(mydev, MINOR_CNT);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, mydev, NULL, "tchar%d", FIRST_MINOR)))
	{
		class_destroy(cl);
		cdev_del(c_cdev);
		unregister_chrdev_region(mydev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}

	printk(KERN_INFO"\n Device Registered: %s\n",CHAR_DEV_NAME);
	printk (KERN_INFO " char_drv_dynamic Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));
	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);
	return 0;
}

/*********************************************************************************
 * Function:			my_module_exit
 * Description:			Exit from Driver
 ********************************************************************************/
static __exit void  my_module_exit(void)
{	
	 cdev_del(c_cdev);
	 unregister_chrdev_region(mydev,1);
	 kfree(char_device_buf);
	 printk(KERN_INFO "\n char_drv_dynamic Driver unregistered \n");
}

module_init(my_module_init);
module_exit(my_module_exit);
MODULE_AUTHOR("TARUN");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

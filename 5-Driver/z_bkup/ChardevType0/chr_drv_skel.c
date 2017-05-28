#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define MAJORNO 						300
#define MINORNO  						0
#define CHAR_DEV_NAME 			"sample_cdrv"
#define MAX_LENGTH 					4000
#define SUCCESS 						0

dev_t mydev;
struct cdev *sample_cdev;

int count=1,inuse=0;
static char char_device_buf[MAX_LENGTH];

static int char_dev_open(struct inode *inode, struct file  *file)
{
   if(inuse)
   {
      printk(KERN_INFO "\nDevice busy %s\n",CHAR_DEV_NAME);
      return -EBUSY;
   }   
   inuse=1;
   printk(KERN_INFO "Open operation invoked \n");
   return SUCCESS;      
}

static int char_dev_release(struct inode *inode, struct file *file)
{
   inuse=0;
   return SUCCESS;
}

static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes = copy_from_user (char_device_buf , &buf, lbuf);
	
	printk (KERN_INFO "\n Date nbytes received from=%d\n",char_device_buf,nbytes);
	printk (KERN_INFO "\n Received data from app %s\n", buf);
	return nbytes;
}

static ssize_t char_dev_read(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
	char char_device_Rx_buf[10]= "1234567890";
	
	printk (KERN_INFO "\n Transmitted data from app");
	
	int nbytes = copy_to_user (buf , &char_device_Rx_buf, lbuf);

	printk (KERN_INFO "\n Transmitted data from app %s , nbytes=%d\n",char_device_Rx_buf,nbytes);
	printk (KERN_INFO "\n Trasmission to app %s\n", buf);
	return nbytes;
}

static struct file_operations char_dev_fops = {
   .owner = THIS_MODULE,
   .write = char_dev_write,
   .read = char_dev_read,
   .open = char_dev_open,
   .release = char_dev_release
};

static int __init char_dev_init(void)
{
   int ret;
   
   mydev = MKDEV(MAJORNO,MINORNO);
   register_chrdev_region(mydev,count,CHAR_DEV_NAME); 
   sample_cdev= cdev_alloc();
   cdev_init(sample_cdev,&char_dev_fops);
   ret=cdev_add(sample_cdev,mydev,count);
   
   if(ret < 0) 
   {
      printk("Error registering device driver\n");
      return ret;
   }
   
   printk(KERN_INFO"\nDevice Registered %s\n",CHAR_DEV_NAME);    
   memset(char_device_buf,'\0',MAX_LENGTH);
   return 0;
}

static void __exit char_dev_exit(void)
{   
	cdev_del(sample_cdev);
	unregister_chrdev_region(mydev,1);
	printk(KERN_INFO "\n Driver unregistered \n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_AUTHOR("TEAM");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");
/* End of code */

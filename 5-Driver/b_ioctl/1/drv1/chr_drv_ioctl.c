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
#include "../../../b_ioctl/1/drv1/ioctl_const.h"

#define CHAR_DEV_NAME 		"Basic_ioctl"
#define MAX_LENGTH 				 4000
#define SUCCESS 					 0

dev_t mydev;
int count = 1;
struct cdev *c_dev;
static struct class *cl;

static char *char_device_buf;

static unsigned int length = MAX_LENGTH;


/*********************************************************************************
 * Function:			char_dev_open
 * Description:		Opens the Driver
 ********************************************************************************/
static int char_dev_open(struct inode *inode, struct file  *file)
{
	static int counter = 0;
	counter++;
	
	printk("char_dev_opend\n");
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
 * Function:			char_dev_read
 * Description: 	Read from Driver
 ********************************************************************************/
static ssize_t char_dev_read(struct file *file,char *buf,size_t lbuf,loff_t *ppos)
{
	int maxbytes; 		//	number of bytes from ppos to MAX_LENGTH 
	int bytes_to_do; 	//	number of bytes to read 
	int nbytes; 			//	number of bytes actually read 

	maxbytes = MAX_LENGTH - *ppos;
	
	if( maxbytes > lbuf )
	{
		bytes_to_do = lbuf;
	}
	else
	{
		bytes_to_do = maxbytes;
	}
	
	if( bytes_to_do == 0 ) 
	{
		printk("Reached end of device\n");
		return -ENOSPC; 	// Causes read() to return EOF
	}	
	
	nbytes = bytes_to_do - copy_to_user( buf,char_device_buf + *ppos,bytes_to_do ); 
	*ppos += nbytes;
	return nbytes;	
}


/*********************************************************************************
 * Function:			char_dev_write
 * Description:		Writes to Driver
 ********************************************************************************/
static ssize_t char_dev_write(struct file *file,const char *buf,size_t lbuf,loff_t *ppos)
{
	int nbytes; 			// Number of bytes written 
	int bytes_to_do; 	// Number of bytes to write 
	int maxbytes; 		// Maximum number of bytes that can be written 

	maxbytes = MAX_LENGTH - *ppos;

	if(maxbytes > lbuf) 
	{
		bytes_to_do = lbuf;
	}
	else
	{
		bytes_to_do = maxbytes;
	}

	if(bytes_to_do == 0) 
	{
		printk("Reached end of device\n");
		return -ENOSPC; //	Returns EOF at write() 
	}

	nbytes = bytes_to_do - copy_from_user( char_device_buf + *ppos,buf,bytes_to_do ); 
	*ppos += nbytes;
	return nbytes;
}


/**********************************************************************************
 * Function:		char_dev_ioctl
 * Description: big_kernel_lock()	
 * 							ioctl----> sys_ioctl---->do_ioctl --->fops--->ioctl==> char_dev_ioctl 
 * 							unlock()

**********************************************************************************/
static inline long char_dev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	// step 1: verify args

	unsigned int i, size;
	char *new_buf;
	char c,Command;
	int retbytes;
	
	if( _IOC_TYPE(cmd) != IOCTL_MAGIC )
	{
		Command  = _IOC_TYPE(cmd);
		printk(KERN_DEBUG "IOCTL Failed due to _IOC_TYPE(cmd) != IOCTL_MAGIC  %d\n",Command);
		printk(KERN_DEBUG "IOCTL Failed due to _IOC_TYPE(cmd) != IOCTL_MAGIC  %c\n",Command);
		return -ENOTTY;
	}
	
	if( _IOC_NR(cmd) > IOCTL_MAX_CMDS )
	{
		printk(KERN_DEBUG "IOCTL Failed due to _IOC_NR(cmd) > IOCTL_MAX_CMDS\n");
		return -ENOTTY;
	}
	
	if( _IOC_DIR(cmd) & _IOC_READ )
	{
		if( !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd) ) )
		{
			printk(KERN_DEBUG "IOCTL Failed due to access_ok\n");
			return -EFAULT;
		}
	}
	
	if( _IOC_DIR(cmd) & _IOC_WRITE )
	{
		if( !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd) ) )
		{
			printk(KERN_DEBUG "IOCTL Failed due to access_ok\n");
			return -EFAULT;
		}
	}

	switch(cmd) 
	{
		case IOCTL_FILL_ZERO:
			for(i=0; i<MAX_LENGTH; i++)
			{
				 char_device_buf[i] = 0;
			}               
			printk(KERN_DEBUG " FILL_ZERO config executed\n ");
		break;

    case IOCTL_FILL_CHAR:
		retbytes = copy_from_user( &c, (char *)arg, sizeof(char) );
		for(i = 0; i < MAX_LENGTH; i++)
		{
			char_device_buf[i] = c;
		}
		printk(KERN_DEBUG "FILL_CHAR config executed \n");
		break;
    
    case IOCTL_SET_SIZE:
			printk(KERN_DEBUG "IOCTL_SET_SIZE config executed \n");
			if(!capable(CAP_SYS_ADMIN))
			{
				printk(KERN_DEBUG "IOCTL_SET_SIZE capable problem\n");
				return -EPERM;
			}
			retbytes = copy_from_user(&size, (unsigned int*)arg,sizeof(unsigned int));
						
			new_buf = (char *)kmalloc(size * sizeof(char),GFP_KERNEL);
			
			if(!new_buf) 
				return -ENOSPC;
			
			kfree(char_device_buf);
			char_device_buf = (char *)new_buf;
		
			for(i=0; i<size; i++) 
			{
				char_device_buf[i] = 0;
			}
			filp->f_pos = 0;
			printk(KERN_DEBUG "SET_SIZE config executed\n");
		break;
	
		case IOCTL_GET_SIZE:
			if (!capable(CAP_SYS_ADMIN))
			{
				printk(KERN_DEBUG "IOCTL_GET_SIZE not capable \n");
				return -EPERM;
			}
			size = MAX_LENGTH;
      retbytes = copy_to_user((unsigned int*)arg,&size,sizeof(unsigned int));
			printk(KERN_DEBUG "GET_SIZE config executed \n");	
		break;
	}
	return SUCCESS;
}	

/*********************************************************************************
 * Function:			char_dev_fops 
 * Description:		File operations
 ********************************************************************************/
static struct file_operations char_dev_fops = 
{
	.owner = THIS_MODULE,
	.read = char_dev_read,
	.write = char_dev_write,
	.open = char_dev_open,
	.release = char_dev_release,
	.unlocked_ioctl = char_dev_ioctl,
};

/*********************************************************************************
 * Function:			char_dev_init
 * Description:		Initialize the Driver
 ********************************************************************************/
static __init int char_dev_init(void)
{
	int ret;

	if(alloc_chrdev_region (&mydev, 0, count, CHAR_DEV_NAME) < 0) 
	{
		printk (KERN_ERR "failed to reserve major/minor range\n");
		return -1;
	}

	if(!(c_dev = cdev_alloc ()))
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		unregister_chrdev_region (mydev, count);
		return -1;
	}

	cdev_init(c_dev,&char_dev_fops);

	ret = cdev_add(c_dev,mydev,count);
	if( ret < 0 ) 
	{
		printk(KERN_INFO "Error registering device driver\n");
		cdev_del (c_dev);
		unregister_chrdev_region (mydev, count); 	
		return -1;
	}

	cl = class_create (THIS_MODULE, "VIRTUAL");
	device_create (cl, NULL, mydev, NULL, "%s", "Basic_ioctl");
	printk(KERN_INFO"\nDevice Registered: %s\n",CHAR_DEV_NAME);
	printk (KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));
	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);
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
	 kfree(char_device_buf);
	 printk(KERN_INFO "\n Driver unregistered \n");
}


module_init(char_dev_init);
module_exit(char_dev_exit);
MODULE_AUTHOR("IOCTL");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

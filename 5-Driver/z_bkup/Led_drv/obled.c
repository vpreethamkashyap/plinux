#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
//#include<uaccess.h>
#include<linux/gpio.h>

#define GPIO_NUM 105

int ival=15,maj_number;
char sval[10] ="sivabuff";
char loacalbuff[20] ="sivabuff";

//module_param(ival, int, S_IRUGO);
//module_param(sval, charp, S_IRUGO);

void disp_msg(char *str)
{
 printk(KERN_ALERT "STR %s %s : %d\n",str,sval,ival);
}

int obled_open (struct inode *my_innode, struct file *my_fp)
{
	disp_msg("my drv open");
	gpio_request(GPIO_NUM,"LED1");
	gpio_direction_output(GPIO_NUM,1);
	return 0;
}

int obled_close (struct inode *my_innode, struct file *my_fp)
{
	disp_msg("my drv close");
	gpio_free(GPIO_NUM);
	return 0;
}


ssize_t  obled_read (struct file *my_fp, char __user *my_ptr, size_t mysize, loff_t *my_loff_t)
{
#if 0	/* Need to check */
	//copy_to_user(my_ptr,loacalbuff,mysize);
	//copy_from_user(loacalbuff,my_ptr,mysize);
#endif
	disp_msg("my drv read");
	my_ptr="mydrvread";
	//printk(KERN_ALERT "address %d\n",my_ptr);
	return 0;
}

ssize_t  obled_write (struct file *my_fp, const char __user *my_ptr, size_t mysize, loff_t *my_loff_t)
{
	
	disp_msg("my drv write");
	printk(KERN_ALERT "I'm in write\n");
	if(strcmp(my_ptr,"ON")==0)
	{
		gpio_set_value(GPIO_NUM,1);
	}
	else if(strcmp(my_ptr,"OFF")==0)
	{
		gpio_set_value(GPIO_NUM,0);
	}
	else
	{
		printk(KERN_ALERT "Driver ERROR",my_ptr);
	}
	return 0;
}

struct file_operations my_fops={
	.owner	 = THIS_MODULE,						
	.open	 = obled_open,					
	.release = obled_close,					
	.read	 = obled_read,					
	.write	 = obled_write
};



static int __init obled_init(void)
{
disp_msg("LED PROGRAM  HELLO ENTRY !!!!\n");
maj_number=register_chrdev(0,"MYDRIVER",&my_fops);
return 0;
}

static int __exit obled_exit(void)
{
disp_msg ("LED PROGRAM Bye !!!!\n");
unregister_chrdev(maj_number,"MYDRIVER");
return 0;
}

//EXPORT_SYMBOL(disp_msg);
//EXPORT_SYMBOL(printval);
module_init(obled_init);
module_exit(obled_exit);
MODULE_LICENSE("GPL");


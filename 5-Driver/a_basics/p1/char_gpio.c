#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
 
#define GPIO_NUMBER    60

// 56 - 32 = 24
 
static dev_t mydev;         	// Global variable for the mydev device number
static struct cdev c_dev;     	// Global variable for the character device structure
static struct class *cl;     	// Global variable for the device class

static int init_result;

/*********************************************************************************
 * Function:			gpio_open
 * Description:			Opens the Driver
 ********************************************************************************/
static int gpio_open( struct inode *inode, struct file *file )
{
	return 0;
}

/*********************************************************************************
 * Function:			gpio_close
 * Description:			Releasse the Driver
 ********************************************************************************/
static int gpio_close( struct inode *inode, struct file *file )
{
	return 0;
}

/*********************************************************************************
 * Function:			gpio_read
 * Description: 		Read from Driver
 ********************************************************************************/
 
static ssize_t gpio_read( struct file* F, char *buf, size_t count, loff_t *f_pos )
{
	unsigned char temp = gpio_get_value(GPIO_NUMBER);

	gpio_set_value(GPIO_NUMBER, 0);

	if(copy_to_user( buf, &temp, 1 ) )
	{
		return -EFAULT;
	}
	return count;
}

/*********************************************************************************
 * Function:			gpio_write
 * Description:			Writes to Driver
 ********************************************************************************/
static ssize_t gpio_write( struct file* F, const char *buf, size_t count, loff_t *f_pos )
{
	char temp;
#if 1
	if (copy_from_user(&temp, buf, count))
	{
		return -EFAULT;
	}

	printk(KERN_INFO "Executing WRITE.\n");

	switch(temp)
	{
		case '0':
			printk("Exeuting Off \n");
			gpio_set_value(GPIO_NUMBER, 0);
		break;

		case '1':
			printk("Exeuting On \n");
			gpio_set_value(GPIO_NUMBER, 1);
		break;

		default:
			printk("Wrong option.\n");
		break;
	}
	return count;
#endif
}


/*********************************************************************************
 * Function:			char_dev_fops
 * Description:			File operations
 ********************************************************************************/
static struct file_operations char_dev_fops =
{
	.owner        = THIS_MODULE,
	.open         = gpio_open,
	.read         = gpio_read,
	.write        = gpio_write,
	.release      = gpio_close,
};

/*********************************************************************************
 * Function:			init_gpio
 * Description:			Initialize the Driver
 * 
 * List of Function:	alloc_chrdev_region();
 * 						cdev_alloc();
 * 						cdev_init();
 * 						cdev_add();			
 ********************************************************************************/
 
static int init_gpio(void)
{

	init_result = alloc_chrdev_region( &mydev, 0, 1, "gpio_drv" );

	if( 0 > init_result )
	{
		printk( KERN_ALERT "Device Registration failed\n" );
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(mydev));

	cdev_init( &c_dev, &char_dev_fops );
	if(cdev_add( &c_dev, mydev, 1 ) == -1)
	{
		printk( KERN_ALERT "Device addition failed\n" );
		device_destroy( cl, mydev );
		class_destroy( cl );
		unregister_chrdev_region( mydev, 1 );
		return -1;
	}


	if ( (cl = class_create( THIS_MODULE, "gpiodrv" ) ) == NULL )
	{
		printk( KERN_ALERT "Class creation failed\n" );
		unregister_chrdev_region( mydev, 1 );
		return -1;
	}

	if( device_create( cl, NULL, mydev, NULL, "gpio_drv%d", 0) == NULL )
	{
		printk( KERN_ALERT "Device creation failed\n" );
		class_destroy(cl);
		unregister_chrdev_region( mydev, 1 );
		return -1;
	}

	  int result = 0;
	   printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");
	   // Is the GPIO a valid GPIO number (e.g., the BBB has 4x32 but not all available)
	   if (!gpio_is_valid(GPIO_NUMBER)){
	      printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
	      return -ENODEV;
	   }
	   // Going to set up the LED. It is a GPIO in output mode and will be on by default
	  bool ledOn = true;
	   gpio_request(GPIO_NUMBER, "sysfs");          // gpioLED is hardcoded to 49, request it
	   gpio_direction_output(GPIO_NUMBER, ledOn);   // Set the gpio to be in output mode and on
	   gpio_set_value(GPIO_NUMBER, 0);          // Not required as set by line above (here for reference)
	   gpio_export(GPIO_NUMBER, false);             // Causes gpio49 to appear in /sys/class/gpio

	return 0;
}

/*********************************************************************************
 * Function:			cleanup_gpio
 * Description:			Exit from Driver
 ********************************************************************************/
void cleanup_gpio(void)
{
	cdev_del( &c_dev );
	device_destroy( cl, mydev );
	class_destroy( cl );
	unregister_chrdev_region( mydev, 1 );
	printk(KERN_ALERT "Device unregistered\n");
}

module_init(init_gpio);
module_exit(cleanup_gpio);

MODULE_AUTHOR("TARUN");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Gpio Demo");

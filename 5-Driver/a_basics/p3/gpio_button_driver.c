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
#include <linux/interrupt.h>
#include <linux/irq.h>

#define DRIVER_NAME "my_button_device"
static unsigned int gpio_button_number = 115;
static unsigned int gpio_led_number = 49;

static dev_t first;          // Global variable for the first device number
static struct cdev c_dev;    // Global variable for the character device structure
static struct class *cl;     // Global variable for the device class

static bool ledOn = 0;
static unsigned int numberPresses = 0;

static irq_handler_t  ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

static int init_result;

static ssize_t gpio_read( struct file* F, char *buf, size_t count, loff_t *f_pos )
{
	unsigned char temp = gpio_get_value(gpio_led_number);

	if( copy_to_user( buf, &temp, 1 ) )
	{
		return -EFAULT;
	}
	return count;
}


static ssize_t gpio_write( struct file* F, const char *buf, size_t count, loff_t *f_pos )
{
	char temp;

	if (copy_from_user(&temp, buf, count))
	{
		return -EFAULT;
	}

	printk(KERN_INFO "Executing WRITE.\n");

	switch(temp)
	{
		case '0':
			gpio_set_value(gpio_led_number, 0);
			break;

		case '1':
			gpio_set_value(gpio_led_number, 1);
			break;

		default:
			printk("Wrong option.\n");
			break;
	}

	return count;
}

static int gpio_open( struct inode *inode, struct file *file )
{
	return 0;
}

static int gpio_close( struct inode *inode, struct file *file )
{
	return 0;
}

static struct file_operations FileOps =
{
	.owner        = THIS_MODULE,
	.open         = gpio_open,
	.read         = gpio_read,
	.write        = gpio_write,
	.release      = gpio_close,
};


static int led_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;

	printk("led Probe Called\n");

	of_property_read_u32(np, "ledno", &gpio_led_number);
	printk("GPIO NUMBER : %d\n", gpio_led_number);

#if 1
	// Going to set up the LED. It is a GPIO in output mode and will be on by default
	bool ledOn = true;
	gpio_request(gpio_led_number, "sysfs");          // gpioLED is hardcoded to 49, request it
	gpio_direction_output(gpio_led_number, ledOn);   // Set the gpio to be in output mode and on
	gpio_set_value(gpio_led_number, 0);          // Not required as set by line above (here for reference)
	gpio_export(gpio_led_number, false);             // Causes gpio49 to appear in /sys/class/gpio
#endif
	return 0;
}

static int led_remove(struct platform_device *pdev)
{

	gpio_free(gpio_led_number);
	return 0;
}

static const struct of_device_id gpio_led_dt[] = {
	    { .compatible = "my-led-driver", },
		    { }
};

MODULE_DEVICE_TABLE(of, gpio_led_dt);
static struct platform_driver led_pldriver = {
	.probe          = led_probe,
	.remove         = led_remove,
	.driver = {
		.name  = DRIVER_NAME,
		.of_match_table = of_match_ptr(gpio_led_dt),
	},
};


static int button_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int result =0;

	printk("button Probe Called\n");

	of_property_read_u32(np, "buttonno", &gpio_button_number);
	printk("GPIO NUMBER : %d\n", gpio_button_number);

	unsigned int irq /*=  platform_get_irq(pdev, 0)*/;
	unsigned int hw_irq;

	gpio_request_one(gpio_button_number, GPIOF_DIR_IN, "button");

	irq = gpio_to_irq(gpio_button_number);

	struct irq_data *irq_data = irq_get_irq_data(irq);

	hw_irq = irqd_to_hwirq(irq_data); 

	printk(" irq number is : %d\n", irq);
	printk(" hw irq number is : %d\n", hw_irq);

	printk(" Mapped GPIO %d to IRQ %d\n", gpio_button_number, irq);

	// This next call requests an interrupt line
	result = request_irq(irq,             // The interrupt number requested
	                     (irq_handler_t)ebbgpio_irq_handler, // The pointer to the handler function below
	                     IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,   // Interrupt on rising edge (button press, not release)
	                     "ebb_gpio_handler",    // Used in /proc/interrupts to identify the owner
	                     NULL);                 // The *dev_id for shared interrupt lines, NULL is okay

	printk("GPIO_TEST: The interrupt request result is: %d\n", result);

#if 1
	gpio_request(gpio_button_number, "sysfs");       // Set up the gpioButton
	gpio_direction_input(gpio_button_number);        // Set the button GPIO to be an input
	gpio_set_debounce(gpio_button_number, 200);      // Debounce the button with a delay of 200ms
	gpio_export(gpio_button_number, false);          // Causes gpio115 to appear in /sys/class/gpio
#endif

#if 1
	// Going to set up the LED. It is a GPIO in output mode and will be on by default
	bool ledOn = true;
	gpio_request(gpio_led_number, "sysfs");          // gpioLED is hardcoded to 49, request it
	gpio_direction_output(gpio_led_number, ledOn);   // Set the gpio to be in output mode and on
	gpio_set_value(gpio_led_number, 0);          // Not required as set by line above (here for reference)
	gpio_export(gpio_led_number, false);             // Causes gpio49 to appear in /sys/class/gpio
#endif
	return 0;
}

static int button_remove(struct platform_device* pdev)
{
	struct device_node *np = pdev->dev.of_node;

	free_irq(pdev, 0);
	gpio_free(gpio_button_number);

	printk(" Button Device removed");
}

static const struct of_device_id gpio_button_dt[] = {
	    { .compatible = "my-button-driver", },
		    { }
};

MODULE_DEVICE_TABLE(of, gpio_button_dt);
static struct platform_driver button_pldriver = {
	.probe          = button_probe,
	.remove         = button_remove,
	.driver = {
		.name  = DRIVER_NAME,
		.of_match_table = of_match_ptr(gpio_button_dt),
	},
};

static irq_handler_t ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledOn = !ledOn;                          // Invert the LED state on each button press
   gpio_set_value(gpio_led_number, ledOn);          // Set the physical LED accordingly
   printk(KERN_INFO "GPIO_TEST: Interrupt! (button state is %d)\n", gpio_get_value(gpio_button_number));
   numberPresses++;                         // Global counter, will be outputted when the module is unloaded
   return (irq_handler_t) IRQ_HANDLED;      // Announce that the IRQ has been handled correctly
}

static int init_mydrv(void)
{
	platform_driver_register(&button_pldriver);
	printk(KERN_ALERT "\n Welcome to sample Platform driver.... \n");

	init_result = alloc_chrdev_region( &first, 0, 1, "gpio_drv" );

	if( 0 > init_result )
	{
		printk( KERN_ALERT "Device Registration failed\n" );
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(first));

	if ( (cl = class_create( THIS_MODULE, "gpiodrv" ) ) == NULL )
	{
		printk( KERN_ALERT "Class creation failed\n" );
		unregister_chrdev_region( first, 1 );
		return -1;
	}

	if( device_create( cl, NULL, first, NULL, "gpio_drv%d", 0) == NULL )
	{
		printk( KERN_ALERT "Device creation failed\n" );
		class_destroy(cl);
		unregister_chrdev_region( first, 1 );
		return -1;
	}

	cdev_init( &c_dev, &FileOps );

	if( cdev_add( &c_dev, first, 1 ) == -1)
	{
		printk( KERN_ALERT "Device addition failed\n" );
		device_destroy( cl, first );
		class_destroy( cl );
		unregister_chrdev_region( first, 1 );
		return -1;
	}

	/* Registering with Kernel */

	//platform_driver_register(&led_pldriver);


	return 0;


}

void cleanup_mydrv(void)
{
	platform_driver_unregister(&button_pldriver);
	printk(KERN_ALERT "\n Thanks....Exiting sample Platform driver... \n");

	cdev_del( &c_dev );
	device_destroy( cl, first );
	class_destroy( cl );
	unregister_chrdev_region( first, 1 );

	printk(KERN_ALERT "Device unregistered\n");

	/* Unregistering from Kernel */

	//platform_driver_unregister(&led_pldriver);

	return;
}

module_init(init_mydrv);
module_exit(cleanup_mydrv);

MODULE_AUTHOR("VPK");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BeagleBone Black GPIO Driver");

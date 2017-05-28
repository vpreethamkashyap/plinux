#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#define SHARED_IRQ 16
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;

module_param (irq, int, S_IRUGO);

/*********************************************************************************
 * Function:			my_interrupt
 * Description:		 
 ********************************************************************************/
static irqreturn_t my_interrupt (int irq, void *dev_id)
{
	irq_counter++;
	printk (KERN_INFO "In the ISR: counter = %d\n", irq_counter);
	return IRQ_NONE; // we return IRQ_NONE because we are just observing
}

/*********************************************************************************
 * Function:			my_init
 * Description:		 
 ********************************************************************************/
static int __init my_init (void)
{
	if (request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id))
		return -1;
	
	printk (KERN_INFO "Successfully loading ISR handler\n");
	return 0;
}

/*********************************************************************************
 * Function:			my_exit
 * Description:		 
 ********************************************************************************/
static void __exit my_exit (void)
{
	synchronize_irq (irq);
	free_irq (irq, &my_dev_id);
	printk (KERN_INFO "Successfully unloading \n");
}

module_init (my_init);
module_exit (my_exit);
MODULE_AUTHOR ("Team veda");
MODULE_DESCRIPTION ("Interrupt Handler Test");
MODULE_LICENSE ("GPL");

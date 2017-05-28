#include <linux/module.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <linux/slab.h>

static struct kt_data
{
    struct hrtimer timer;
    ktime_t period;
} *data;

/*********************************************************************************
 * Function:			ktfun
 * Description:		 
 ********************************************************************************/
 
static enum hrtimer_restart ktfun (struct hrtimer *var)
{
	ktime_t now = var->base->get_time();
	printk	ktime_t now = var->base->get_time ();
	printk (KERN_INFO "timer running at jiffies=%ld\n", jiffies);
	hrtimer_forward (var, now, data->period);
	//  return HRTIMER_NORESTART;
	return HRTIMER_RESTART;
 (KERN_INFO "timer running at jiffies=%ld\n", jiffies);
	hrtimer_forward (var, now, data->period);
	//  return HRTIMER_NORESTART;
	return HRTIMER_RESTART;
}

/*********************************************************************************
 * Function:			my_init
 * Description:		 
 ********************************************************************************/
static int __init my_init (void)
{
	data = kmalloc (sizeof (*data), GFP_KERNEL);
	data->period = ktime_set (1, 0);    /* short period, 1 second  */
	hrtimer_init (&data->timer, CLOCK_REALTIME, HRTIMER_MODE_REL);
	data->timer.function = ktfun;
	hrtimer_start (&data->timer, data->period, HRTIMER_MODE_REL);
	return 0;
}

/*********************************************************************************
 * Function:			my_exit
 * Description:		 
 ********************************************************************************/
static void __exit my_exit (void)
{
	hrtimer_cancel (&data->timer);
	kfree (data);
}

module_init (my_init);
module_exit (my_exit);
MODULE_LICENSE ("GPL");

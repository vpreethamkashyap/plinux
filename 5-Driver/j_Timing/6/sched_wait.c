#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

int delay = HZ;
module_param(delay, int, 0);

static struct task_struct *thread_st;

static int thread_fn(void *unused)
{
	unsigned long j1, j2;
	
	while (!kthread_should_stop()) 
	{
		j1 = jiffies;
		j2 = j1 + delay;
		while (time_before(jiffies, j2))
			schedule();
		j2 = jiffies;
		printk("Jit Start = %lu\t Jit End = %lu\n", j1, j2);
	}
	printk(KERN_INFO "Thread Stopping\n");
	do_exit(0);
}


static int __init init_thread(void)
{
	printk(KERN_INFO "Creating Thread\n");
	thread_st = kthread_run(thread_fn, NULL, "mythread");

	return 0;
}

static void __exit cleanup_thread(void)
{
	int ret;
	printk("Cleaning Up\n");
	ret = kthread_stop(thread_st);
	if(!ret)
		printk(KERN_INFO "Thread stopped");
}

module_init(init_thread);
module_exit(cleanup_thread);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tarun");
MODULE_DESCRIPTION("Thread Creation Demo");


/***********************************************************************
	tsp@tsp-Inspiron-5558:~/tlinux/mylinux/Tools/6-Driver/j_Timing/6$ sudo insmod sched_wait.ko
	tsp@tsp-Inspiron-5558:~/tlinux/mylinux/Tools/6-Driver/j_Timing/6$ dmesg
	[10665.620784] Jit Start = 4297557739	 Jit End = 4297558739
	[10665.940757] Jit Start = 4297558569	 Jit End = 4297558819
	[10666.940720] Jit Start = 4297558819	 Jit End = 4297559069
	[10667.940683] Jit Start = 4297559069	 Jit End = 4297559319
	[10668.940649] Jit Start = 4297559319	 Jit End = 4297559569
	[10669.620642] Jit Start = 4297558739	 Jit End = 4297559739
	[10669.940611] Jit Start = 4297559569	 Jit End = 4297559819
	[10670.940578] Jit Start = 4297559819	 Jit End = 4297560069
	[10671.940534] Jit Start = 4297560069	 Jit End = 4297560319
	[10672.940498] Jit Start = 4297560319	 Jit End = 4297560569


 * */

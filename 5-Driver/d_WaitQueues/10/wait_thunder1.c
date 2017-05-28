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
#include <linux/semaphore.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev *c_dev;
static struct class *cl;

static struct task_struct *thread_st;
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;
static char c;
static struct semaphore sem;
static int a[10];
static wait_queue_t wq_entry[10];

static int thread_fn(void *data)
{
	allow_signal(SIGKILL);
	init_wait(&wq_entry[(*(int *)data)]);
	if (data == NULL)
	{
		printk("Data is NULL\n");
		do_exit(-1);
	}
	printk("Data is %d\n", *(int *)data);
	
	if (down_interruptible(&sem))
		return -ERESTARTSYS;

	while (flag != 'y') 
	{
		up(&sem);
		printk("Thread %d going to Sleep\n", *(int *)data);
		prepare_to_wait_exclusive(&wq, &wq_entry[*(int *)data],TASK_INTERRUPTIBLE); 
		if (flag != 'y')
			schedule();
		finish_wait(&wq, &wq_entry[*(int *)data]);
		if (signal_pending(current))
			return -ERESTARTSYS;

		printk("Thread %d Woken Up\n", *(int *)data);
		if (down_interruptible(&sem))
			return -ERESTARTSYS;
	}
	up(&sem);
	printk("Data read by %d thread is %c\n", *(int *)data, c);
	ssleep(1);
	if (down_interruptible(&sem))
		return -ERESTARTSYS;
	flag = 'n';
	up(&sem);
	do_exit(0);
}

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) 
{
	printk(KERN_INFO "Inside write \n");
	if (copy_from_user(&flag, buff, 1)) 
	{
		printk("copy_from_user failed\n");
		return -EFAULT;
	}
	wake_up_interruptible(&wq);
	return count;
}       

int open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Inside open \n");
	return 0;
}


int release(struct inode *inode, struct file *filp) 
{
	printk (KERN_INFO "Inside close \n");
	return 0;
}


struct file_operations pra_fops = {
	write:        write,
	open:         open,
	release:    release
};


static int __init wqt_init(void)
{
	int i = 0;
	char name[20];

	sema_init(&sem, 1);
	
	for (i = 0; i < 10; i++) 
	{
		a[i] = i;
		sprintf(name, "mythread%d", a[i]);
		printk(KERN_INFO "Creating Thread- %d\n", a[i]);
		thread_st = kthread_run(thread_fn, &a[i], name);
	}
	if (alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "SCD") < 0)
	{
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(dev));

	if (!(c_dev = cdev_alloc ()))
	{
		printk (KERN_ERR "cdev_alloc() failed\n");
		return -1;
 	}

	cdev_init(c_dev, &pra_fops);

	if (cdev_add(c_dev, dev, MINOR_CNT) == -1)
	{
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}

	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		cdev_del(c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}
	if (IS_ERR(device_create(cl, NULL, dev, NULL, "exe_wait_thunder%d", 0)))
	{       
		class_destroy(cl);
		cdev_del(c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}

	return 0;
}

static void __exit wqt_exit(void)
{
	printk("Cleaning Up\n");
	printk(KERN_INFO " Inside cleanup_module\n");
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(wqt_init);
module_exit(wqt_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tarun");
MODULE_DESCRIPTION("Wait Queue Thunder Demo");

/*
 * tsp@tsp-Inspiron-5558:~/tlinux/mylinux/Tools/6-Driver/d_WaitQueues/10$ sudo insmod wait_thunder1.ko
 *
 * demsg
 *
[45660.062108] Creating Thread- 0
[45660.064186] Creating Thread- 1
[45660.064189] Data is 0
[45660.064195] Thread 0 going to Sleep
[45660.064243] Creating Thread- 2
[45660.064253] Data is 1
[45660.064256] Thread 1 going to Sleep
[45660.064278] Creating Thread- 3
[45660.064285] Data is 2
[45660.064288] Thread 2 going to Sleep
[45660.064919] Creating Thread- 4
[45660.064931] Data is 3
[45660.064934] Thread 3 going to Sleep
[45660.065238] Creating Thread- 5
[45660.065242] Data is 4
[45660.065246] Thread 4 going to Sleep
[45660.065348] Creating Thread- 6
[45660.065354] Data is 5
[45660.065362] Thread 5 going to Sleep
[45660.065385] Creating Thread- 7
[45660.065389] Data is 6
[45660.065392] Thread 6 going to Sleep
[45660.065492] Creating Thread- 8
[45660.065496] Data is 7
[45660.065499] Thread 7 going to Sleep
[45660.065966] Creating Thread- 9
[45660.065968] Data is 8
[45660.065971] Thread 8 going to Sleep
[45660.066012] Data is 9
[45660.066014] Major Nr: 243
[45660.066015] Thread 9 going to Sleep

###################################################################

tsp@tsp-Inspiron-5558:~/tlinux/mylinux/Tools/6-Driver/d_WaitQueues/app$ sudo ./a.out /dev/exe_wait_thunder0
[sudo] password for tsp:

 Program name  : ./a.out
1st arg  : /dev/exe_wait_thunder0
1: Open
2: Read
3: Write
4: Close
5: Ioctl
0: Exit
Enter choice: 1
1: Open
2: Read
3: Write
4: Close
5: Ioctl
0: Exit
Enter choice: 3
Enter your string: y
Wrote 1 bytes from 0x7ffc7b814c50
1: Open
2: Read
3: Write
4: Close
5: Ioctl
0: Exit
Enter choice:


###################################################################

[45757.931226] Inside open
[45762.421110] Inside write
[45762.421341] Thread 0 Woken Up
[45762.421345] Data read by 0 thread is


 */




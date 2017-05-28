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

static struct task_struct *thread_st[10];
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;
static char c;
static struct semaphore sem;
static int a[10];

static int thread_fn(void *data)
{
	allow_signal(SIGKILL);
	if (data == NULL)
	{
		printk("Data is NULL\n");
		return -1;
	}
	printk("Data is %d\n", *(int *)data);

	// if no thread has taken the semaphore then it will get execute otherwise other threads has to wait untill it is released
	if (down_interruptible(&sem))
		return -ERESTARTSYS;

	while (flag != 'y')
	{
		up(&sem);
		printk("Thread %d going to Sleep\n", *(int *)data);
		if (wait_event_interruptible(wq, flag == 'y'))
			return -ERESTARTSYS;

		printk("Thread %d Woken Up\n", *(int *)data);
		if (down_interruptible(&sem))
			return -ERESTARTSYS;
	}
	ssleep(1);
	flag = 'n';
	up(&sem);

	printk("Data read by %d thread is %c\n", *(int *)data, c);
	thread_st[*(int *)data] = NULL;
	do_exit(0);
}

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) {

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
		thread_st[i] = kthread_run(thread_fn, &a[i], name);
	}
	printk("Waking Up Thread\n");
	flag = 1;
	wake_up_interruptible(&wq);

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
	if (IS_ERR(device_create(cl, NULL, dev, NULL, "wait_thunder%d", 0)))
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
	int i;
	printk("Cleaning Up\n");

	for (i = 0; i < 10; i++) 
	{
		if (thread_st[i] != NULL)
			kthread_stop(thread_st[i]);
	}
	printk(KERN_INFO " Inside cleanup_module\n");
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(wqt_init);
module_exit(wqt_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pradeep");
MODULE_DESCRIPTION("Wait Queue Thunder Demo");

/****************************************************************************************************
 [43035.632508] Creating Thread- 0
[43035.632543] Creating Thread- 1
[43035.632544] Data is 0
[43035.632546] Thread 0 going to Sleep
[43035.632632] Creating Thread- 2
[43035.632634] Data is 1
[43035.632635] Thread 1 going to Sleep
[43035.632684] Creating Thread- 3
[43035.632685] Data is 2
[43035.632686] Thread 2 going to Sleep
[43035.632699] Creating Thread- 4
[43035.632700] Data is 3
[43035.632701] Thread 3 going to Sleep
[43035.632715] Creating Thread- 5
[43035.632717] Data is 4
[43035.632718] Thread 4 going to Sleep
[43035.632731] Creating Thread- 6
[43035.632732] Data is 5
[43035.632733] Thread 5 going to Sleep
[43035.632792] Creating Thread- 7
[43035.632793] Data is 6
[43035.632794] Thread 6 going to Sleep
[43035.632810] Creating Thread- 8
[43035.632811] Data is 7
[43035.632812] Thread 7 going to Sleep
[43035.633279] Creating Thread- 9
[43035.633299] Waking Up Thread
[43035.633300] Data is 9
[43035.633302] Thread 9 going to Sleep
[43035.633308] Major Nr: 243
[43035.634267] Data is 8
[43035.634270] Thread 8 going to Sleep
[43126.887285] Inside open


 *********************
 Once user writes y to driver then all threads will wake up
 *********************
[44151.843341] Inside write
[44151.843359] Thread 8 Woken Up
[44151.843360] Thread 5 Woken Up
[44151.843384] Thread 7 Woken Up
[44151.843388] Thread 0 Woken Up
[44151.843390] Thread 2 Woken Up
[44151.843393] Thread 3 Woken Up
[44151.843395] Thread 1 Woken Up
[44151.843397] Thread 6 Woken Up
[44151.843400] Thread 4 Woken Up
[44151.843402] Thread 9 Woken Up
[44152.844569] Data read by 5 thread is
[44152.844576] Thread 8 going to Sleep
[44152.844603] Thread 7 going to Sleep
[44152.844610] Thread 0 going to Sleep
[44152.844621] Thread 2 going to Sleep
[44152.844624] Thread 3 going to Sleep
[44152.844630] Thread 1 going to Sleep
[44152.844635] Thread 6 going to Sleep
[44152.844639] Thread 4 going to Sleep
[44152.844640] Thread 9 going to Sleep
 *********************
 * */

/*
 tsp@tsp-Inspiron-5558:~/tlinux/mylinux/Tools/6-Driver/d_WaitQueues/app$ sudo ./a.out /dev/wait_thunder0

 Program name  : ./a.out
1st arg  : /dev/wait_thunder0
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
Wrote 1 bytes from 0x7fff1bb80af0
1: Open
2: Read
3: Write
4: Close
5: Ioctl
0: Exit
Enter choice:

 * */


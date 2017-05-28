#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <malloc.h>
#include <string.h>
#include "../../../b_ioctl/2/app/ioctl_data.h"

#define NODE_NAME "/dev/ioctl_var"
#define MY_IOW(type,nr,size) _IOC(_IOC_WRITE,(type),(nr),size)
#define MY_IOR(type,nr,size) _IOC(_IOC_READ, (type),(nr),size)

int main ()
{
	int fd, ret_ioctl, i, lbuf;
	char *buffer;
	int MYIOC_X;

	// open the device node 
	fd = open (NODE_NAME, O_RDWR);
	if(fd<0)
	{
		printf ("unable to open the driver\n");
		return;
	}
	printf (" I opened the device node, file descriptor = %d\n", fd);

	// set the buffer size
	lbuf = 10;
	printf (" I am going to send back and forth a buffer of %d bytes\n", lbuf);

	// malloc the buffer 
	buffer = malloc (lbuf);

	// send the IOCTL and read the contents from the kernel 
	printf ("\n User Reading data from the kernel space:\n");

	MYIOC_X = (int)MY_IOR (VEDA_MAGIC, 1, lbuf);
	ret_ioctl = ioctl (fd, MYIOC_X, buffer);	
	printf ("\n Ret_ioctl from ioctl = %d \n\n", ret_ioctl);
	
	printf ("buffer in user-space is =\n ");	
	for (i = 0; i < lbuf; i++)
	{
		printf ("%c", buffer[i]);
	}		
	printf ("\n");

	//  clear it and send it back 
	memset (buffer, 'b', lbuf);

	printf ("\n User Sending data to the kernel:\n");
	MYIOC_X = (int)MY_IOW (VEDA_MAGIC, 1, lbuf);
	ret_ioctl = ioctl (fd, MYIOC_X, buffer);
	printf ("\n Ret_ioctl from ioctl = %d \n\n", ret_ioctl);
	
	printf ("\n User Reading data from the kernel space:\n");

	MYIOC_X = (int)MY_IOR (VEDA_MAGIC, 1, lbuf);
	ret_ioctl = ioctl (fd, MYIOC_X, buffer);	
	printf ("\n Ret_ioctl from ioctl = %d \n\n", ret_ioctl);
	
	
	printf ("Buffer in user-space is =\n   ");
	
	for (i = 0; i < lbuf; i++)
		printf ("%c", buffer[i]);
			
	printf ("\n");

	close (fd);
	exit (0);
}

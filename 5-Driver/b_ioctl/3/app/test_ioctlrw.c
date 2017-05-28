#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include "../../../b_ioctl/3/app/ioctl_data.h"

#define NODE_NAME "/dev/Ioctl_rw_node"

struct MY_data my_data;

/******************************************************************************************
 * Function Name: 	main
 * Description:			opens the node & read write the data
 * ****************************************************************************************/
int main (int argc, char *argv[])
{
	int fd, Ioctl_ret;
	int MY_IOCTL;
	
	//open the device node 
	fd = open (NODE_NAME, O_RDWR);
	if(fd < 0) 
	{
		printf("\n\nDevice could not be opened\n\n");
		return 1;
	}
	printf (" I opened the device node, file descriptor = %d\n", fd);

  // retrieve the original values; 
	MY_IOCTL = (int)_IOR (VEDA_MAGIC, 1, struct MY_data);
	Ioctl_ret = ioctl (fd, MY_IOCTL, &my_data);
	printf ("\n Response from ioctl reading = %d \n\n", Ioctl_ret);
	printf(" my_data.i = %d\n    my_data.x = %ld\n    my_data.s = %s\n",my_data.i, my_data.x, my_data.s);

	// fill up the data structure 
	strcpy (my_data.s, "a string");
	my_data.i = 10;
	my_data.x = 800;
	printf ("\n Sending from user-space:\n");
	printf("my_data.i = %d\n    my_data.x = %ld\n    my_data.s = %s\n",my_data.i, my_data.x, my_data.s);

	// send to the device 
	MY_IOCTL = (int)_IOW (VEDA_MAGIC, 1, struct MY_data);
	Ioctl_ret = ioctl (fd, MY_IOCTL, &my_data);
	printf ("\n Response from writing ioctl = %d \n\n", Ioctl_ret);

	// read device and see if it got through 
	MY_IOCTL = (int)_IOR (VEDA_MAGIC, 1, struct MY_data);
	Ioctl_ret = ioctl (fd, MY_IOCTL, &my_data);
	printf ("\n Response After updating from ioctl reading = %d \n\n", Ioctl_ret);
	printf ("my_data.i = %d\n    my_data.x = %ld\n    my_data.s = %s\n",my_data.i, my_data.x, my_data.s);
	close (fd);
	exit (0);

}

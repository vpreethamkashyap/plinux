#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define CHAR_DEV_NAME 		"/dev/async_poll_drv"

int main()
{
	int fd, i;
	char my_message[22];
	unsigned long size;

	strcpy(my_message, "Linux Solutions");

	printf("[%d] - Opening device async_chr_drv\n", getpid() );
	fd = open(CHAR_DEV_NAME, O_RDWR );
	if( fd < 0 ) 
	{
		printf("Device could not be opened\n");
		return 1;
	}	
	printf("Device opened with ID [%d]\n", fd);
	
	//ioctl(fd, CHAR_GET_SIZE, &size);
	printf("Size of the device = %d\n", size);
	printf("Writing [%s]\n", my_message );
	
	// write the contents of my buffer into the device 
	size = (unsigned long)write( fd, my_message, strlen(my_message));
	printf("Bytes written %d\n", size);
	bzero(my_message, 20 );
	read(fd, my_message, 20 );
	printf("Written [%s] \n", my_message);	
	close(fd);	
	exit(0);
}



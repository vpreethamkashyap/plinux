#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../../../b_ioctl/1/app/ioctl_const.h"

#define CHAR_DEV_NAME 		"/dev/Basic_ioctl"

int main()
{
	int fd, i;
	char c;
	char my_buf[4000];	
	unsigned int size;
		
	printf("[%d] - Opening device Basic_ioctl\n", getpid() );
	
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if( fd < 0 ) 
	{
		printf("\n\nDevice could not be opened\n\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);	

	if(ioctl( fd, IOCTL_GET_SIZE, &size ) < 0)
	{
		printf("ioctl failed\n");
		return;
	}
	
	printf("Present size of the buffer is %d\n", size);	
	size = 4096;
	printf("Setting size of buffer to 4096\n");

	if( ioctl( fd, IOCTL_SET_SIZE, &size ) < 0 )
	{
		printf("ioctl failed\n");
		return;
	}
	
	if(ioctl( fd, IOCTL_GET_SIZE, &size ) < 0)
	{
		printf("ioctl failed\n");
		return;
	}
	printf("New size of the buffer is %d\n", size);		
	printf("lets fill the buffer with character = \n");
	
	c = 'C';
	if(ioctl(fd, IOCTL_FILL_CHAR, &c) < 0)
	{
		printf("ioctl failed\n");
		return;
	}
	
	printf("lets read the buffer\n");
	read( fd, my_buf, 70 );
	printf("New contents\n %s\n", my_buf);	
	close(fd);	
	exit(0);
}



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define CHAR_DEV_NAME "/dev/char_driver_dynamic"

int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[12]="Hello world";
	char str[12];	
	
	printf("You are going to test dynamic char driver\n");
		
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if(fd<0)
	{
		printf("failed acquiring file descriptor return status %d\n",fd);
		return;
	}

	ret = write( fd, my_buf, 12 );
	printf("Write the contents of my buffer into the device %d \n",ret);

	ret = read(fd,str,12);
	printf("Read the contents of my buffer from device %d \n",ret);
	
	printf(" %s \n",str);
	
	if(ret<0)
		printf("read operation failed with return status %d\n",ret);
		
	close(fd);
}
	

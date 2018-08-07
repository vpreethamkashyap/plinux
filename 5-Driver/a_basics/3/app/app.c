#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define CHAR_DEV_NAME "/dev/gpio_drv0"

int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[1]="1";
	char str[1];	
		char str2[1];
	
	printf("You are going to test dynamic char driver\n");
		
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if(fd<0)
	{
		printf("failed acquiring file descriptor return status %d\n",fd);
		return;
	}

	ret = write( fd, my_buf, 1 );
	printf("Write the contents of my buffer into the device %d \n",ret);

	ret = read(fd,str,1);
	printf("Read the contents of my buffer from device %d \n",ret);
	
	printf(" %s \n",str);
	

		ret = read(fd,str2,1);
	printf("Read the contents of my buffer from device %d \n",ret);
	
	printf(" %s \n",str2);

	if(ret<0)
		printf("read operation failed with return status %d\n",ret);
		
	close(fd);
}
	

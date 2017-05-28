#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define CHAR_DEV_NAME "/dev/char_driver_static"

int main()
{
	int fd;
	ssize_t ret;
	
	char my_buf[12]="Hello world";
	char str[12];	
	
	fd = open(CHAR_DEV_NAME, O_RDWR );
	if(fd<0)
	{
		printf("failed acquiring file descriptor return status %d\n",fd);
		return 0;
	}
	
	printf("\n");
	printf("Write the contents of my buffer into the device \n");
	
	ret = write( fd, my_buf, 12 );	
	if(ret<0)
	{
		printf("Write operation failed with return status %d\n",ret);
		close(fd);
		return;
	}
	else
	{
		printf("Write operation Successed with return status %d\n",ret);
	}
	
	ret = read(fd,str,12);
	if(ret<0)
	{
		printf("Read operation failed with return status %d\n",ret);
	}
	else
	{
		printf("Read operation Successed with return status %d\n",ret);
		printf("Read Data from Driver %s\n",str);
	}
	close(fd);
}
	

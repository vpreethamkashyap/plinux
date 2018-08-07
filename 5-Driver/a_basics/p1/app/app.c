#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define CHAR_DEV_NAME "/dev/gpio_drv0"

void main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[1]="1";
	char str[1];	
	char str2[1];
	
unsigned char gpio_stat = 0;

	printf("You are going to test dynamic char driver\n");
		
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if(fd<0)
	{
		printf("failed acquiring file descriptor return status %d\n",fd);
		return;
	}

	while(1) {
		printf("Enter H or L to change GPIO \n");
		scanf("%c",&gpio_stat);
		printf("You have pressed %c \n",gpio_stat);
		if(gpio_stat == 'H'){
			ret = write(fd, "1", 1);	
			printf("H \n");
			gpio_stat = 0;
		}
		else if(gpio_stat == 'L'){
			ret = write(fd, "0", 1);
			printf("L \n");
			gpio_stat = 0;
		}
		else if (gpio_stat == 'N') {
			gpio_stat = 0;
			break;
		}
	}

	ret = read(fd,str,1);
	printf("Read the contents of my buffer from device %d \n",ret);
	
	printf(" %s \n",str);


	if(ret<0)
		printf("read operation failed with return status %d\n",ret);
		
	close(fd);
}
	

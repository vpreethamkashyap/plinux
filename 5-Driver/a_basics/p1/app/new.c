#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[1]="1";
	char str[1];	
	char str2[1];
	
unsigned char gpio_stat = 0;


	while(1) {
		printf("Enter H or L to change GPIO \n");
		scanf("%c",&gpio_stat);
		printf("You have pressed %c \n",gpio_stat);
		if(gpio_stat == 'H'){
			//ret = write(fd, "1", 1);	
			printf("H \n");
			gpio_stat = 0;
		}
		else if(gpio_stat == 'L'){
			//ret = write(fd, "0", 0);
			printf("L \n");
			gpio_stat = 0;
		}
		else if (gpio_stat == 'N') {
			gpio_stat = 0;
			break;
		}
	}
}
	

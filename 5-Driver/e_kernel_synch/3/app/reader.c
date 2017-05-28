#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#define CHAR_DEV_NAME 		"/dev/kSynch_spin" 

void handler(int);

/*********************************************************************************
 * Function:			main
 * Description:		Opens the Driver
 ********************************************************************************/
int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[40];
	
	signal(SIGINT,handler);
	
	// open the device for read/write/lseek 
	printf("Opening device kSynch_spin with Pid [%d] - \n", getpid() );
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if(fd < 0)
	{
		printf("Could not open the device \n");
		return 0;
	}

again:
	if ((ret = read(fd, my_buf, 40)) < 0) 
	{
		// just an interrupted system call 
		if (errno == EINTR)
			goto again;     
	}
	printf("Read frm device %s \n", my_buf);
	close(fd);
	printf("Byeeeeeeeee \n");
}

void handler(int signum)
{
	printf("interrupt signal handled \n");
}
	

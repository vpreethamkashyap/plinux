#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define CHAR_DEV_NAME 		"/dev/kSynch_reentarnt"

int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[40];
	
	// fill my buffer with *'s 
	for(i=0; i<40; i++) 
	{
		my_buf[i] = 'T';
	}
	
	// open the device for read/write/lseek 
	printf("Opening device my driver with Pid [%d]\n", getpid() );
	fd = open( CHAR_DEV_NAME, O_RDWR );
	if(fd < 0)
	{
		printf("Unable to open the device\n");
		return 0;
	}
	
	printf("Write the contents of my buffer into the device \n");
	write( fd, my_buf, 40 );
	printf("Writing done\n");
	close(fd);
	printf("Byeeeeeeeee \n");
}
	

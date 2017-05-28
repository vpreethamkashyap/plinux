// App to write to device
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../../../f_block_io/1/app/char_device.h"

#define CHR_DEV_NAME "/dev/bio_chr_comp"

int main()
{
	int fd, i;
	char my_message[40];
	unsigned int size;

	strcpy(my_message, "Our Solutions : welcome to linux world");

	// open the device for read/write/lseek 
	printf("Opening device bio_chr_comp With PID [%d]\n", getpid() );
	fd = open( CHR_DEV_NAME, O_RDWR );
	if( fd < 0 ) 
	{
		printf("Device could not be opened\n");
		return 1;
	}	
	printf("Device opened with ID [%d]\n", fd);
	
	printf("Writing [%s]\n", my_message );
	size = write( fd, my_message, strlen(my_message) );
	printf("Bytes written %d\n", size);
	bzero( my_message, 20 );
	
	//read( fd, my_message, 20 );
	//printf("Written [%s] \n", my_message );	
	close(fd);	
	exit(0);
}



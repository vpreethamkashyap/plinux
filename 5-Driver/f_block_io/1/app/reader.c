
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
	int fd, i,ret;
	char my_buf[4000];
	
	bzero(my_buf, 4000);
		
	printf("Opening device bio_chr_comp With PID [%d]\n", getpid() );
	fd = open(CHR_DEV_NAME, O_RDONLY );
	perror("fd ");
	if( fd < 0 ) 
	{
		printf("Device could not be opened\n");
		return 1;
	}
	
	printf("Device opened with ID [%d]\n", fd);	
	
	// try to read 40bytes from this device 
	printf("Trying to read from the device\n\n");
	if ((ret = read( fd, my_buf, 40 )) < 0)
	{
		perror("\nRead ");
		exit(1);
	}
	printf("Read from char device [%s]\n", my_buf);
	//ioctl(fd,VEDA_FILL_ZERO);	
	close(fd);
}



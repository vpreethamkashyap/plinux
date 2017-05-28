#include <stdlib.h>
#include <math.h>
#include <stdio.h>  
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>   
#include <errno.h> 

int fd;

char *port = "/dev/sample_cdrv";

char TxBuffer[15] = "TARUN Aggarwal";
char RxBuffer[15];

char OpenSerialPort(void){

	int i=0,a=0;
	
	fd = open (port, O_RDWR | O_NONBLOCK);
	if(fd < 0) 
	{
		printf("Unable to open the Sample Port \n ");
	}
	else
	{
		printf("Able to open the Sample Port %s \n ",port);
		printf("Data Trasmission to driver \n ");
		write(fd,TxBuffer,strlen(TxBuffer));	
		a = read(fd,RxBuffer,10);
		if(a <0){
			printf("Read problem \n ");
		}
		printf("Data Reception from driver \n ");
		printf("Rx Buffer is %s \n",RxBuffer);	
	}     
	return 0;
}

/********************************************************************************************
			Main Starts Here
*********************************************************************************************/
int main(void)
{
   OpenSerialPort();	
}



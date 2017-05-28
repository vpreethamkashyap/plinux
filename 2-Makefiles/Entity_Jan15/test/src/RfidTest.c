#include "../inc/Header.h"

int RfidIndex = 0;
char RfidBuffer[64];

extern int RFID_fd;


/*************************************************************************************************************
**		function 	 		:	 	ReadRfidSensor
**		Definition   	:		Read the RFID Sensor
**
**************************************************************************************************************/

void ReadRfidSensor(void)
{
	int ReadBytes = 0;
	unsigned char byte;	
	RfidIndex = 0;
	
	OpenRFID_SerialPort();
	
	while(RfidIndex != 12)
	{		
		read(RFID_fd, &byte, 1);
		fcntl(RFID_fd,F_SETFL,0);
		if(byte != 0)
		{
			RfidBuffer[RfidIndex] = byte;	
			RfidIndex++;
		}		
	}
	printf("RFID Number \n");
	printf(" %s",RfidBuffer);
	printf("\n");
	close(RFID_fd);		
}


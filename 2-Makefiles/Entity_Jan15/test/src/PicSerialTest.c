#include"../inc/Header.h"

void TestPicBoard(void);
void TestProcSerialPorts(void);


extern int MDB_fd;
extern unsigned char HoldingReg[10];


/********************************************************************************************************
**
**	Function Name		: 	TestProcSerialPorts
** 	Description 		:	 	This function send the command to PIC Co-Processor Board
**
*********************************************************************************************************/

void TestProcSerialPorts(void)
{
	unsigned char MdbResponse = 0;
	
	//WELLTH_CHECK_TIMEOUT_SEC = WEIGHT_CHECK_TIMEOUT_SEC;
	HoldingReg[1] = 0x00;   
	HoldingReg[0] = 0x01;
	MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x0009, 0x000l, (unsigned char *)HoldingReg,1);
	if(MdbResponse!=0)
	{
		#if defined	SHOW_DISPLAY
			printf("Modbus Error Response %d \n",MdbResponse);
		#endif
	} 
	else
	{
		printf("Modbus Error Response %d \n",MdbResponse);
		HoldingReg[1] = 0x00;   
		HoldingReg[0] = 0x00;
		TestPicBoard();
	}	
}


/********************************************************************************************************
**
**	Function Name		: 	TestPicBoard
** 	Description 		:	 	This function tests the all serial ports of PIC Co-Processor Board
**
*********************************************************************************************************/


void TestPicBoard(void)
{
	unsigned int SerialPort;
	unsigned char SerialString[10];
	
	while(1)
	{
		printf("You can check the serial port 1,2,3,4,5,6 on PIC Co-Processor Board\n");
		printf("Press the Any Number from 1 to 6 to test the serial port\n");
		scanf("%d",SerialPort);
		printf("Pass the UART String\n");
		scanf("%s",&SerialString[1]);
		switch (SerialPort)
		{
			case 1:
				SerialString[0] = 0x31;
				printf("You are going to test UART 1\n");
				write(MDB_fd,SerialString,strlen(SerialString));	
			break;
			
			case 2:
				SerialString[0] = 0x32;
				printf("You are going to test UART 2\n");
				write(MDB_fd,SerialString,strlen(SerialString));	
			break;
			
			case 3:
				SerialString[0] = 0x33;
				printf("You are going to test UART 3\n");
				write(MDB_fd,SerialString,strlen(SerialString));
			break;			
			
			case 4:
				SerialString[0] = 0x34;
				printf("You are going to test UART 4\n");
				write(MDB_fd,SerialString,strlen(SerialString));
			break;
			
			case 5:
				SerialString[0] = 0x35;
				printf("You are going to test UART 5\n");
				write(MDB_fd,SerialString,strlen(SerialString));
			break;	
				
			case 6:
				SerialString[0] = 0x36;
				printf("You are going to test UART 6\n");
				write(MDB_fd,SerialString,strlen(SerialString));
			break;			
			
			default:
			break;	
		}		
	}
}

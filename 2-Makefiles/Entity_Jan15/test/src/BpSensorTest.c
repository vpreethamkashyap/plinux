#include"../inc/Header.h"

extern int BP_fd;
extern int LoopState;
extern char BpSerialPortName[64];

unsigned char LowBp=0;         
unsigned char HighBp=0;
unsigned char PulseRate=0;
unsigned char BpBuffer[60];
unsigned char BpStarResp[100];

unsigned int BpIndex = 0;
unsigned int BpStartIndex =0;


void AbortBP(void);
void SendStartCommand(void);
void SendGetCommand(void);
void SendInitCommand(void);
void ReadBPDirectTest(void);

int ReadBpResponse(void);
int ReadInitResponse(void);
int ReadStartResponse(void);


/*************************************************************************************************************
**		function 	 		:	 	ReadBPDirectTest
**		Definition   	:		Tests the BP without using any Co-Processor Board
**
**************************************************************************************************************/
int BpSwitch = 0;

void ReadBPDirectTest(void)
{
	switch(BpSwitch)
	{
		case 0:
			// open the serial port
			BP_fd = ArgOpenSerialPort(BpSerialPortName, 9600);
			sleep(.5);
			BpSwitch = BpSwitch +1;
		break;
		
		case 1:
			// this command intialize the BP Sensor
			SendInitCommand();
			BpSwitch = BpSwitch+1;
		break;

		case 2:			
			// Read the response from BP Init command
			if(ReadInitResponse())
			{
				BpSwitch = BpSwitch+1;
			}
		break;
		
		case 3:
			SendStartCommand();
			BpSwitch = BpSwitch+1;
		break;
		
		case 4:			
			if(ReadStartResponse())
			{
				BpSwitch = BpSwitch+1;
			}
		break;

		case 5:			
			SendGetCommand();					
			BpSwitch = BpSwitch+1;	
			printf("\n Get The values of BP \n\n");		
		break;	
	
		case 6:			
			if(ReadBpResponse())
			{
				BpSwitch = BpSwitch+1;
			}
		break;
		case 7:
			printf("\n\nNow closing Serial Port /dev/ttyUSB0 \n\n");
			close(BP_fd);
			CalculateBp();
			UpdateBp_SummaryFile();		
			UpdateBp_RawFile();
			UpdateBp_DataBase();
			BpSwitch = 0;
			LoopState = DO_LOOP_TEST;	
		break;
		default:
		break;
	}
}

/*************************************************************************************************************
**		function 	 		:	 	SendInitCommand
**		Definition   	:		Initialize the Pressure
**
**************************************************************************************************************/
void SendInitCommand(void)
{	
	int WrCount;
	unsigned char Set_Init[5] = {0x3A, 0x17, 0x96, 0x00, 0x19};
	
	WrCount = write(BP_fd, &Set_Init, sizeof(Set_Init));
	fcntl(BP_fd,F_SETFL,O_FSYNC);

	if (WrCount < 0)
	{
			fputs("write() of 1 bytes failed!\n", stderr);
	}
	else
	{
			printf("SendInitCommand\n");
	}
}

/*************************************************************************************************************
**		function 	 		:	 	ReadInitResponse
**		Definition   	:		Read response from Init Command
**
**************************************************************************************************************/
int ReadInitResponse(void)
{	
	unsigned char ReadByte;
	
	read(BP_fd, &ReadByte, 1);
	fcntl(BP_fd,F_SETFL,0);
	if(ReadByte == 0x4B)
	{
		printf("Init Response has come \n");
		return 1;		
	}
	return 0;
}

/*************************************************************************************************************
**		function 	 		:	 	SendStartCommand
**		Definition   	:		Start The BP test
**
**************************************************************************************************************/

void SendStartCommand(void)
{
	int ret;
	unsigned char SendStartCommand[3]={0x3A, 0x20, 0xA6};
				
	ret = write(BP_fd, &SendStartCommand, sizeof(SendStartCommand));
  fcntl(BP_fd,F_SETFL,O_FSYNC);  

	if (ret < 0)
	{
		fputs("write() of 1 bytes failed!\n", stderr);
	}
	else
	{
		printf("SendStartCommand\n");		
	}
	memset(BpStarResp, 0, sizeof(BpStarResp));
}

/*************************************************************************************************************
**		function 	 		:	 	ReadSendStartCommandResponse
**		Definition   	:		Get the Bp Response of start command
**
**************************************************************************************************************/
int ReadStartResponse(void)
{
	int k = 0;	
	unsigned char byte;
	
	read(BP_fd, &byte, 1);
	fcntl(BP_fd,F_SETFL,0);
	if(byte != 0x00)
	{
		BpStarResp[BpStartIndex] = byte;						
		if(BpStarResp[BpStartIndex] == 0x4B)
		{
			read(BP_fd, &byte, 1);
			BpStarResp[BpStartIndex+1] = byte;
			for(k=0;k<9;k++)
			{
				printf("the bp data %x\n", BpStarResp[k]);
			}
			printf("module completed the bp \n");
			return 1;
		}
	}
	return 0;
}

/*************************************************************************************************************
**		function 	 		:	 	SendGetCommand
**		Definition   	:		Read the BP Response
**
**************************************************************************************************************/

void SendGetCommand(void) 
{
	int bp;	
	unsigned char SendGetCommand[5] = {0x3A, 0x79, 0x03, 0x00, 0x4A};

	bp = write(BP_fd, &SendGetCommand, sizeof(SendGetCommand));
  fcntl(BP_fd,F_SETFL,O_FSYNC);
	BpIndex = 0;
	if (bp < 0)
	{
		fputs("write() of 1 bytes failed!\n", stderr);
	}
	else
	{
		printf("SendGetCommand\n");
    memset(BpBuffer, 0, sizeof(BpBuffer));
  }
}

/*************************************************************************************************************
**		function 	 		:	 	ReadeBpResponse
**		Definition   	:		Read the Bp output
**
**************************************************************************************************************/

int ReadBpResponse(void)
{
	int i = 0;	
	unsigned char byte;
	
	read(BP_fd, &byte, 1);
	fcntl(BP_fd,F_SETFL,0);
	BpBuffer[BpIndex] = byte;						
	if(BpIndex >=18)
	{
		HighBp= BpBuffer[2];         
		LowBp= BpBuffer[4] ;
		PulseRate= BpBuffer[16];
		printf("HighBP=%d   LowBP=%d   Pulserate=%d \n",HighBp, LowBp, PulseRate);
		for(i=0;i<18;i++)
		{
			printf("BP DATA = 0X%x \n", BpBuffer[i]);
		}
		return 1;
	}
	printf("BP DATA = %d \n", BpBuffer[BpIndex]);
	BpIndex++;
	
	return 0;
}


/*************************************************************************************************************
**		function 	 		:	 	AbortBP
**		Definition   	:		Stops the BP Test
**
**************************************************************************************************************/
void AbortBP(void)
{
	int abt, k, i;
	unsigned char cmd = '-';
	unsigned char Abt[10];
	unsigned char abort[5]={0x3A, 0x79,0x01,0x00,0x4C};

	abt = write(BP_fd, &abort, sizeof(abort));
	fcntl(BP_fd,F_SETFL,O_FSYNC);
	
	if (abt < 0)
	{
		fputs("write() of 1 bytes failed!\n", stderr);
	}
	else
	{
		printf("Successfully wrote  bytes= %d\n", abt);
		memset(Abt, 0, sizeof(Abt));
		read(BP_fd, Abt, sizeof(Abt));
		fcntl(BP_fd,F_SETFL,0);
		printf("No of bytes read is %d\n",abt);
		if (abt <= 0)
		{
			fputs("read failed!\n", stderr);
		}
		else
		{
			for(k=0;k<100;k++);
			write(BP_fd, &cmd, 1);
			for(i=0;i<abt;i++)
			{
				printf("ABORT Response = 0X%x \n", Abt[i]);
			}
		}
	}
}


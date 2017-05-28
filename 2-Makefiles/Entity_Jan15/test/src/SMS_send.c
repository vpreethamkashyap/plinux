#include"../inc/Header.h"

struct timeval start;

extern int UserMode,LoopState;
extern int GSM_fd;
extern char GsmSerialPortName[64];

char SigStrengthStr[4];	
char SmsFormat[5]  = "text";
unsigned char GsmRxBuffer[255];
unsigned char GsmTxBuffer[512];
unsigned char MobileNumber[16];

int SigStrength;
int SmsSwitch = 0;
int TestStartTime = 0;
long PrevSecVal = 0;

int SendSms(int);
int OpenSmsPort(void);
int CallTimeOut(void);
int SendAtCommand(int);
int SelectSmsFormat(int);
int TestGSMBoard(void);
int GetSignalStrength(int);
void SendCommandDelay(int);
void SendSmsToUser(int);



/********************************************************************************************************
**
**	Function Name		: 	TestGSMBoard
** 	Description 		:	 	Tests the GSM Board
**
*********************************************************************************************************/

int TestGSMBoard(void)
{
	volatile int CaseTrue = 1;
	strcpy(GsmTxBuffer,"Wellth GSM Test");
	strcpy(MobileNumber,"9663127247"); //
			
	printf("SMS to---------- %s", MobileNumber);
	printf("SMS is --\n %s", GsmTxBuffer);
	
	SmsSwitch = 0;
	while(CaseTrue)
	{
		switch(SmsSwitch)
		{
			case 0:
				// open the sms port
				if(OpenSmsPort())
				{
					CaseTrue  = 0;
				}
				SmsSwitch = SmsSwitch +1; 
			break;
			
			case 1:
				// send the AT command
				printf("send the AT command \n");
				if(SendAtCommand(6))
				{
					CaseTrue  = 0;
				}
				SmsSwitch = SmsSwitch + 1; 
			break;
											
			case 2:
				// select the SMS SmsFormat
				printf("Select the SMS SmsFormat\n");
				if(SelectSmsFormat(6))
				{
					CaseTrue  = 0;
				}
				SmsSwitch = SmsSwitch +1; 
			break;
			
			case 3:
				printf("Send SMS To user\n");
				// send sms to User
				if(SendSms(6))
				{
					CaseTrue  = 0;
				}	
				SmsSwitch = SmsSwitch +1; 
			break;
			
			case 4:
				// Close the serial port
				nu_SerialComPort_Close (GSM_fd);
				LoopState = DO_LOOP_TEST;
				return 1;
		}		
	}
		
	LoopState = DO_LOOP_TEST;
					
	// get the signal strength
	printf("Get the signal strength\n");
	GetSignalStrength(6);		
	//ResetModem();		
	return 0;				
}

/********************************************************************************************************
**
**	Function Name		: 	SendSmsUser
** 	Description 		:	 	Send the SMS to USER
**
*********************************************************************************************************/
void SendSmsToUser(int MaxTries)
{
	FILE	*sms_fp,*fp;
	int i = 0;
	// This below file opening read sms from file	
	sms_fp = fopen(SMS_SEND_FILE, "r"); 	
	if(sms_fp == NULL)
	{
		printf("Sms file can't open");
	} 
	else 
	{
		fread(GsmTxBuffer, sizeof(GsmTxBuffer), 1, sms_fp);
		fclose(sms_fp);
	}

	// This below file opening get the user mobile MobileNumber
	fp = fopen (IN_ENTERY_FILE, "r"); 
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	}
	else
	{
		fread(MobileNumber,sizeof(MobileNumber),1,fp);
		fclose(fp);		
	}
	
	printf("SMS to---------- %s", MobileNumber);
	printf("SMS is --\n %s", GsmTxBuffer);
	for(i=0;i<MaxTries;i++)
	{
		if(TestGSMBoard())
		{
				LoopState = DO_LOOP_TEST;
				return;
		}
	}
	LoopState = DO_LOOP_TEST;
}

/********************************************************************************************************
**
**	Function Name		: 	OpenSmsPort
** 	Description 		:	 	opens the GSM serial port
**
*********************************************************************************************************/
int OpenSmsPort(void)
{
	//GSM_fd = ArgOpenSerialPort( GsmSerialPortName, 115200);
	GSM_fd = ArgOpenSerialPort( "/dev/ttyUSB2" , 9600);
	if(GSM_fd < 0) 
	{
		printf("System not able to open GSM serial port  \n");
		return 1;
	}
	else
	{
		printf("System able to open GSM serial port  \n");
	}
	return 0;
}


/********************************************************************************************************
**
**	Function Name		: 	SendAtCommand
** 	Description 		:	 	Send the AT command 
**
******************************************************************************************************** */

int SendAtCommand(int MaxTries)
{ 
	int BytesWritten = 0;
	int NoOfTries = 0;
	
	PrevSecVal = 0;
	TestStartTime = 0;	
	
	for(NoOfTries=0; NoOfTries < MaxTries; NoOfTries++)
	{
		//Write command to GSM PORT	
		if((BytesWritten = serial_port_write(GSM_fd, "AT\r\n") ) >=2 )
		{
			printf("byte written= %d\n", BytesWritten);
			SendCommandDelay(1);
		}

		//Read GSM PORT	
		memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 8);
		printf("GsmRxBuffer %s \n", GsmRxBuffer);
		if(strncmp(GsmRxBuffer, "AT", 2) == 0)
		{
			memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
			timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 4);
			printf("%s", GsmRxBuffer);
			if(strncmp(GsmRxBuffer, "OK", 2) == 0)
			{
				printf("AT Command Ok \n");
				return 0;
			} 
		} 
	}
	printf("AT Command Error");
	return 1;				
}

/********************************************************************************************************
**
**	Function Name		: 	ResetModem
** 	Description 		:	 	Resets the Modem
**
******************************************************************************************************** */

void ResetModem(void)
{
/***********************************************************************************
		Give the Reset Pulse to GSM Modem
		TxTime = 24 Seconds
***********************************************************************************/
	const char Command1[13] = "AT+QPOWD=0";		//AT+QPOWD=0
	const char Command2[13] = "AT+CFUN=1";		//AT+CFUN=1

	serial_port_write(GSM_fd, Command1);
			//Read GSM PORT	
	memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
	timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 8);
	printf("GsmRxBuffer %s \n", GsmRxBuffer);
	SendCommandDelay(50);

	serial_port_write(GSM_fd, Command2);
	memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
	timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 8);
	printf("GsmRxBuffer %s \n", GsmRxBuffer);
	SendCommandDelay(50);
}

/********************************************************************************************************
**
**	Function Name		: 	GetSignalStrength
** 	Description 		:	 	Get the Signal Strength
**
******************************************************************************************************** */

int GetSignalStrength(int MaxTries)
{
	int index = 0, i = 0;
	int nbytes,BytesWritten;
	int NoOfTries=0, 

	SigStrength = 0;
	PrevSecVal = 0;
	TestStartTime = 0;
	
	SendCommandDelay(10);
	
	for(NoOfTries=0; NoOfTries<MaxTries; NoOfTries++)
	{
		//SendCommandDelay(30);
		tcflush (GSM_fd, TCIOFLUSH);
		
		//Write command to GSM PORT
		if((BytesWritten = serial_port_write(GSM_fd, "AT+CSQ\r\n")) >= 8)
		{
			printf("AT+CSQ byte written= %d\n", BytesWritten);
		}
		else
		{
			return 1;
		}
		SendCommandDelay(1);
		memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 8);
		printf("1. GsmRxBuffer %s \n", GsmRxBuffer);
		if( strncmp(GsmRxBuffer, "+CSQ:", 5) == 0)
		{
			printf("Got the  Strength \n");
			printf("GsmRxBuffer %s \n", GsmRxBuffer);
			SigStrengthStr[0] = GsmRxBuffer[6];
			SigStrengthStr[1] = GsmRxBuffer[7];
			SigStrengthStr[2] = 0;
			printf("SigStrengthStr string %s\n", SigStrengthStr);
			SigStrength = atoi(SigStrengthStr);
			printf("SigStrength is %d \n",SigStrength);
			return 0;
		}
		SendCommandDelay(10);	
		memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 14);
		printf("2 .GsmRxBuffer %s \n", GsmRxBuffer);
		
		if( strncmp(GsmRxBuffer, "+CSQ:", 5) == 0)
		{
			printf("Got the  Strength \n");
			printf("GsmRxBuffer %s \n", GsmRxBuffer);
			SigStrengthStr[0] = GsmRxBuffer[6];
			SigStrengthStr[1] = GsmRxBuffer[7];
			SigStrengthStr[2] = 0;
			printf("SigStrengthStr string %s\n", SigStrengthStr);
			SigStrength = atoi(SigStrengthStr);
			printf("SigStrength is %d \n",SigStrength);
			return 0;
		}
	}		
	return 1;		
}

/********************************************************************************************************
**
**	Function Name		: 	SelectSmsFormat
**  Description 		:	 	Set the sms transmit mode
**
*********************************************************************************************************/
int SelectSmsFormat	(int MaxTries)
{
	int BytesWritten = 0;
	int NoOfTries=0;

	PrevSecVal = 0;
	TestStartTime = 0;
	
	tcflush (GSM_fd, TCIOFLUSH);
	SendCommandDelay(20);
	memset(GsmTxBuffer, 0, sizeof(GsmTxBuffer));
	
	if(SmsFormat[0] == 't' || SmsFormat[0] == 'T')
		strcpy(GsmTxBuffer, "AT+CMGF=1\r\n");
	else if(SmsFormat[0] == 'p' || SmsFormat[0] == 'P')
		strcpy(GsmTxBuffer, "AT+CMGF=0\r\n");
	else
		strcpy(GsmTxBuffer, "AT+CMGF=1\r\n");
	
	for(NoOfTries=0; NoOfTries < MaxTries; NoOfTries++)
	{
		tcflush (GSM_fd, TCIOFLUSH);
		
		//Write command to GSM PORT
		if ( (BytesWritten = serial_port_write(GSM_fd, GsmTxBuffer)) >= 11)
		{
			printf("AT+CMGF=1 bytes written= %d\n", BytesWritten);
			SendCommandDelay(20);
		}
		else
		{
			return 0;
		}
		
		//Read From GSM Port
		memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 8);
		printf("GsmRxBuffer %s \n", GsmRxBuffer);
		if(strncmp(GsmRxBuffer, "AT+CMGF=1", 8) == 0)
		{
			memset(GsmRxBuffer, 0, sizeof(GsmRxBuffer));
			timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, 4);
			printf("%s", GsmRxBuffer);
		} 
		if((GsmRxBuffer[0] == 'O') || (GsmRxBuffer[0] == 'K') || (GsmRxBuffer[1] == 'K'))
		{
			printf("AT+CMGF=1 Command Ok \n");
			return 0;
		}
		//	SendCommandDelay(40);
	}
	printf("AT+CMGF=1 Command Error");
	return 1;				
}

/********************************************************************************************************
**
**	Function Name		: 	SendSms
** 	Description 		:	 	Transmits Buffer To User
**
*********************************************************************************************************/
int SendSms(int MaxTries)
{
	char Com1[] 		= "AT+CMGS=";
	char DoubleCots[2]  = {0x22,0x00};
	char Space[2]  		= {0x20,0x00};
	char Com4[]  		= "ALL";
	int BytesWritten = 0;	
	int NoOfTries = 0;

	for(NoOfTries=0; NoOfTries < MaxTries; NoOfTries++)
	{
		SendCommandDelay(100);
		tcflush (GSM_fd, TCIOFLUSH); 
		memset(GsmTxBuffer, 0, sizeof(GsmTxBuffer));
		strcpy(GsmTxBuffer,Com1);
		strcat(GsmTxBuffer,DoubleCots);
		strcat(GsmTxBuffer,MobileNumber);
		strcat(GsmTxBuffer,DoubleCots);
		printf("%s\n",GsmTxBuffer);	
		
		if( (BytesWritten = serial_port_write(GSM_fd,GsmTxBuffer)) > 8)
		{
			printf("AT+CMGS=1 bytes written= %d\n", BytesWritten);
		}
		else
		{
			return 1;
		}
		SendCommandDelay(100);

		SendCRLF();
		
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer, (BytesWritten));	
		printf("GsmRxBuffer %s \n",GsmRxBuffer);
		
		timeout_SerialComPort_BlockRead (GSM_fd, GsmRxBuffer,15);	
		printf("GsmRxBuffer %s \n",GsmRxBuffer);
		//if(GsmRxBuffer[0] == '>')
		{	
			SendCommandDelay(100);
			memset(GsmTxBuffer,0,100);
			strcpy(GsmTxBuffer,"Wellth");
			serial_port_write(GSM_fd,GsmTxBuffer);
			
			SendCRLF();
			SendCtrlZ();
			SendCRLF();
			SendCommandDelay(1);
			printf("SMS has send\n");	
			return 0;
		}
	}
	return 1;
}

void SendCRLF(void)
{
	SendCStringiageReturn();
	SendLineFeed();
}

/********** /r Enter *************/

void SendCStringiageReturn(void)
{	 
	unsigned Buf[2]  = {0x0d,0};
	serial_port_write(GSM_fd,Buf);	
}

/********** /n *************/

void SendLineFeed(void)
{    
	unsigned Buf[2]  = {0x0A,0};
	serial_port_write(GSM_fd,Buf);	
}

void SendCtrlZ(void)
{ 
	unsigned Buf[2]  = {0x1A,0};
	serial_port_write(GSM_fd,Buf);	
}

void SendCommandDelay(int DelayCount)
{
	long int DelayTime = 100000;
	while(DelayCount>0)
	{
		while(DelayTime--);
		DelayCount--;
		DelayTime = 100000;
	}
}

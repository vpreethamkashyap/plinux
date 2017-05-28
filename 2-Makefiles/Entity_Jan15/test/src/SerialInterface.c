#include "../inc/Header.h"

int BP_fd;
int MDB_fd;
int GSM_fd;
int RFID_fd;
int Weight_fd;
int BodyFat_fd;

char MODBUS_USB[32];
char RFID_PORT_USB[32];

char BpSerialPortName[64];
char RfidSerialPortName[64];
char GsmSerialPortName[64];
char WeightSerialPortName[64];
char BodyFatSerialPortName[64];

extern int SRL_index;
extern int SerialPortStatus;
extern char *SerialPortName[];

void ReadRfidSensor(void);
void ReadBp_SerialPort(void);
void ReadGsm_SerialPort(void);
void OpenRFID_SerialPort(void);
void ReadWeight_SerialPort(void);
void ReadBodyFat_SerialPort(void);
void OpenProcessor_SerialPort(void);

/*************************************************************************************************************
**		function 	 		:	 	OpenSerialPort
**		Definition   	:		Opens all Serial Ports
**
**************************************************************************************************************/

void OpenSerialPort(void)
{
	#ifdef W2_INTERFACE_EN
		printf("You are in PIC based Sesnor Interface \n");
		OpenProcessor_SerialPort();	
	#else
		printf("You are in Direct Sesnor Interface \n");
		
		#ifdef BMI_INTERFACE_EN
			ReadWeight_SerialPort();
		#endif
		#ifdef BP_INTERFACE_EN
			ReadBp_SerialPort();
		#endif		
		#ifdef BLI_INTERFACE_EN
			ReadBodyFat_SerialPort();
		#endif
	#endif

	#ifdef GSM_INTERFACE_EN
		ReadGsm_SerialPort();
	#endif
	
	#ifdef RFID_ENTRY_MODE_EN
		printf("RFID Interfaced Enabled \n");
		OpenRFID_SerialPort();
	#endif
}

/*************************************************************************************************************
**		function 	 		:	 	OpenProcessor_SerialPort
**		Definition   	:		Open Co-Processor connected serial port
**
**************************************************************************************************************/
void OpenProcessor_SerialPort(void)
{
	memset(MODBUS_USB, 0, sizeof(MODBUS_USB));
	MDB_fd=-1;

	MDB_fd = ArgOpenSerialPort(PROCESSOR_USB_PORT, 9600);
	if (MDB_fd < 0)
	{
		printf("\nAlert: reconnect the master co-processor port USB and restart the daemon");
		return;
	} 
	else 
	{
		SerialPortStatus = 1;
	}
	
	if(MDB_fd < 0) 
	{
		printf("__Error : The Co-Processor is not connected");
		return;
	}
}


/*************************************************************************************************************
**		function 	 		:	 	ReadWeight_SerialPort
**		Definition   	:		Read the Weight Usb Port
**
**************************************************************************************************************/

void ReadWeight_SerialPort(void)
{
	FILE *fp;
	
	char *StrPtr;
	char PrevLine[512];
	char Line[512];
	int len=0;

	system("/bin/dmesg | grep \"ch341-uart converter now\" > /home/ab.c");
	fp = fopen("/home/ab.c", "r");
	
	while( GetLine(fp, Line) != 0)
	{
		strcpy(PrevLine, Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "ch341-uart converter now attached to ");
	
	if(StrPtr == NULL) 
	{
		printf("\n**********\nError : The WeightSensor is not connected\n*************\n");
	} 
	else 
	{
		StrPtr = strstr(PrevLine, "tty");
		strcpy(WeightSerialPortName, "/dev/");
		strcat(WeightSerialPortName, StrPtr);
		len = strlen(WeightSerialPortName);
		printf(">>> %s -- %d\n", WeightSerialPortName, len);
		WeightSerialPortName[len] = 0;		
	}
}


/*************************************************************************************************************
**		function 	 		:	 	ReadBp_SerialPort
**		Definition   	:		Get the BP serial Port
**
**************************************************************************************************************/

void ReadBp_SerialPort(void)
{
	FILE *fp;
	
	char *StrPtr;
	char PrevLine[512];
	char Line[512];
	int len=0;

	system("/bin/dmesg | grep \"pl2303 converter now\" > /home/ab.c");
	fp = fopen("/home/ab.c", "r");
	
	while( GetLine(fp, Line) != 0)
	{
		strcpy(PrevLine, Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "pl2303 converter now attached to");
	
	if(StrPtr == NULL) 
	{
		printf("\n**********\nError : The BP Sensor is not connected\n*************\n");
	} 
	else 
	{
		StrPtr = strstr(PrevLine, "tty");
		strcpy(BpSerialPortName, "/dev/");
		strcat(BpSerialPortName, StrPtr);
		len = strlen(BpSerialPortName);
		printf(">>> %s -- %d\n", BpSerialPortName, len);
		BpSerialPortName[len] = 0;
		printf("Entity is able to detect : \n %s\n",BpSerialPortName );		
	}
}

/*************************************************************************************************************
**		function 	 		:	 	ReadGsm_SerialPort
**		Definition   	:		Get the GSM Port
**
**************************************************************************************************************/

void ReadGsm_SerialPort(void)
{
	FILE *fp;
	
	char *StrPtr;
	char PrevLine[512];
	char Line[512];
	int len=0;

	system("/bin/dmesg | grep \"cp210x converter now\" > /home/ab.c");
	fp = fopen("/home/ab.c", "r");
	
	while( GetLine(fp, Line) != 0)
	{
		strcpy(PrevLine, Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "cp210x converter now attached to");
	
	if(StrPtr == NULL) 
	{
		printf("\n**********\nError : GSM Board is not connected\n*************\n");
	} 
	else 
	{
		StrPtr = strstr(PrevLine, "tty");
		strcpy(GsmSerialPortName, "/dev/");
		strcat(GsmSerialPortName, StrPtr);
		len = strlen(GsmSerialPortName);
		printf(">>> %s -- %d\n", GsmSerialPortName, len);
		GsmSerialPortName[len] = 0;		
	}
}

/*************************************************************************************************************
**		function 	 		:	 	ReadBodyFat_SerialPort
**		Definition   	:		Get the BLI sensor Port
**
**************************************************************************************************************/

void ReadBodyFat_SerialPort(void)
{
	FILE *fp;
	
	char *StrPtr;
	char PrevLine[512];
	char Line[512];
	int len=0;

	system("/bin/dmesg | grep \"cp210x converter now\" > /home/ab.c");
	fp = fopen("/home/ab.c", "r");
	
	while( GetLine(fp, Line) != 0)
	{
		strcpy(PrevLine, Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "cp210x converter now attached to");
	
	if(StrPtr == NULL) 
	{
		printf("\n**********\nError : The BLI Sensor is not connected\n*************\n");
	} 
	else 
	{
		StrPtr = strstr(PrevLine, "tty");
		strcpy(BodyFatSerialPortName, "/dev/");
		strcat(BodyFatSerialPortName, StrPtr);
		len = strlen(BodyFatSerialPortName);
		printf(">>> %s -- %d\n", BodyFatSerialPortName, len);
		BodyFatSerialPortName[len] = 0;		
	}
}

/*************************************************************************************************************
**		function 	 		:	 	OpenRFID_SerialPort
**		Definition   	:		opens the serial port for RFID
**
**************************************************************************************************************/

void OpenRFID_SerialPort(void)
{
	FILE *rfid_fp;
	
	char *StrPtr;
	char PrevLine[512];
	char Line[512];
	char readBuf[64];
	int i=0,len;

	system("/bin/dmesg | grep \"FTDI USB Serial Device converter now\" > /home/ab.c");
	rfid_fp = fopen("/home/ab.c", "r");
	
	while( GetLine(rfid_fp, Line) != 0)
	{
		strcpy(PrevLine, Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "FTDI USB Serial Device converter now attached to");
	fclose(rfid_fp);
	
	if(StrPtr == NULL) 
	{
		printf("\n**********\nError : The RFID Sensor is not connected\n*************\n");
	} 
	else 
	{
		StrPtr = strstr(PrevLine, "tty");
		strcpy(RfidSerialPortName, "/dev/");
		strcat(RfidSerialPortName, StrPtr);
		len = strlen(RfidSerialPortName);
		printf(">>> %s -- %d\n", RfidSerialPortName, len);
		RfidSerialPortName[len] = 0;
		strcpy(RFID_PORT_USB,RfidSerialPortName);
		printf("RfidSerialPortName %s \n",RfidSerialPortName);
		RFID_fd = ArgOpenSerialPort(RfidSerialPortName, 9600);
		tcflush(RFID_fd, TCIFLUSH);
		//fcntl(RFID_fd,F_SETFL,d);
		fcntl(RFID_fd,F_SETFL,O_SYNC);
		printf("RFID String Read \n");
	}
}



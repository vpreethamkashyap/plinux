#include"../inc/Header.h"

// Declaration of functions
void GetWeightValue(void);

void OpenPort(char *SerialPortName, int baudRate);

// Declaration of Local variables
extern int LoopState;
int W_fd;
extern int RFID_fd;
extern float Weight,Sub,Mul;
extern char WeightSerialPortName[64];

char avg1[5], avg2[5],avg3[5], avg4[5], avg5[5];

struct termios oldtp, newtp;

/*************************************************************************************************************
**		function 	 		:	 	RunBmiDirectTest
**		Definition   	:		opens the serial port & set the baud rate
**
**************************************************************************************************************/

void RunBmiDirectTest(void)
{
	float f1,f2,f3,f4;
	
	printf("Weight Read start\n");
	OpenPort(WeightSerialPortName, 2400);
	sleep(1);

	//GetWeightValue();
	readport();
	
	f1 = strtof(avg1, NULL);
	f2 = strtof(avg2, NULL);
	f3 = strtof(avg3, NULL);
	f4 = strtof(avg4, NULL);

	Weight = ((f1+f2+f3+f4)/4);
	printf("\nYour Weight is %.2f Kgs\n\n",Weight);
	printf("Your Weight is = %f\n",Weight); 
	
	if(Weight < 0)
	{
		Weight *= (-1);
	}
	CalculateBmi();
	UpdateBmi_SummaryFile();		
	UpdateBmi_RawFile();
	UpdateBmi_DataBase();
	LoopState = DO_LOOP_TEST;	
	close(W_fd);
}

/*************************************************************************************************************
**		function 	 		:	 	GetWeightValue
**		Definition   	:		Read the weight value from Sensor
**
**************************************************************************************************************/

void GetWeightValue(void)
{
	int readsize,i,j;
	static int cnt =0;
	char tempbuf[10], RawBuffer[100];
	
	//clear all the buffer
	memset(tempbuf,0,sizeof(tempbuf));		
	memset(RawBuffer,0,sizeof(RawBuffer));
	
	//If cnt=100 the loop gets end
	while(cnt<100)
	{						
		//read the W_fd until  cnt becomes == 100
		readsize=read(W_fd,tempbuf,sizeof(tempbuf));
		printf("Read Size %d \n",&readsize);	
		fcntl(W_fd,F_SETFL,0);		
		for(i=0;i<readsize;i++)
		{
			//Taking 100 values of weight in RawBuffer
			RawBuffer[cnt] = tempbuf[i];	
			cnt++;		
		}
		//clear the tempbuf
		memset(tempbuf,0,sizeof(tempbuf));		
	}
	
	for(j=0;j<100;j++)
	{
		while ((RawBuffer[j] == '\n') && (RawBuffer[j+1] == '\n'))
		{
			j+=2;
			memcpy(avg1, &RawBuffer[j], 5);
			j+=7;
			memcpy(avg2, &RawBuffer[j], 5);
			j+=7;
			memcpy(avg3, &RawBuffer[j], 5);
			j+=7;
			memcpy(avg4, &RawBuffer[j], 5);
			j+=7;
			memcpy(avg5, &RawBuffer[j], 5);
			return;
		} 
	}
}     

void readport(void)
{
	int readsize,i,j;
	static int cnt=0;
	char tempbuf[10], main_buf[200];
	
	memset(tempbuf,0,sizeof(tempbuf));//clear all the buffer
	memset(main_buf,0,sizeof(main_buf));
	
	while(cnt<100)
	{ 
		readsize=read(W_fd,tempbuf,sizeof(tempbuf)); 
		printf("readsize = %d \n",readsize);
		fcntl(W_fd,F_SETFL,0);
		for(i=0;i<readsize;i++)
		{
			main_buf[cnt] = tempbuf[i]; //Taking 100 values of weight in main_buf
			cnt++;
		}
		memset(tempbuf,0,sizeof(tempbuf));//clear the tempbuf
	}//end of while

	for(j=0;j<100;j++)
	{
			while ((main_buf[j] == '\n') && (main_buf[j+1] == '\n'))
			{
				j+=2;
				memcpy(avg1, &main_buf[j], 5);
				j+=7;
				memcpy(avg2, &main_buf[j], 5);
				j+=7;
				memcpy(avg3, &main_buf[j], 5);
				j+=7;
				memcpy(avg4, &main_buf[j], 5);
				j+=7;
				memcpy(avg5, &main_buf[j], 5);
				return;
			} 
	}
}//end of read port                                    

/*************************************************************************************************************
**		function 	 		:	 	openport
**		Definition   	:		opens the serial port with different settings
**
**************************************************************************************************************/


void OpenPort(char *SerialPortName, int baudRate)
{
	W_fd = open(SerialPortName, O_RDWR | O_NOCTTY |O_NDELAY );
	if (W_fd <0)
	{
		printf("Not Able to Open Serial Port \n");
		perror(SerialPortName);
	}
	printf("Able to Open Serial Port %s \n",SerialPortName);

	fcntl(W_fd,F_SETFL,0);
	tcgetattr(W_fd,&oldtp); /* save current serial port settings */
	bzero(&newtp, sizeof(newtp));

	newtp.c_cflag = baudRate | CRTSCTS | CS8 | CLOCAL | CREAD;

	newtp.c_iflag = IGNPAR | ICRNL;

	newtp.c_oflag = 0;

	newtp.c_lflag = ICANON;

	newtp.c_cc[VINTR]    = 0;     /* Ctrl-c */
	newtp.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
	newtp.c_cc[VERASE]   = 0;     /* del */
	newtp.c_cc[VKILL]    = 0;     /* @ */
	//newtp.c_cc[VEOF]     = 4;     /* Ctrl-d */
	newtp.c_cc[VEOF]     = 0;     /* Ctrl-d */
	newtp.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	newtp.c_cc[VMIN]     = 6;     /* blocking read until 1 character arrives */
	newtp.c_cc[VSWTC]    = 0;     /* '\0' */
	newtp.c_cc[VSTART]   = 0;     /* Ctrl-q */
	newtp.c_cc[VSTOP]    = 0;     /* Ctrl-s */
	newtp.c_cc[VSUSP]    = 0;     /* Ctrl-z */
	newtp.c_cc[VEOL]     = 0;     /* '\0' */
	newtp.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	newtp.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	newtp.c_cc[VWERASE]  = 0;     /* Ctrl-w */
	newtp.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
	newtp.c_cc[VEOL2]    = 0;     /* '\0' */
	tcflush(W_fd, TCIFLUSH);
	tcsetattr(W_fd,TCSANOW,&newtp);
}
















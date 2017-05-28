
/********************************************************************************************
							List of Header Files
*********************************************************************************************/
#include "../inc/Main.h"
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h> 

//#define THREAD_EN


//#define NEW 10
/********************************************************************************************
							Structure variable declaration
*********************************************************************************************/
// timer struct
struct timeval start, end;

// structure used for Data  transition between GTK
_INPUT_DATA_STRUCT		Din;
_LOGIN_DATA_STRUCT		Uin;
_IN_FILE_STRUCT 			Indata;
_BMI_TEST_STRUCT 			Bmi;
_BP_TEST_STRUCT				Bp;
_BLI_TEST_STRUCT			Bli;
_LOGIN_TEST_STRUCT		login;

/********************************************************************************************
							List of variable Declaration
*********************************************************************************************/
int testStartTime = 0;
int SerialPortStatus =0;
int UserMode = 0;
int LoopState=0;
long prevSecVal = 0;
int CurrentValue  = 0;
int LastValue  = 0;
volatile int TestTimeOutValue  = 0;

// Threads
pthread_t LoopTest_t1, PeripheralTest_t2; 

extern int BpSwitch;
extern int Hight,TempWeight;
extern unsigned short int BmiTestEn;
extern unsigned short int BpTestEn;
extern unsigned short int BliTestEn;
extern unsigned char HoldingReg[10];

/********************************************************************************************
							List of Function Declaration
*********************************************************************************************/
void CallWhileLoop(void);
void *DoLoopTest(void *);
void OpenSerialPort(void);
void TestProcSerialPorts(void);
void CheckSensorResponse(void);
void *DoPeripheralTest(void *);

int NEW = 10;
/********************************************************************************************
							Main Starts Here
*********************************************************************************************/
int main(void)
{
	FILE * app_fp;
	
	printf("\nWelcome Wellth Entity Code\n");	
	
	//clear the demon input files
	ClearDemonInputFile();	
	//open the serial port for various interface
	OpenSerialPort();
    
	// if serial port opens up
	#ifdef W2_INTERFACE_EN
		if(SerialPortStatus==0)
		{
			printf(" Wellth System MODBUS Disconnected \n");
			return 0;
		}
	#endif
		
	app_fp = fopen("/home/time_app.c", "w");
	system("/bin/chmod 777 /home/time_app.c");
	fchmod (app_fp, S_IROTH | S_IWOTH | S_IXOTH);
	fclose(app_fp);	
	
	LoopState = DO_LOOP_TEST;
	printf(" Wellth System is Running \n");
	fflush(stdout);
	
	#ifdef PIC_BOARD_SERIAL_TEST
		TestProcSerialPorts();
	#elif defined THREAD_EN
		CallThreads();		
	#else
		printf("Runing wodout Threasds");
		CallWhileLoop();
	#endif
	
	while(1)
	{
		printf("Threads Got reset Command\n");	
		sleep(2);
		CallThreads();		
	}
	
	return 0;
}

/*************************************************************************************************************
**		function 			:	 	CallThreads
**		Definition   	:		Call the all the threads
**
**************************************************************************************************************/

void CallThreads(void)
{
	pthread_create(&LoopTest_t1, NULL, DoLoopTest, (void *)"LoopThread");
	pthread_create(&PeripheralTest_t2, NULL, DoPeripheralTest, (void *)"PeriThread\n");

	pthread_setschedprio (LoopTest_t1 ,2);
	pthread_setschedprio (PeripheralTest_t2 ,1);			
	pthread_join(LoopTest_t1, NULL);			
	pthread_join(PeripheralTest_t2, NULL);
}

/*************************************************************************************************************
**		function 			:	 	CallWhileLoop
**		Definition   	:		Check for which test response 
**
**************************************************************************************************************/
void *DoLoopTest(void *m)
{
	FILE * app_fp;
  char *cp = (char *) m;
  printf("%s", m);
  fflush(stdout);

  while(1)
  {
		// check the sensor response
		CheckSensorResponse();		
	}
}

/*************************************************************************************************************
**		function 			:	 	DoPeripheralTest
**		Definition   	:		Check for which test has enable from GTK Tool	
**
**************************************************************************************************************/
void *DoPeripheralTest(void *m)
{
	char *cp = (char *) m;
  printf("%s", m);
  fflush(stdout);
  int old, oold;
	int res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,&old);
	
	CallWhileLoop();
}
/*************************************************************************************************************
**		function 			:		CheckSensorResponse
**		Definition   	:		Weight for Sensor Response If it is delayed then 
**											it cancels the test
**
**************************************************************************************************************/

void CheckSensorResponse(void)
{
	if (LoopState != DO_LOOP_TEST)
	{
		/*****************************
			check the time if it is more than 2 min then 
			1) clear the daemon input files
			2) give a msg to the UI that sensors are not responding
			3) change LoopState to 1
		*************************/
		gettimeofday(&start, NULL);
		if(prevSecVal != start.tv_sec)
		{
			prevSecVal = start.tv_sec;
			testStartTime++;
		}
		printf("\n__%d__\n", testStartTime);//printf("/*****Thread 1\n");
	} 
	else 
	{
		testStartTime = 0;
		gettimeofday(&start, NULL);
		if(LastValue  == 0)
		{
			LastValue = start.tv_sec;
		}
		else
		{
			CurrentValue = start.tv_sec;
			if((CurrentValue - LastValue) >10 )
			{
				printf("\n Thread 1 alive \n");	
				LastValue  =	0;	
			}
		}		
	}
	
	// compare with maximum delay time
	if(testStartTime > TestTimeOutValue)
	{
		BpSwitch = 0;
		LoopState =  DO_LOOP_TEST;
		ClearDemonInputFile();	
		printf("/**********************/\nRetry Test..! No Response From Sensor resetted the Daemon....!\n/**********************/\n");
		testStartTime = 0;
		prevSecVal = 0;
		
		#ifdef THREAD_EN
			printf("/*********THREAD_EN*************/");
			pthread_cancel(PeripheralTest_t2);					
			printf("cancelling thread\n");	
			pthread_exit("Bye");
		#endif
	}
	
	// If Bp test enable then always check for abort files
	if(BpTestEn ==1)
	{
		CheckAbortFile();
	}	
}



/*************************************************************************************************************
**		function 			:	 	CallWhileLoop
**		Definition   	:		Check for which test has enable from GTK Tool	
**
**************************************************************************************************************/
void CallWhileLoop(void)
{
	while(1)
	{
		#ifndef THREAD_EN
			// check the sensor response
			//printf("check the sensor response \n");
			//CheckSensorResponse();	
		#endif
		
		switch(LoopState) 
		{		
			// check the inputs from GTK & Run the test
			case DO_LOOP_TEST:
					testStartTime = 0;
				#ifdef GTK_DISABLE
					GetUserInputs();					
				#else
					usleep(40000);
					ReadInputFile();
					CheckUserInfo();
				#endif	
			break;
			
			// Run the bmi test
			case DO_BMI_TEST:
				TestTimeOutValue  = 6;
				#ifdef W2_INTERFACE_EN
					RunBmiMdbTest();
				#else
					RunBmiDirectTest();
				#endif
			break;
			
			// Run the bp test
			case DO_BP_TEST:
				TestTimeOutValue  = 20;
				#ifdef W2_INTERFACE_EN
					RunBpMdbTest();
				#else
					ReadBPDirectTest();
				#endif
			break;
			
			// Run the bli test
			case DO_BLI_TEST:
				TestTimeOutValue  = 6;
				#ifdef W2_INTERFACE_EN
					RunBliMdbTest();
				#else
					ReadBliDirectTest();
				#endif
			break;
			
			// Run the Ecg test
			case DO_ECG_TEST:
			break;	
			
			// Run the Rfid test		
			case DO_RFID_TEST:
				printf("Test RFID Board \n");
				ReadRfidSensor();
				LoopState = DO_LOOP_TEST;
			break;	
			
			// Run the GSM test	
			case DO_SMS_TEST:
				TestTimeOutValue  = 500;
				#ifdef TEST_GSM_BOARD
					printf("Test GSM Board");
					TestGSMBoard();
				#else
					GSM_INTERFACE_EN
					SendSmsToUser(3);
					ClearDemonInputFile();
				#endif
			break;
			default:
			break;
		}
	}
}






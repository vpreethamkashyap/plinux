
/********************************************************************************************
							List of Header Files
*********************************************************************************************/

#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 

/********************************************************************************************
							Structure variable declaration
*********************************************************************************************/
// timer struct
struct timeval start, end;

int Thread2Data = 0;
int Thread2Reset = 0;
volatile int TestTimeOutValue = 25;
/********************************************************************************************
							List of variable Declaration
*********************************************************************************************/
int testStartTime = 0;
long prevSecVal = 0;
int CurrentValue  = 0;
int LastValue  = 0;


// Threads
pthread_t LoopTest_t1, PeripheralTest_t2; 

/********************************************************************************************
							List of Function Declaration
*********************************************************************************************/
void GetUsrInputs(void);
void CallThreads(void);
void *DoLoopTest(void *);
void CallWhileLoop(void);
void *DoPeripheralTest(void *);


/********************************************************************************************
							Main Starts Here
*********************************************************************************************/
int main(void)
{
	printf("\n You can test two threads functionality \n");	
	printf("\n one threads will work as time counter\n");	
	printf("\n Second Thread waits data from the user \n");	
	printf("\n if user won't send any data it kills all threads \n");	
	
	CallThreads();		
	
	while(1)
	{
		printf("\nThreads Got reset Command\n");	
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
	Thread2Reset = 0;
	printf("Two threads are creating \n");
	pthread_create(&LoopTest_t1, NULL, DoLoopTest, (void *)"LoopThread");
	pthread_create(&PeripheralTest_t2, NULL, DoPeripheralTest, (void *)"UserInputThread\n");

	pthread_setschedprio (LoopTest_t1 ,2);
	pthread_setschedprio (PeripheralTest_t2 ,1);			
	printf("Two threads are joining \n");
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
	CallWhileLoop(); 
}

void CallWhileLoop(void)
{
	while(1)
	{
		if(Thread2Data != 0)
		{
			printf("You have pressed the %d \n",Thread2Data);
			testStartTime = 0;
			Thread2Data = 0;
			Thread2Reset = 0;
			printf("*********** Thread 1 got data from Thread 2 ************\n\n\n");
		}
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
		//printf("\n Thread 1 Time Value __%d__\n", testStartTime);
		
		// compare with maximum delay time
		if(testStartTime > TestTimeOutValue)
		{
			printf("/**********************/\nRetry Test..! No Response From Sensor resetted the Daemon....!\n/**********************/\n");
			testStartTime = 0;
			prevSecVal = 0;
			printf("/*********THREAD_EN*************\n");
			pthread_cancel(PeripheralTest_t2);					
			printf("cancelling thread\n");	
			pthread_exit("Bye");
			printf("\n");
			printf("\n");
		}	
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
	
	int old;
	int res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,&old);	
	
	if(Thread2Reset == 0)
		GetUsrInputs();
}

void GetUsrInputs(void)
{
		printf("User has to send the Data to thread number 1 \n");
		printf("Please press any integer\n");
		printf("Other wise this thread will be killed \n");
		scanf("%d",&Thread2Data);
		printf("\n");
		printf("\n");
		Thread2Reset = 1;
}




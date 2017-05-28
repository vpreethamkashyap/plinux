#include <stdio.h>
//#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void Process1(void);
void Process2(void);
void Process3(void);
void Process4(void);
void Process5(void);
void Process6(void);
void Process7(void);
void Process8(void);
void Process8_1(void);
void Process9(void);
void Process10(void);
void Process11(void);
void Process12(void);
void Process13(void);
void Process13_1(void);
void Process14(void);
void Process15(void);
void Process16(void);
void Process17(void);
void Process18(void);
void Process19(void);
void Process20(void);
void ListOfProcessCalls(int);

int main(void)
{
	int process;
	system("clear");
	printf("\n**********************************\n");
	printf("Hi user your are in Process App\n");
	printf("**********************************\n");
	printf("Press 1 to check the Current Process ID\n");
	printf("Press 2 to check the Parent Process ID\n");
	printf("Press 3 to to demonstrate the fork	\n");
	printf("Press 4 to find effect of PID on Fork function\n");
	printf("Press 5 to find effect mutliple Fork function\n");
	printf("Press 6 to get Parent process PID by Fork function\n");
	printf("Press 7 to get child process PID by Fork function\n");
	printf("Press 8 to see Parent & child together	\n");
	printf("Press 81 to see Parent & child together	\n");
	printf("Press 9 to Understand Parent & child together\n");
	printf("Press 10 to Understand Effect of wait function in Parent process\n");
	printf("Press 11 to One Parent & two children\n");
	printf("Press 12 to Data Sharing between Parent & child\n");
	printf("Press 13 to make parent to sleep for more than one child\n");
	printf("Press 131 to make parent to sleep for more than one child\n");
	printf("Press 14 to make parent to wait for more than one child\n");
	printf("Press 15 to Create Zombie process\n");
	printf("Press 16 to orphan process\n");
	printf("Press 17 to Create Zombie Process with one child\n\n\n\n");	
		
	scanf("%d",&process);
	printf("************* See the ouput ******************* \n\n\n");
	ListOfProcessCalls(process);
}

void ListOfProcessCalls(int Process)
{
	switch(Process)
	{
		case 1:
			Process1();
		break;
		case 2:
			Process2();
		break;
		case 3:
			Process3();
		break;
		case 4:
			Process4();
		break;
		case 5:
			Process5();
		break;
		case 6:
			Process6();
		break;
		case 7:
			Process7();
		break;
		case 8:
			Process8();			
		break;
		case 81:			
			Process8_1();
		break;
		case 9:
			Process9();
		break;
		case 10:
			Process10();
		break;		
		case 11:
			Process11();
		break;
		case 12:
			Process12();
		break;
		case 13:
			Process13();
		break;
		case 131:
			Process13_1();
		break;
		case 14:
			Process14();
		break;
		case 15:
			Process15();
		break;
		case 16:
			Process16();
		break;
		case 17:
			Process17();
		break;
		default:
			printf("Option is not present\n");
		break;	
	}
}

/********************************************************************************
 * Description		: This function get the process id of current function
 ********************************************************************************/
 
void Process1(void)
{
	int pid;
	pid = getpid();
	printf ("Process id getpid()  = %d\n",pid);
}

/********************************************************************************
 * Description		: This function get the process id of parent
 ********************************************************************************/

void Process2(void)
{
	int ppid;
	ppid = getppid();
	printf ("Parent Process ID getppid() = %d\n",ppid);
}

/********************************************************************************

 * Description		: This is to demonstrate the fork
 ********************************************************************************/

void Process3(void)
{
	printf ("This is to demonstrate the fork\n");
	fork();
	printf ("Hello world\n");
}

/********************************************************************************
 * Description		: This is to find effect of PID on Fork function
 ********************************************************************************/

void Process4(void)
{
	printf ("The pid before calling fork %d\n",getpid());
	fork();
	printf ("The pid after calling fork %d\n",getpid());
}

/********************************************************************************
 * Description		:	This is to find effect mutliple Fork function
 ********************************************************************************/

void Process5(void)
{
	printf ("Effect of multiple Fork function\n");
	
	printf ("Fork 1 time called \n");
	fork();
	printf ("Fork 1.1 pid number is %d\n",getpid());
	printf("Fork 1.2 ppid is %d\n",getppid());	
	

	printf ("Fork 2.0 time called \n");
	fork();
	printf ("Fork 2.1 pid number is %d\n",getpid());
	printf("Fork 2.2 ppid is %d\n",getppid());	

#if 0	
	printf ("Fork 3 time called \n");
	fork();
	printf ("Fork 3 pid number is %d\n",getpid());
	printf("Fork 3 ppid is %d\n",getppid());	
#endif

}

/********************************************************************************
 * Description		:	This is to get Parent process PID by Fork function
 ********************************************************************************/

void Process6(void)
{
	int pid;
	pid = fork();

	if (pid > 0)
		printf ("Parent process PID is %d\n",pid);	
}

/********************************************************************************
 * Description		:	This is to get child process PID by Fork function
 ********************************************************************************/

void Process7(void)
{
	int pid;
	pid = fork();
	
	if (pid == 0)
		printf ("Child Process pid = %d\n",pid);
}

/********************************************************************************
 * Description		: This is to see Parent & child together
 ********************************************************************************/

void Process8(void)
{
	int pid;
	pid = fork();
	
	if (pid == 0)
	{
		printf ("I am the child,my process ID is %d\n",getpid());
		printf ("The child's parent process ID is %d\n",getppid());
	}
	else
	{
		printf ("I am the parent,my process ID is %d\n",getpid());
		printf ("The parent's parent process ID is %d\n",getppid());
	}
}

void Process8_1(void)
{
	#if 1
		int pid,cpid;
		int status;
		
		printf ("***************************************************\n");
		printf ("***************************************************\n");
			
		pid = fork();
		
		if (pid == 0)
		{
			printf ("I am the child,my process ID is %d\n",getpid());
			printf ("The child's parent process ID is %d\n",getppid());
		}
		else
		{
			printf ("I am the parent,my process ID is %d\n",getpid());
			#if 1
				cpid = wait(1);	
			#else
				do
				{
					cpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
					
					if (WIFEXITED(status)) 
					{ 
						printf("exited, status=%d\n", WEXITSTATUS(status)); 
					} 
					
				} while (!WIFEXITED(status));
			#endif
			 
			printf ("---child with pid %d died\n",cpid);
			printf ("The parent's parent process ID is %d\n",getppid());
		}
	#else

	pid_t cpid, w; 
	int status;

	cpid = fork(); 
	if (cpid == -1) 
	{ 
		perror("fork"); exit(EXIT_FAILURE); 
	}

	if (cpid == 0) 
	{ 
		/* Code executed by child */ 
		printf("Child PID is %ld\n", (long) getpid()); 
		
	} 
	else 
	{ /* Code executed by parent */ 
		do 
		{ 
			printf("****\n");
			w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
			printf("PID is = %d \n", w);  
			if (w == -1) 
			{ 
				perror("waitpid"); exit(EXIT_FAILURE); 
			}

			if (WIFEXITED(status)) 
			{ 
				printf("exited, status=%d\n", WEXITSTATUS(status)); 
			} 
			else if (WIFSIGNALED(status)) 
			{ 
				printf("killed by signal %d\n", WTERMSIG(status)); 
			} 
			else if (WIFSTOPPED(status)) 
			{ 
				printf("stopped by signal %d\n", WSTOPSIG(status)); 
			} 
			else if (WIFCONTINUED(status)) 
			{ 
				printf("continued\n"); 
			} 
		} while (!WIFEXITED(status) && !WIFSIGNALED(status)); exit(EXIT_SUCCESS); 
	}

#endif
}

/********************************************************************************
 * Description		: Understand Parent & child together
 ********************************************************************************/

void Process9(void)
{
	int i=0,j=0,pid;
	pid = fork();
	if (pid == 0)
	{
		for(i=0;i<5;i++)
			printf ("child %d\n",i);
	}
	else if (pid > 0)
	{
		for(j=9;j<14;j++)
			printf ("Parent %d\n",j);
	}
}

/********************************************************************************
 * Description		: Understand Effect of wait function in Parent process 
 ********************************************************************************/

void Process10(void)
{
	int i=0,pid;
	
	printf ("Ready to fork\n");
	pid = fork();

	if (pid == 0)
	{
		printf ("Child starts\n");	
		for(i=0;i<100;i++)
		{
			printf ("%d\t",i);
		}
		printf ("\nChild ends\n");
	}
	else
	{
		printf ("Parent process in wait state \n");
		wait(1);
		printf ("Parent process\n");	
	}
}

/********************************************************************************
 * Description		: One Parent & two children
 ********************************************************************************/

void Process11(void)
{
	int pid,dip,cpid;
	
	pid = fork();
	if (pid == 0)
	{
		printf ("1st child process ID is %d\n",getpid());
		printf ("first-child terminating from memory\n");
	}
	else
	{
		printf ("I am parent creates children\n");
		dip=fork();
		if (dip == 0)
		{
			printf ("2nd child process ID is %d\n",getpid());
			printf ("second-child terminating\n");
		}
		else
		{
			printf ("Parent creates 2nd children\n");
			cpid = wait(1);
			printf ("---child with pid %d died\n",cpid);
			cpid = wait(1);
			printf ("++++child with pid %d died\n",cpid);
			printf ("I am parent\n");
		}
	}
}

/********************************************************************************
 * Description		: Data Sharing between Parent & child
 ********************************************************************************/

void Process12(void)
{
	int pid;
	int Data = 10;
	
	pid = fork();
		
	if (pid == 0)
	{
		printf ("The initial value of Data in the child  is %d\n",Data);
		Data += 10;
		printf ("Value of Data after increment in child is %d\n",Data);
	}
	else
	{
		wait(0);
		printf ("Value on Data in parent is %d\n",Data);	
	}
}

/********************************************************************************
 * Description		: to make parent to sleep for more than one child
 ********************************************************************************/

void Process13(void)
{
	int pid,dip;
	pid = fork();

	if(pid == 0)
	{
		printf ("1st child process id is %d\n",getpid());
		printf ("First process dead\n");
	}
	else
	{
		printf ("I am parent process \n");
		dip = fork();
		if(dip == 0)
		{
			printf ("2nd child process id is %d\n",getpid());
			printf ("Second process dead\n");
		}
		else
		{
			printf ("Parent process waits  \n");
			wait(1); 
			printf ("I am parent process and i am dying\n");
		}
	}
}

/********************************************************************************
 * Description		: to make parent to sleep for more than one child
 ********************************************************************************/

void Process13_1(void)
{
	int pid,dip;
	pid = fork();

	if(pid == 0)
	{
		printf ("1st child process id is %d\n",getpid());
		printf ("First process dead\n");
	}
	else
	{
		printf ("I am parent process \n");
		dip = fork();
		if(dip == 0)
		{
			printf ("2nd child process id is %d\n",getpid());
			printf ("Second process dead\n");
		}
		else
		{
			printf ("Parent process sleeps  \n");
			sleep(1); //try with diff slep value
			printf ("Iam parent process and i am dying\n");
		}
	}
}

/********************************************************************************
 * Description		: to make parent to wait & sleep for more than one child
 ********************************************************************************/

void Process14(void)
{
	int pid,dip;
	pid = fork();

	if(pid == 0)
	{
		printf ("1st child process id is %d\n",getpid());
		printf ("First process dead\n");
	}
	else
	{
		printf ("I am parent process \n");
		dip = fork();
		if(dip == 0)
		{
			printf ("2nd child process id is %d\n",getpid());
			printf ("Second process dead\n");
		}
		else
		{
			printf ("I am new ---- parent process \n");
			sleep(11);
			//sleep(); dont use this 
			printf ("Child with pid %d died\n",wait(1)); // with wait(0);
			printf ("Iam parent process and i am dying\n");
		}
	}
}

/*******************************************************************************
 * Description		: Create Zombie process with two child
 ********************************************************************************/

void Process15(void)
{
	int pid,dip;
	
	printf ("Parent PID  process is %d\n",getpid());
	pid = fork();
	
	if(pid == 0)
	{
		printf ("1st child process is %d\n",getpid());
		printf ("first-child terminating\n");
	}
	else
	{
		printf ("I am parent\n");
		dip = fork();
		if (dip == 0)
		{
			printf ("2nd child process is %d\n",getpid());
			printf ("second-child terminating\n");
		}
		else 
		{	printf ("I am new parent\n");
			printf ("Child with pid %d died\n",wait(0));
			printf ("Child again with pid %d died\n",wait(0));
			printf ("I am parent going to sleep forever\n");
			sleep(1);
			printf ("BYE !!!!\n");
		}
	}
}

/********************************************************************************
 * Description		: orphan process
 ********************************************************************************/

void Process16(void)
{
	int pid;
	pid = fork();

	if (pid == 0)
	{
		printf ("I am the child process,my process id is %d\n",getpid());
		printf ("The child's parent process id is %d\n",getppid());
		sleep(3);
		printf ("I am the child process,my process id is %d\n",getpid());
		printf ("The child's parent process id is %d\n",getppid());
	}
	else
	{
		printf ("I am the parent process,my process id is %d\n",getpid());
		printf ("The parents parent process id is %d\n",getppid());
	}
}

/********************************************************************************
 * Description		: Create Zombie Process with one child
 ********************************************************************************/

void Process17(void)
{
	int pid;

	printf ("Parent PID Process is %d\n",getpid());
	pid = fork();

	if (pid > 0)
	{
		sleep(50);
	}
	else
	{
		exit(0);
	}
	return;
}


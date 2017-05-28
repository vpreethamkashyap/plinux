/* **********************************************************************************
 * **********************************************************************************
 * Function Name : 	IPC_Pipe_Test
 * Description:			This file contains description about pipes
 * 									Pipes can be tested in two ways  
 * 									1. Either we can combine the two commands
 * 											output of command 1 used by 2 command.
 * 
 * 									2. Or we can create two pipes where we can
 * 										 communicate from two file descriptor								
 * 											1 for read & write.
 * **********************************************************************************
 * **********************************************************************************
*/

# include <stdio.h>

void IPC_Pipe_Test(void);
void TestPipeByProcessModel(void);
void TestPipeByClinetSeverModel(void);

int main()
{
	IPC_Pipe_Test();
}

void IPC_Pipe_Test(void)
{
	printf("\nHi Usr You are going to Test TestPipeByProcessModel \n");	
	TestPipeByProcessModel();
	
	printf("**************\n***************\n****************\n");	
	printf("\nHi Usr You are going to Test TestPipeByClinetSeverModel \n");	
	TestPipeByClinetSeverModel();
}

/* **********************************************************************************
 * **********************************************************************************
 * Function Name : 	TestPipeByProcessModel
 * Description:			This function combines the command set and give the result
 * 									ls | wc -l
 * **********************************************************************************
 * **********************************************************************************
*/
void TestPipeByProcessModel(void)
{
	// Always Remember for this model we will use file pointer
	
	FILE *pipein_fp, *pipeout_fp;
	char readbuf[80];

	printf("This function combines the command set and give the result \n");	
	printf("\nThis is the command which we r going to test ls| wc -l \n");
	
	//Create one way pipe line with call to popen() 	
	if((pipein_fp = popen("ls", "r")) == NULL)
	{
		perror("popen");
		exit(1);
	}
	// Create one way pipe line with call to popen() 
	if((pipeout_fp = popen("wc -l", "w")) == NULL)
	{
		perror("popen");
		exit(1);
	}
	//Processing loop
	/*content of pipein_fp is put into	readbuf */
	while(fgets(readbuf, 80, pipein_fp))
			fputs(readbuf, pipeout_fp);/* content of readbuf is put into pipeout_fp*/

	/* Close the pipes */
	pclose(pipein_fp);
	pclose(pipeout_fp);
	return(0);
}

/* **********************************************************************************
 * **********************************************************************************
 * Function Name : 	TestPipeByClinetSeverModel
 * Description:			This function create pipe though which two process communicates
 * 									 	
 * **********************************************************************************
 * **********************************************************************************
*/
void TestPipeByClinetSeverModel(void)
{
	int 	pipefd[2], n;
	char	buff[100] = "fgdfg";
	
	printf("This function create pipe though which two process communicates \n");
	
	if(pipe(pipefd) < 0)
		perror("filed in openning pipe\n");
	
	printf("read fd = %d, write fd = %d\n",pipefd[0],pipefd[1]);
	//Creating the child
	if(fork() == 0)
	{	
		//Child closes read discriptor 
		printf("Child closes read discriptor\n");
		close(pipefd[0]);	
		//Child writes to pipe descriptor
		if(write(pipefd[1],"hello world.....I am child!",26)!= 16)
			perror("Child filed in writing pipe\n");

		//Child closes write discriptor 
		printf("Child writes to pipe descriptor\n");
		close(pipefd[1]);	
	}
	else
	{
		puts("I am parent going to create my child\n");
	
		// Parent closes write discriptor 
		printf("Parent closes write discriptor\n");
		close(pipefd[1]);	
		wait(1);
		printf("\nParent reads from read descriptor\n");
		if((n = read(pipefd[0],buff,100)) < 0)
			perror("filed in writing pipe\n");
		//Write to stdout
		write(1,buff, n);	
		printf("\nParent closes read discriptor \n");
		close(pipefd[0]);
		close(pipefd[1]);	
		_exit(0);
	}	
}



/*****************************************************************************
Module name: server.c
Description: fifo is created and opened for read mode this process will be
	     waiting in block mode.
# written to use as  program to ipc using fifo
******************************************************************************/

# include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#define  FIFO_FILE	"myfifo"
void IPC_Fifo_Server_Test(void);

int main(void)
{
	printf("Hi Usr You are going to Test IPC FIFO as Server\n");
	IPC_Fifo_Server_Test();
}

void IPC_Fifo_Server_Test(void)
{
	FILE	*fp;
	char	buff[1024];

	if(mkfifo(FIFO_FILE,0666) == -1)
		perror("In server mkfifo");

	fp = fopen(FIFO_FILE,"r");
	fgets(buff,80,fp);
	printf("Server recived string  %s\n",buff);
	fclose(fp);
}


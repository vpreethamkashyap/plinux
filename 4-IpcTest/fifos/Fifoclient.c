/**************************************************************************
	Program name: cllient.c
	Description: Thic clien opens fifo for write mode and puts some data 
		     into fifo. server which is waiting in the back ground 
		     read from fifo and prints the read contents to stdout
# written to use as  program to ipc using fifo
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define  FIFO_FILE	"myfifo"
void IPC_Fifo_ClientTest(void);

int main(void)
{
	printf("Hi Usr You are going to Test IPC FIFO as Client\n");
	IPC_Fifo_ClientTest();
}
void IPC_Fifo_ClientTest(void)
{
	FILE	*fp;
	char Buf[100] ="Client is filling FIFO";

	if((fp = fopen(FIFO_FILE,"a")) == NULL){
		printf("client: file open error\n");
		exit(1);
	}
	
	if(fputs(&Buf,fp)== NULL)
		perror("error");
	
	fclose(fp);
}

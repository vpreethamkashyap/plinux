/* This program illustrates how a shared memory segment attatched and how data is written to the shared memory segment*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SEGSIZE 100

int main(void)
{
	int shmid,pos;
	char *msg;
	key_t key;
	printf("\n****************************************** \n");
	printf(" You are in shared memory write function \n");
	printf("****************************************** \n");
	
	printf("Create unique key via call to ftok() \n");
	key = ftok(".", 'S');
       
	printf("Creating new shared memory segment\n");  
	if((shmid=shmget(key,SEGSIZE,IPC_CREAT|0666))==-1) 
	{
		perror("shmget");
		exit(1);
	}
	msg=shmat(shmid,0,0);
	printf("Enter the data you want to write into shared memory\n");	
	fgets(msg,SEGSIZE,stdin);
	pos = strlen(msg);
	strcpy(msg+pos-1,"world");
	printf("Data successfully written\n");
	shmdt(msg);
}

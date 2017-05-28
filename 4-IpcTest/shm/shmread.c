/* This program illustrates how a data is read from a shared memory segment*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SEGSIZE 100

int main(void)
{
	int shmid;
	char *msg;
	key_t key;

	printf("\n****************************************** \n");
	printf(" You are in shared memory read function \n");
	printf(" ****************************************** \n");
		
	printf("Create unique key via call to ftok() \n");
	key = ftok(".", 'S');	

	printf("Sharring shared memory segment\n");  
	if((shmid=shmget(key,SEGSIZE,IPC_CREAT|0666))==-1) 
	{
		perror("shmget");
		exit(1);
	}
	
	msg=shmat(shmid,0,0);
	printf("\nData written in the shared memory is:%s\n",msg);	
	shmdt(msg);
}
	
	

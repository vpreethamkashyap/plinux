/*************************************************************
                          semget.c  -  description
                                    -------------------
           begin                : Wed Jul 23 2003
***************************************************************/
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

main()
{
	int semid;
	printf(" Creating a semaphore\n");
	semid = semget(1117,1,0644|IPC_CREAT);
	if(semid < 0)
	{
		perror("semget");
		_exit(0);
	}
	printf("Semaphore successfully got\n");
	printf(" Execute ipcs for status\n");
	semctl(semid,0,SETVAL,1);
}	

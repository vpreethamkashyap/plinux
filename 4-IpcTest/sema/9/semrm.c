/***************************************************************
                          semrm.c  -  description
                                    -------------------
           begin                : Wed Jul 23 2003
*****************************************************************/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>

main()
{
	int semid;
	semid = semget(1112,1,0644);
	semctl(semid,0,IPC_RMID,0);
	printf(" Semaphore removed\n");
}	

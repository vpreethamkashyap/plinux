/*************************************************************************
 Program name:    semget1.c   
 Description : setting the sem value using semctl()
*********************************************************************** **/
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

main()
{
	int semid,retval;
        int value=5;  
        int semnum=0;
        int cnt=1;
	printf(" Creating a semaphore\n");
	semid = semget(12,cnt,0777|IPC_CREAT);
	if(semid < 0)
	{
		perror("semget");
		exit(0);
	}
	printf("Semaphore successfully got\n");
        retval=semctl( semid,semnum,GETVAL,0);
        printf("%d\n",retval);

        semctl( semid,semnum,SETVAL,value);

        retval=semctl( semid,semnum,GETVAL,0);
        printf("%d\n",retval);
        //semctl( semid,semnum,IPC_RMID,0);
   
}	

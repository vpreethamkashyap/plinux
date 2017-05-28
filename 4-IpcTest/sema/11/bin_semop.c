/***************************************************************************
                          semop.c  -  description
                                    -------------------
           begin                : Wed Jul 23 2003
version : 2.1
*****************************************************************/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>

struct sembuf s1[2]={0,0,0,
		    0,1,0};

struct sembuf s2[1]={0,-1,0};
main()
{
	int semid,val;
	semid = semget(1112,1,0644|IPC_CREAT);
	int ctr;

	semop(semid,s1,2);

	//Critical region
	for(ctr =0 ; ctr < 500000000; ctr ++); //Busy doing
	val = semctl(semid,0,GETVAL,0);
	printf("The sem value is changed to %d\n",val);

	//End of Critical region
	semop(semid,s2,1);
}	

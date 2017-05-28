#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>

struct sembuf s1[1]={0,-1,0};
struct sembuf s2[1]={0,1,0};
main()
{
	int ctr;
	int semid,val;

	semid = semget(1112,1,0644|IPC_CREAT);

	val = semctl(semid,0,GETVAL,0);

	semop(semid,s1,1);
	//Critical region
	printf("I am in critical region\n");
	for(ctr =0 ; ctr < 500000000; ctr ++); //Busy doing
	val = semctl(semid,0,GETVAL,0);
	printf("The sem value is changed to %d\n",val);
	sleep(15);
	//End of Critical region

	semop(semid,s2,1);

	val = semctl(semid,0,GETVAL,0);
	printf("I am out of critical region\n");
	//val = semctl(semid,0,IPC_RMID,0);
}	


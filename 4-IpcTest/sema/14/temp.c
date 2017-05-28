#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
union semun {
   int val;                  /* value for SETVAL */
   struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
   unsigned short *array;    /* array for GETALL, SETALL */
                                     /* Linux specific part: */
   struct seminfo *__buf;    /* buffer for IPC_INFO */
};

main()
{
	int ctr;
	union semun obj;
	obj.val = 1;
	int semid,val;

	semid = semget(1112,1,0644|IPC_CREAT);

	semctl(semid,0,SETVAL,obj);

	sleep(1000);
	//End of Critical region

	val = semctl(semid,0,IPC_RMID,0);
}	


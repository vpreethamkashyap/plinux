/*************************************************************************
 program name :  semgetall.c  
 description  :
                                
*********************************************************************** **/
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

main()
{
	int semid,retval;
        int value=1;  
        int semnum=0;
        int cnt=3;
        int key=31; 
        char ch;
        static ushort val[3]={0,1,2},val1[3]; 
	printf(" Creating a semaphore\n");
	semid=semget(key,cnt,0777|IPC_CREAT);
	if(semid < 0)
	{
		perror("semget");
		exit(0);
	}
	printf("Semaphore successfully got\n");
	printf("getting the values ofsem %d\n sem1:%d\n sem2:%d\n sem3:%d \n"\
	,semid,val1[0],val1[1],val1[2]);         
        semctl( semid,semnum,GETVAL,val1);
        printf("setting values for sems\n");  
        semctl( semid,0,SETALL,val);
        semctl( semid,0,GETALL,val1);
  	printf("getting the values ofsem %d\n sem1:%d\n sem2:%d\n sem3:%d \n"\
	,semid,val1[0],val1[1],val1[2]);         
	printf("\n want remove sem %d\n(y/n):",semid);
        ch=getchar();
        if(ch=='y'){
        	printf("removing semophore\n"); 
       		semctl( semid,0,IPC_RMID,0);
}	}

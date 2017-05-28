/*****************************************************************************
	MODULE: semstat.c
	Description : union semun is not present in sys/sem.h file so here,
	 	    I created a union semun.(more details see man semctl.
 		    A companion command line tool for the semtool package.
		    semstat displays the current value of all semaphores 
		    in the set created by semtool.
		    (semtool is another program in this directory).
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun{
	int  val;
	struct semid_ds	*buf;
	unsigned short *array;

	struct	seminfo *__buf;
};

int get_sem_count(int sid);
void show_sem_usage(int sid);
int get_sem_count(int sid);
void dispval(int sid);

int main()
{
        key_t key;
        int   semset_id;

        /* Create unique key via call to ftok() */
        key = ftok(".", 'v');

        /* Open the semaphore set - do not create! */
	/* done some changes here (intentionally I am creating it*/
        if((semset_id = semget(key, 1, IPC_CREAT|0666)) == -1) 
        {
                printf("Semaphore set does not exist\n");
                exit(1);
        }

        show_sem_usage(semset_id); 
	dispval(semset_id);
        return(0);
}

void show_sem_usage(int sid)
{
        int cntr=0, maxsems, semval;

        maxsems = get_sem_count(sid);

        while(cntr < maxsems) {
                semval = semctl(sid, cntr, GETVAL, 0);
                printf("Semaphore #%d: --> semaphore value:%d\n", cntr, semval);
                cntr++;
        }
}

int get_sem_count(int sid)
{
        int rc;
        struct semid_ds mysemds;
        union semun semopts;

        /* Get current values for internal data structure */
        semopts.buf = &mysemds;

        if((rc = semctl(sid, 0, IPC_STAT, semopts)) == -1) {
                perror("semctl");
                exit(1);
        }

        /* return number of semaphores in set */
        return(semopts.buf->sem_nsems);
}

void dispval(int sid)
{
        int semval;

        semval = semctl(sid, 0, GETVAL, 0);
        printf("semval is %d\n", semval);
}
 

 
  

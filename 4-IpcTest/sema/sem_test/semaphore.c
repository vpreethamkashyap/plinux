# include <stdio.h>
# include <sys/sem.h>
# include <sys/types.h>
# include <sys/ipc.h>


# define BIGCOUNT	10000

static struct sembuf 	op_lock[2]={
			2, 0, 0,
			2, 1, SEM_UNDO
			};	
	
static struct sembuf 	op_endcreate[2]={
			1, -1, SEM_UNDO,
			2, -1, SEM_UNDO
			};

static struct sembuf	op_open[1] = {
			1, -1, SEM_UNDO 
			};

static struct sembuf	op_close[3] = {
			2, 0, 0,
			2, 1, SEM_UNDO,
			1, 1, SEM_UNDO,
			};

static struct sembuf	op_unlock[1] = { 2, -1, SEM_UNDO };

static struct sembuf	op_op[1] = { 0, 99, SEM_UNDO };

int sem_create(key_t	key, int initval)
{
	int    id, semval;
	union semun{
		int 	val;
		struct	semid_ds	*buf;
		ushort	*array;
	} semctl_arg;
	if(( id = semget(key, 3, 0600 | IPC_CREAT)) < 0)
		return -1;
	if(semop(id,&op_lock[0], 2) < 0)
		perror("semop error\n");
	if((semval = semctl(id , 1, GETVAL, 0)) < 0)
		perror("semctl error\n");
	if(semval == 0){
		semctl_arg.val = initval;
		if( semctl(id , 0, SETVAL, semctl_arg) < 0)
			perror("semctl error\n");

		semctl_arg.val = BIGCOUNT;
		if( semctl(id , 1, SETVAL, semctl_arg) < 0)
			perror("semctl error\n");
	}
	if(semop(id,&op_endcreate[0], 2) < 0)
		perror("semop fail\n");
	return id; 
	
}

int 	sem_open(key_t key)
{
	int    id;
	if((id = semget(key, 3, 0)) < 0)
		perror("sem get error\n");
	if(semop(id, &op_open[0], 1) < 0)
		perror("semop fail\n");
	return id;
}

int sem_rm(key_t id)
{
	if(semctl(id, 0, IPC_RMID, 0) < 0)
		perror("Can't ipc_rmid\n");
}

int sem_close(int id)
{
	int  semval;
	if(semop(id,&op_close[0], 3) < 0 )	
		perror("semop failed\n");
	
	if((semval = semctl(id,1, GETVAL,0)) < 0)
		perror("semctl failed\n");
	if(semval > BIGCOUNT)
		perror("semctl error\n");
	else if(semval == BIGCOUNT)
		sem_rm(id);
	else
		if(semop(id, &op_unlock[0], 1) < 0)
			perror("can't unlock");
}

int sem_wait(int id)
{
	sem_op(id, -1);
}

int sem_signal(int id)
{
	sem_op(id,1);
}

int sem_op(int id, int value)
{
	if( ( op_op[0].sem_op = value) == 0)
		perror("can't have value 0\n");
	if(semop(id, &op_op[0], 1) < 0)
		perror("sem_op error\n");
}		

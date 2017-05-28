# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

# define SEMKEY   123456L
# define PERMS	  0666

# define SEQFILE  "seqfile"
# define MAXBUF   100

static struct sembuf	op_lock[2] = { 0,0,0,
				       0,1,SEM_UNDO
				       };

static struct sembuf	op_ulock[1] = { 0,-1,(IPC_NOWAIT | SEM_UNDO) };
int semid = -1;

void my_unlock(void);
void my_lock(void);

main()
{
	int    fd, i , n, pid,   seqno;
	char 	buff[MAXBUF];
	int ctr;
	pid = getpid();
	if( (fd = open(SEQFILE, 2)) < 0)
		perror("cant open %s",SEQFILE);

	my_lock();
	for(i = 0; i < 100 ; i ++){
		lseek(fd , 0, 0);
		for(ctr = 0; ctr <91000;ctr ++); //By being busy I am wasting time
		if( (n  = read(fd, buff,MAXBUF)) <= 0)
			perror("read error\n");
		buff[n] = '\0';
		for(ctr = 0; ctr <91000;ctr ++); // To keep busy

		if((n = sscanf(buff," %d\n",&seqno))!=1)
			perror("sscanf error\n");
		printf("pid# %d,seqno# %d  ",pid,seqno);

		for(ctr = 0; ctr <91000;ctr ++); // Just for fun to keep busy
		seqno++;

		sprintf(buff, "%03d\n" , seqno);
		n = strlen(buff);
		for(ctr = 0; ctr <91000;ctr ++);
		lseek(fd, 0, 0);
		if(write(fd, buff , n)!= n)
			perror("write error\n");
		for(ctr = 0; ctr <91000;ctr ++);
	}
	my_unlock();
}

void my_lock(void)
{
	if( semid < 0){
		if( (semid = semget(SEMKEY,1,IPC_CREAT | PERMS)) < 0)
			perror("semget error\n");
	}
	if(semop(semid, &op_lock[0],2) < 0)
		perror("semop lock error\n");
}

void my_unlock(void)
{
	if(semop(semid, &op_ulock[0],1) < 0)
		perror("semop unlock error\n");
}

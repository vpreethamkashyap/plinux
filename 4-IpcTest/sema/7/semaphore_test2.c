/* incomplete */


# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>

# define SEQFILE	"seqfile"
# define MAXBUF		100
# define SEMKEY		12345L

main()
{
	int 	fd, i ,pid, seqno , n, semid;
	char	buff[MAXBUF + 1];
	
	int my_lock(int );
	int my_unlock(int );

	pid = getpid();
	if((fd = open(SEQFILE, O_RDWR)) < 0)
		fprintf(stderr,"can't open SEQFILE\n");

	if( (semid = sem_creat(SEMKEY, 1)) < 0)
		fprintf(stderr,"can't open Semaphore\n");

	for(i = 0;i < 20;i++)
	{
		sem_wait(semid);
		lseek(fd, 0L, 0);
	
		if((n=read(fd, buff, MAXBUF)) <= 0)
			fprintf(stderr,"read error\n");
		buff[n] = '\0';

		if((n = sscanf(buff,"%d\n",&seqno)) !=1)
			fprintf(stderr,"sscanf error\n");
		printf("pid = %d, seqno = %d",pid, seqno);
		seqno ++;

		sprintf(buff, "%03d\n", seqno);
		n = strlen(buff);
		lseek(fd,0L, 0);
		if((write(fd, buff ,n))!= n)
			fprintf(stderr,"write error\n");
		sem_signal(semid);
	}
	sem_close(semid);
}
/*
sem_wait(int   id)
{
	sem_op(id, -1);
}
sem_close(int id)
{
	register int semval;
	if( semop(id,&op_close[0],3) < 0) 
*/

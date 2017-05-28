# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

# define SEMKEY   123456L
# define PERMS	  0666

# define SEQFILE  "seqfile"
# define MAXBUF   100

main()
{
	int    fd, i , n, pid,   seqno, semid;
	char 	buff[MAXBUF];
	
	pid = getpid();
	if( (fd = open(SEQFILE, 2)) < 0)
		perror("cant open %s",SEQFILE);

	if((semid = sem_create(SEMKEY , 1)) < 0)
		perror("sem_create error\n");

	for(i = 0; i < 20 ; i ++){
		sem_wait(semid);
		lseek(fd , 0, 0);
		if( (n  = read(fd, buff,MAXBUF)) <= 0)
			perror("read error\n");
		buff[n] = '\0';

		if((n = sscanf(buff," %d\n",&seqno))!=1)
			perror("sscanf error\n");
		printf("pid# %d,seqno# %d  ",pid,seqno);

		seqno++;

		sprintf(buff, "%03d\n" , seqno);
		n = strlen(buff);
		lseek(fd, 0, 0);
		if(write(fd, buff , n)!= n)
			perror("write error\n");
		sem_signal(semid);
	}
	sem_close(semid);
}


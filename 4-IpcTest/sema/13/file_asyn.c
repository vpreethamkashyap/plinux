# include <stdio.h>
# include <sys/types.h>

# define SEQFILE  "seqfile"
# define MAXBUF   100

main()
{
	int    fd, i ,ctr, n, pid,   seqno;
	char 	buff[MAXBUF];
	
	pid = getpid();
	if( (fd = open(SEQFILE, 2)) < 0)
		perror("cant open SEQFILE");

		my_lock();
	for(i = 0; i < 100 ; i ++){
		lseek(fd , 0, 0);
		for(ctr = 0; ctr <91000;ctr ++);
		if( (n  = read(fd, buff,MAXBUF)) <= 0)
			perror("read error\n");
		buff[n] = '\0';

		for(ctr = 0; ctr <91000;ctr ++);

		if((n = sscanf(buff," %d\n",&seqno))!=1)
			perror("sscanf error\n");
		printf("pid# %d,seqno# %d\t",pid,seqno);
		for(ctr = 0; ctr <91000;ctr ++);

		seqno++;

		sprintf(buff, "%03d\n" , seqno);
		n = strlen(buff);
		lseek(fd, 0, 0);
		for(ctr = 0; ctr <91000;ctr ++);
		if(write(fd, buff , n)!= n)
			perror("write error\n");
		for(ctr = 0; ctr <9100;ctr ++);
	}
		my_unlock();
}



my_lock()
{
	return;
}

my_unlock()
{
	return;
}

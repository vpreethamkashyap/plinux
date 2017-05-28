#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
main ()
{
	unsigned int nhost = 0xd04c,nnetwork;
	unsigned char *p;

	p = (unsigned char *)&nhost;
	
	printf ("%x %x\n",*p,*(p+1));
	nnetwork = htons(nhost);
		
	p = (unsigned char *)&nnetwork;
	printf ("%x %x\n",*p,*(p+1));
}

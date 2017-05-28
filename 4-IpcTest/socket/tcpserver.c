/*This is a simple sequential server program which receives message at port 1034 ans sends the message to desired client*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define MYPORT 1034

void main(void)
{
	int sd,pid,nsd,dat,yes=1;
	char message[40];
	struct sockaddr_in server,client;
	socklen_t length;
	if((sd=socket(PF_INET,SOCK_STREAM,0))==-1) 
	{
		perror("socket");
		exit(1);
  }  
	server.sin_port=htons(MYPORT);
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");     
 	
	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1) 
	{
		perror("setsockopt");
		exit(1);
	}	        	  
	
	if(bind(sd,(struct sockaddr  *)&server,sizeof(server))==-1) 
	{
		perror("bind");
		exit(1);
	}

	if(listen(sd,5)==-1) 
	{
		perror("listen");
		exit(1);
	} 
	printf("Waiting for connection.............\n");    

	if((nsd=accept(sd,(struct sockaddr *)&client,&length))==-1) 
	{
		perror("accept");
		exit(1);
	 }   	   
	printf("Got connection from client:%s\n",inet_ntoa(client.sin_addr));
          
	while(1)
	{       
		if((dat=recv(nsd,message,40,0))==-1) 
		{
			perror("recv");
			exit(1);
		}
		message[dat]='\0';
		printf("Data received is : %s\n",message);
	}
	message[dat]='\0';
	printf("Data received is : %s\n",message);
	printf("Enter the data you want to send to client\n");
	fgets(message,40,stdin); 
	printf("Enter the data transmitting to client\n");
	send(nsd,message,40,0);
	close(sd); 
}

    
    
     

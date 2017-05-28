/*This is a simple UDP client socket which sends the message to the udpserver and receives the message from server*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>   

#define PORT 1034

main()
{
	int n,sd,length;
	char msg[40];
	struct sockaddr_in server,client;
	if((sd=socket(PF_INET,SOCK_DGRAM,0))==-1) {
		perror("socket");
		exit(1);
	}

	client.sin_family=PF_INET;
	client.sin_port=htons(PORT);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");

        printf("Enter the message you want to send to server\n");
        fgets(msg,40,stdin);
        if(sendto(sd,msg,40,0,(struct sockaddr *)&client,sizeof(server))==-1) {
		perror("sendto");
		exit(1);
	}
	printf("Waiting for message from server..............\n");
	length=sizeof(client);
	n=recvfrom(sd,msg,40,0,(struct sockaddr *)&server,&length);
	msg[n]='\0';
	
	printf("Message received from server is:%s\n",msg);
	
}
			
	

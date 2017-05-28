/* This is a simple program illustrating the UDP sockets which receives the message from client and sends the message to same client*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MYPORT 1034


main()
{
	int sd,nsd,dat,length,yes=1;
        char message[40];
        struct sockaddr_in server,client;

	if((sd=socket(PF_INET,SOCK_DGRAM,0))==-1) {
	    				     perror("socket");
            				     exit(1);
        }
	server.sin_port=htons(MYPORT);
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
     
/*	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1) {
	     		  perror("setsockopt");
	        	  exit(1);
	}*/
	 
	if(bind(sd,(struct sockaddr  *)&server,sizeof(server))==-1) {
	      		  perror("bind");
                 	  exit(1);
        }
      
        length=sizeof(client);
       	if((dat=recvfrom(sd,message,40,0,(struct sockaddr *)&client,&length))==-1) {
		perror("recvfrom");
		exit(1);
	}
    
	printf("Got connection from client:%s\n",inet_ntoa(client.sin_addr));
          
        
        message[dat]='\0';
	 	  
	printf("Data received is : %s\n",message);
	printf("Enter the data you want to send to client\n");
        fgets(message,40,stdin); 
        sendto(sd,message,40,0,(struct sockaddr *)&client,length);
}  
    
    
     


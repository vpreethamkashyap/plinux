/* This is a program which illustrates the concurrent server by creating a child process */
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MYPORT 1034


main()
{
	int pid,sd,nsd,dat,yes=1;
        char message[40];
	socklen_t length;
        struct sockaddr_in server,client;

	if((sd=socket(PF_INET,SOCK_STREAM,0))==-1) {
	    				     perror("socket");
            				     exit(1);
        }
	server.sin_port=htons(MYPORT);
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("192.168.2.20");
     

	 
	if(bind(sd,(struct sockaddr  *)&server,sizeof(server))==-1) {
	      		  perror("bind");
                 	  exit(1);
        }

		
      
       if(listen(sd,1)==-1) {
	     	perror("listen");
	       exit(1);
	} 

                /*A child process is created for accepting connections*/
		
			printf("Waiting for connection.............\n");      
		
	
		pid=fork();
		while(1)
		{
		if(pid==0)
		{

     	if((nsd=accept(sd,(struct sockaddr *)&client,&length))==-1) {
			perror("accept");
			exit(1);
	        	    }
			
       	   
    			printf("Got connection from client:%s\n",inet_ntoa(client.sin_addr));
                       /*else fragment is the parent process taking care                                of send and receive to clients*/
       			   if((dat=recv(nsd,message,40,0))==-1) {
			   perror("recv");
			   exit(1);
			   }
                
        		message[dat]='\0';
	 	  
			printf("Data received is : %s\n",message);
			printf("Enter the data you want to send to client\n");
        		fgets(message,40,stdin); 
        		send(nsd,message,40,0);
		    }	
             }
	//close(sd);
}		       
    
    
     

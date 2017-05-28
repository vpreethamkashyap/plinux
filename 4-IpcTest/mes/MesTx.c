#include <stdio.h>
#include <stdlib.h>
#include <linux/ipc.h>
#include <linux/msg.h>

struct mymsgbuf 
{
	 long    	mtype;          // Message type 
	 int     	request;        // Work request number 
	 char 		MesTxBuf[30];   // info
}msg;

int send_message( int , struct mymsgbuf *);

int main(void)
{
	int    qid;
	key_t  msgkey;
	
	printf("\nMessage Transmission test \n");	
	printf("Generate our IPC key value \n");
	msgkey = ftok(".", 'm');

	printf("Open or create the Message queue\n");
	if((qid = msgget( msgkey, IPC_CREAT | 0660 )) == -1)
	{
		printf("Error in Open or create the queue\n");
		return(-1);
	}

	printf("Load up the message with arbitrary test data \n");
	msg.mtype   = 1;        							// Message type must be a positive number!    
	msg.request = 1;        							// Data element #1 
	strcpy(msg.MesTxBuf,"I am message Transmitter");  	// Data element #2 (my yearly salary!) 	

	if((send_message( qid, &msg )) == -1) 
	{
		perror("send_message");
		exit(1);
	}
	printf("Successfully Message transmitted \n");
}

int send_message( int qid, struct mymsgbuf *qbuf )
{
	int result, length;

	// The length is essentially the size of the structure minus sizeof(mtype) 
	length = sizeof(struct mymsgbuf) - sizeof(long);        

	printf("Message transmitting \n");
	if((result = msgsnd( qid, qbuf, length, 0)) == -1)
	{
		printf("Error in sending message \n");
		return(-1);
	}	
	return(result);
}


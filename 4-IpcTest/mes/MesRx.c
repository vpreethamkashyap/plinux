/***********************************************************************
 	program name: 	rcv_message.c.c
 	Description : A command line tool for tinkering with SysV 
			style Message Queues
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf 
{
	long    mtype;     			// Message type 
	int     request;   			// Work request number 
	char 	MesRxBuf[30];   	// info 
} msg;

void remove_queue(int qid);
void change_queue_mode(int qid, char *mode);
void read_message(int qid, struct mymsgbuf *qbuf, long type);

int main()
{
	key_t key;
	char	choice;
	int   msgqueue_id;
	struct mymsgbuf qbuf;

	printf("A utility for tinkering with msg queues\n");
	printf("A utility for (r)ecv <type>\n");
	printf("A utility for (d)elete\n");
	printf("A utility for (m)ode <octal mode>\n");     
	printf("enter u'r choice\n");
	scanf("%c",&choice);
	
	printf("Create unique key via call to ftok() \n");
	key = ftok(".", 'm');

	printf("Open the queue - create if necessary  \n");
	if((msgqueue_id = msgget(key, IPC_CREAT|0660)) == -1) 
	{
		printf(" msgget qid Error\n");
		perror("msgget");
		exit(1);
	}

	switch(choice)
	{
		case 'r': 
			read_message(msgqueue_id, &qbuf, 1); 
		break;
		case 'd': 
			remove_queue(msgqueue_id); 
		break;        
		case 'm': 
			change_queue_mode(msgqueue_id, "0600"); 
		break;
		default: 
			printf(" Sorry This option is not present\n");
		break;
	}
	return(0);
}

void read_message(int qid, struct mymsgbuf *qbuf, long type)
{
	printf("Reading a message ...\n");
	msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);	
	printf("Type: %ld Text: %s\n", qbuf->mtype, qbuf->MesRxBuf);
}

void remove_queue(int qid)
{
	printf("Remove the queue \n");
	msgctl(qid, IPC_RMID, 0);
}

void change_queue_mode(int qid, char *mode)
{
	struct msqid_ds myqueue_ds;
	printf("Get current info \n");
	msgctl(qid, IPC_STAT, &myqueue_ds);
	printf("Convert and load the mode \n");
	sscanf(mode, "%ho", &myqueue_ds.msg_perm.mode);
	printf("Update the mode \n");
	msgctl(qid, IPC_SET, &myqueue_ds);
}


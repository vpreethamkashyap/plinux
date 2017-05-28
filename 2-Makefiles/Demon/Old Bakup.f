/* NIRMITSU TECHNOLOGIES PVT LTD, BANGALORE */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "SerialComPort.h"

/********************************************************************************************
			Function Declarations
*********************************************************************************************/
void CheckEndOfTest(void);
void DisplayMessage(void);
/********************************************************************************************
			Variable Declarations
*********************************************************************************************/

char RxBuf[100];
char TxBuf[30];
char TempBuf[5];
char LoopCase = 0;
char BMITest = 0;
char BPITest = 0;
char BLITest = 0;

/********************************************************************************************
			Main Starts Here
*********************************************************************************************/

int main(int argc, char **argv[]){

	int baud,i=0,Length=0,fd;;
	char cbuf;
  	FILE *pFile;

	if(argc < 2) {
		printf("please input proper arguments");
		return -1;
 	}
	fd = nu_SerialComPort_Open(argv[1]);
	if(fd < 0) {
	   	printf("Error opening device");
		   return -2;
	}
	baud = atoi(argv[2]);
	if(nu_SerialComPort_Init(fd, baud) < 0 ){
		printf("baud not set");
		return -3;
	} 
	
	DisplayMessage();
	while(1){
		switch(LoopCase){
			case 0:
				scanf("%c",&cbuf);
				printf("You have entered the Option No %c \n",cbuf);
				strcat(TxBuf,"#BMI");
				printf("Please Enter Your Hight in cms in 3 Letters\n");
				scanf("%s",&TempBuf);
				strcat(TxBuf,"@");
				strcat(TxBuf,TempBuf);
				strcat(TxBuf,"$");
				write(fd,TxBuf,20);
				memset(TxBuf,0,30);
				memset(TempBuf,0,5);
				LoopCase = LoopCase +1;
			break;
			case 1:
            while(read(fd,RxBuf, 100) > 0) {
              	printf("%s",RxBuf);
					CheckEndOfTest();
					memset(RxBuf,0,100);
				}			
			break;
			case 2:
				scanf("%c",&cbuf);
				printf("You have entered the Option No %c \n",cbuf);
				strcat(TxBuf,"#BPI");
				strcat(TxBuf,"@");
				strcpy(TempBuf,"NNN");
				strcat(TxBuf,TempBuf);
				strcat(TxBuf,"$");
				write(fd,TxBuf,20);
				memset(TxBuf,0,30);
				memset(TempBuf,0,5);
				LoopCase = LoopCase +1;
			break;
			case 3:
       		while(read(fd,RxBuf, 100) > 0) {
       	      printf("%s",RxBuf);
					CheckEndOfTest();
					memset(RxBuf,0,100);
				}			
			break;
			case 4:
				scanf("%c",&cbuf);
				printf("You have entered the Option No %c \n",cbuf);
				strcat(TxBuf,"#BLI");
				if(BMITest != 1){
					printf("Please Enter Your Weight in Kgs in 3 Letters\n");
					scanf("%s",&TempBuf);
				}
				else{
					strcpy(TempBuf,"NNN");
				}
				strcat(TxBuf,"@");
				strcat(TxBuf,TempBuf);
				strcat(TxBuf,"$");
				write(fd,TxBuf,20);
				memset(TxBuf,0,30);
				memset(TempBuf,0,5);
				LoopCase = LoopCase + 1;
			break;
			case 5:
            while(read(fd,RxBuf, 100) > 0) {
               printf("%s",RxBuf);
					CheckEndOfTest();
					memset(RxBuf,0,100);
				}			
			break;
			default:
			break;
		}
	}

/*
	while(1){
		memset(buf,0,5);
      while(read(fd, buf2, 100) > 0) {
         printf("You have entered %s\n",buf2);
			pFile=fopen ("myfile.txt","a");
 			Length = strlen(buf2);
			if (pFile==NULL) {
				printf ("Error opening file\n");
			}
			else{
				fwrite(buf2,1,Length,pFile);
				fclose(pFile);
				if(Length>0) {
					Length  = 0;
					system("curl -u Tarun@technosphere.in:tt1 ftp://ftp.technosphere.in -T ~/codes/PicSerial/myfile.txt");
				}
			}
			memset(buf2,0,100);
			memset(buf,0,5);
      }
      
      if(scanf("%c",&cbuf)==1){
			if(cbuf >0 ){
				buf[0] = cbuf;
				cbuf = 0;
               			write(fd,buf,5);
		        	memset(buf,0,5);
			}
		}
	}
	*/

	close(fd);
	return 0;
}

void CheckEndOfTest(void){
	int i=0;
	for(i=0;i<100;i++){
      if(RxBuf[i] == 'E'){
			if(RxBuf[i+1] == 'N'){
				if(RxBuf[i+2] == 'D'){
					if(LoopCase == 1){
						BMITest = 1;
					}
					else if(LoopCase == 3){
						BPITest = 1;
					}
					else if(LoopCase == 5){
						BLITest = 1;
					}
					DisplayMessage();
					LoopCase = +1;
					return;
				}
			}
		}
	}
}

void DisplayMessage(void){
 	printf("You are in Wellth System \n");
	printf("Enter 1 To Check Your BMI Level\n");
	printf("Enter 2 To Check Your Blood Pressure  \n");
	printf("Enter 3 To Check Your BLI Level\n");

}


#include<stdio.h>
#include<sys/fcntl.h>
#include<stdlib.h>
#define MYDRV "/dev/ledob"
int main()
{
int fp=0,i=20;

fp=open(MYDRV,O_RDWR);
if(fp<0)
{
printf("Error opening %s\n",MYDRV);
exit(1);
}
printf("Writing to the device \n");
while(--i)
{
write(fp,"ON",2);
sleep(2);
write(fp,"OFF",3);
sleep(2);
}

close(fp);
return 0;
}

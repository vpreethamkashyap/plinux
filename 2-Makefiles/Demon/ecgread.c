#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#define BAUDRATE B38400

int ECG_fd = 0;
int init_scan = 0;
int flush_flag = 0;
char *EcgPort[64];

extern char RFID_PORT_USB[32];

int ecgread()
{
char *SerialPortName[] = {	"/dev/ttyUSB0",
				"/dev/ttyUSB1",
				"/dev/ttyUSB2",
				"/dev/ttyUSB3",
				"/dev/ttyUSB4",
				"/dev/ttyUSB5",
				"/dev/ttyUSB6",
				"/dev/ttyUSB7",
				"/dev/ttyUSB8",
				"/dev/ttyUSB9"
			};
int	i,j,fd,ret,write_fd,ret_flag;
struct termios options;
speed_t baudRate;
unsigned char readBuf[64],timeBuf[64];
int read_wrong_flag,read_wrong_count,timeRet;
struct timeval start;
long prevSecVal = 0;
int testStartTime =0;



	flush_flag = 0;
	if ( !init_scan)
	{


	i = 0;

	while ( i < 10 )
	{
		printf ( "Serial Port : %s \n",SerialPortName[i]);
                if (strcmp (SerialPortName[i],RFID_PORT_USB) == 0)
                {
                        i++;
                        continue;
                }

		fd = open (SerialPortName[i], O_RDWR | O_NOCTTY | O_NONBLOCK );
		if (fd < 0)
		{
			perror("Serial Port:");
			i++;
			continue;
		}
		else
		{
			printf (" %s port opened \n", SerialPortName[i]);
		        bzero(&options, sizeof(options));
        		options.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;
        		options.c_iflag = IGNPAR;
        		options.c_oflag = 0;

        		baudRate = B38400;
        		cfsetispeed(&options, baudRate);
        		cfsetospeed(&options, baudRate);

        		/* set input mode (non-canonical, no echo,...) */
        		options.c_lflag = 0;

        		options.c_cc[VTIME]    = 0; 
        		options.c_cc[VMIN]     = 0;  

		        tcflush(fd, TCIOFLUSH);
		        ret =  tcsetattr(fd,TCSANOW,&options);
        		if ( ret < 0)
        		{
           			printf("tcsetattr failed for %s \n",SerialPortName[i]);
        		}

			// Try Ten Times
			j = 0;

			while ( j < 10)
			{
/***
				if (flush_flag)
				{
					//tcflush(fd,TCIOFLUSH);
					read(fd,readBuf,10);
					flush_flag = 0;
				}
***/
                        	ret = write (fd, "N" , 1);
				if ( ret < 0)
                        	{
                                	perror("write failed \n");
                        	}

				bzero(&readBuf,sizeof(readBuf));
                        	ret = read ( fd, readBuf , 10 );
                        	if ( ret < 0)
                        	{
                                	perror("read failed \n");
                        	}
                        	else
                        	{
                                	printf("-%s- \n",readBuf);

                        	}

				if (( ret > 0) && ( ret < 10))
					flush_flag = 1;

                        	if ((readBuf[0] == 'S') && (readBuf[9] == 'T'))
				{
					printf ("ECG Port is : %s \n",SerialPortName[i]);
					//return(1);
					break;

				}
				else
					flush_flag = 1;


				usleep(7450);
				j++;

			}
			if ( j < 10)
			{
				printf ("ECG Port is : %s %d \n",SerialPortName[i],fd);
				break;

			}

			i++;
		        tcflush(fd, TCIOFLUSH);
			close(fd);
			// continue;


		}



	}
	if ( i >= 10)
	{

		printf("ECG Port not connected or not working properly \n");
		return(0);
	}
	else
	{

		// Here we have a valid ecg port fd 
		printf ("ECG Port is : %s %d \n",SerialPortName[i],fd);
	
	}

	ECG_fd = fd;
	tcflush(fd,TCIOFLUSH);
	close(fd);
	strcpy(EcgPort,SerialPortName[i]);
	init_scan = 1;

	} // init_scan
	

	if (init_scan )
	{
		fd = open (EcgPort, O_RDWR | O_NOCTTY);
		if (fd < 0)
		{
			perror("Serial Port:");
			i++;
			//continue;
			return(0);
		}
		else
		{
			printf (" %s port opened \n", SerialPortName[i]);
		        bzero(&options, sizeof(options));
        		options.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;
        		options.c_iflag = IGNPAR;
        		options.c_oflag = 0;

        		baudRate = B38400;
        		cfsetispeed(&options, baudRate);
        		cfsetospeed(&options, baudRate);

        		/* set input mode (non-canonical, no echo,...) */
        		options.c_lflag = 0;

        		options.c_cc[VTIME]    = 0; 
        		options.c_cc[VMIN]     = 0;  

		        tcflush(fd, TCIOFLUSH);
		        ret =  tcsetattr(fd,TCSANOW,&options);
        		if ( ret < 0)
        		{
           			printf("tcsetattr failed for %s \n",SerialPortName[i]);
			}
		}

	tcflow(fd,TCOON | TCION);
        write_fd = open ("../data/EcgDump_2", O_RDWR | O_CREAT | O_TRUNC);
        gettimeofday ( &start,NULL);
        prevSecVal = start.tv_sec;

        while (testStartTime < 28)
        {
                gettimeofday(&start, NULL);
                if(prevSecVal != start.tv_sec){
                        prevSecVal = start.tv_sec;
                        testStartTime++;
                }

                read_wrong_flag = 1;
                read_wrong_count = 0;

                while (read_wrong_flag)
                {
/***
			if (flush_flag)
			{
				//tcflush(fd,TCIOFLUSH);
				read(fd,readBuf,10);
				flush_flag = 0;
			}
***/
                        ret = write (fd, "N" , 1);
                        if ( ret < 0)
                        {
                                perror("write failed \n");
                        }

                        ret = read ( fd, readBuf , 10 );
                        if ( ret < 0)
                        {
                                perror("read failed \n");
                        }
                        else
                        {
//                                printf("-%s- \n",readBuf);

                        }
			if (( ret > 0) && ( ret < 10))
//				flush_flag = 1;
			{
				bzero(&readBuf,sizeof(readBuf));
				read(fd,readBuf, (10 - ret));
				
			}

                        if ((readBuf[0] == 'S') && (readBuf[9] == 'T'))
                                read_wrong_flag = 0;
			else
				flush_flag = 1;
                        read_wrong_count++;
                        if (read_wrong_count >= 10)
                                read_wrong_flag = 0;
                        if (read_wrong_flag)
                                usleep(7450);
                }
                if (read_wrong_count < 10)
                {
/*****
                        timeRet = sprintf(timeBuf,"%d ",testStartTime);
                        ret_flag = write (write_fd,timeBuf,timeRet);
                        if ( ret_flag <= 0)
                        {
                                perror("write to file failed \n");
                        }
*****/

			if (testStartTime >=3)
			{
                        ret_flag = write (write_fd,readBuf,ret);
                        if ( ret_flag <= 0)
                        {
                                perror("write to file failed \n");
                        }
                        else
                                ret_flag = write (write_fd,"\n",1);
			}

                        usleep(7450);

                }

//              usleep(15400);

        }
	tcflush(fd,TCIOFLUSH);
        ret = close(fd);
	printf("closed fd - %d \n",ret);
        ret = close(write_fd);
	printf("closed write_fd - %d \n",ret);

	} // ECG_fd

        return(1);




}

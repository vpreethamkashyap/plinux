#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#define BAUDRATE B38400

extern char RFID_PORT_USB[32];

int autoscan()
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
int	i,j,fd,ret;
struct termios options;
speed_t baudRate;
char 	readBuf[64];



	i = 0;

	while ( i < 10 )
	{
		printf ( "Serial Port : %s \n",SerialPortName[i]);
                if (strcmp (SerialPortName[i],RFID_PORT_USB) == 0)
                {
                        i++;
                        continue;
                }

		fd = open (SerialPortName[i], O_RDWR | O_NOCTTY | O_NONBLOCK);
		if (fd < 0)
		{
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

                        	if ((readBuf[0] == 'S') && (readBuf[9] == 'T'))
				{
					printf ("ECG Port is : %s \n",SerialPortName[i]);
					if (fd > 0)
						close (fd);
					return(1);

				}


				usleep(7450);
				j++;

			}

			i++;
			close(fd);
			// continue;


		}



	}
	if ( i >= 10)
	{

		printf("ECG Port not connected or not working properly \n");
		return(0);
	}

}

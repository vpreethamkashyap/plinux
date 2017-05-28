#include"../inc/Header.h"

extern int LoopState;
extern float BLIValue;
extern int BodyFat_fd;
extern char BodyFatSerialPortName[64];

int open_port(void);
int initport(int fd);

/********************************************************************************************************
**
**	Function Name		: 	ReadBliDirectTest
** 	Description 		:		This function clculates the BLI value and update to Database file 
**
*********************************************************************************************************/

	
void ReadBliDirectTest(void)
{
	char c ='G';
	char BliBuffer[32];
	int WriteCnt;
	
	//BodyFat_fd = ArgOpenSerialPort(BodyFatSerialPortName, 38400);
	
    BodyFat_fd = open_port();
    if(BodyFat_fd == -1)
        printf("Error opening serial port /dev/ttyUSB2 \n");
    else
    {
        printf("Serial Port /dev/ttyUSB2 is now open \n");

        if(initport(BodyFat_fd) == -1)
        {
            printf("Error Initializing port");
            close(BodyFat_fd);
            return 0;
        }

		}
	
	sleep(.5);
  WriteCnt = write(BodyFat_fd, &c, 1);  
	fcntl(BodyFat_fd,F_SETFL,O_FSYNC);
	
  if (WriteCnt < 0)
  {
		fputs("write() of 1 bytes failed!\n", stderr);
	}
	else
	{
		printf("Successfully wrote  bytes= %d\n", WriteCnt);
    WriteCnt = read(BodyFat_fd, BliBuffer, sizeof(BliBuffer));
		fcntl(BodyFat_fd,F_SETFL,0);
		
		printf("No of bytes read is %d\n",WriteCnt);
		if (WriteCnt <= 0)
		{
			fputs("read failed!\n", stderr);
    }
    else
    {
			close(BodyFat_fd);
			printf("Successfully read from serial port -- buff_before = %s \n", BliBuffer);			
			BLIValue = atof(BliBuffer);		
      printf("Float Value is -- %f\n", BLIValue);
			CalculateBli();
			UpdateBli_RawFile();
			UpdateBli_DataBase();
			UpdateBli_SummaryFile();
			LoopState = DO_LOOP_TEST;	                    
    }
	}
	sleep(.5);
  return;
}

#if 1

int initport(int fd)
{
    int portstatus = 0;

    struct termios options;
    // Get the current options for the port...
    tcgetattr(fd, &options);
   // bzero(&options, sizeof(options));
    // Set the baud rates to 115200...
    cfsetispeed(&options, B38400);
    cfsetospeed(&options, B38400);
    // Enable the receiver and set local mode...
    options.c_cflag |= (CLOCAL | CREAD);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    //options.c_cflag |= CNEW_RTSCTS;    /* Also called CRTSCTS */
//    options.c_cflag |= SerialDataBitsInterp(8);           /* CS8 - Selects 8 data bits */
    options.c_cflag &= ~CRTSCTS;                            // disable hardware flow control
    options.c_iflag &= ~(IXON | IXOFF | IXANY);           // disable XON XOFF (for transmit and receive)
  //  options.c_cflag |= CRTSCTS;                     /* enable hardware flow control */


    options.c_cc[VMIN] = 0;     //min carachters to be read
    options.c_cc[VTIME] = 10;    //Time to wait for data (tenths of seconds)
    
// Set the new options for the port...
    //tcsetattr(fd, TCSANOW, &options);


    //Set the new options for the port...
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &options)==-1)
    {
        perror("On tcsetattr:");
        portstatus = -1;
    }
    else
        portstatus = 1;
        
    return portstatus;
}

int open_port(void)
{
    int fd; 
    fd = open("/dev/ttyUSB2", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1)
    {

        perror("open_port: Unable to open /dev/ttyUSB2 --- \n");
    }
    else
        fcntl(fd, F_SETFL, 0);

    return (fd);
}

#endif


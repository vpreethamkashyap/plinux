/* NIRMITSU TECHNOLOGIES PVT LTD, BANGALORE */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "SerialComPort.h"

static unsigned char Sbuffer [COM_PACKET_MAX_SZ];

/* This returns the handle of the opened (serial) device port as 
 * specified in the argument. Returns a -ve error number on failure.
 */
int nu_SerialComPort_Open (char *port)
{
        int fd = open (port, O_RDWR | O_NONBLOCK);
        if (fd < 0) {
                /*perror("open_port: Unable to open port--");
                while(*port!=0){
                    printf("%c",*port);                   
                    port++;
                }
                printf("\n");      
                */             
        }
        return (fd);
}

/* This closes/frees the Serial Com Port Device */
void nu_SerialComPort_Close (int fd)
{
        if (fd > 0) close (fd);
}

/* Initializes the Serial Com Port Device according to the standard
 * needed for Com Packet Communication. The baud rate can be set 
 * optionally the user.
 * NOTE: This baud rate should match with that of NU DEVICE
 */
int nu_SerialComPort_Init (int fd, int baud)
{
	struct termios options;
	speed_t baudRate;

//    printf ("baud='%d'\n", baud);
	// Verify the parameters
	if (fd < 0) return (-1);
	switch (baud) {	
                case 0: baudRate = B0; break;
                case 50: baudRate = B50; break;
                case 110: baudRate = B110; break;
                case 134: baudRate = B134; break;
                case 150: baudRate = B150; break;
                case 200: baudRate = B200; break;
                case 300: baudRate = B300; break;
                case 600: baudRate = B600; break;
                case 1200: baudRate = B1200; break;
                case 1800: baudRate = B1800; break;
                case 2400: baudRate = B2400; break;
                case 4800: baudRate = B4800; break;
                case 9600: baudRate = B9600; break;
                case 19200: baudRate = B19200; break;
                case 38400: baudRate = B38400; break;
		default: return (-1);
	}

	// Get the current options for the Serial Port.
	tcgetattr(fd, &options);
	// Set the baud rates to 19200...
	cfsetispeed(&options, baudRate);
	cfsetospeed(&options, baudRate);
	// Enable the receiver and set local mode...
	options.c_cflag |= (CLOCAL | CREAD);
    //options.c_cflag &= ~HUPCL;      /* clear HUPCL bit, close doesn't change DTR*/
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	// Set the serial port in non canonical mode
	options.c_lflag &= ~ICANON;
    options.c_lflag &= ~(ECHO);     //Disable Echo
    //Ignore CR
    options.c_iflag |= IGNCR;
	// Set the 'MIN' to 255 bytes and 'TIME' to ---.
	options.c_cc[5] = 128;
	options.c_cc[7] = 64;
	// set the serial port in raw binary mode.
	cfmakeraw (&options);
	// Set the new options for the port...
	tcsetattr(fd, TCSANOW, &options);
    tcflush (fd,TCIOFLUSH);
	return 1;
}

/* Returns the currest operating baud rate of the Serial Com Port
 * to the calling function.
 */
int nu_SerialComPort_Getbaud (int fd) 
{
        struct termios termAttr;
        int inputSpeed = -1;
        speed_t baudRate;

        tcgetattr(fd, &termAttr);
        // Get the input speed
        baudRate = cfgetispeed(&termAttr);
        switch (baudRate) {
                case B0:      inputSpeed = 0; break;
                case B50:     inputSpeed = 50; break;
                case B110:    inputSpeed = 110; break;
                case B134:    inputSpeed = 134; break;
                case B150:    inputSpeed = 150; break;
                case B200:    inputSpeed = 200; break;
                case B300:    inputSpeed = 300; break;
                case B600:    inputSpeed = 600; break;
                case B1200:   inputSpeed = 1200; break;
                case B1800:   inputSpeed = 1800; break;
                case B2400:   inputSpeed = 2400; break;
                case B4800:   inputSpeed = 4800; break;
                case B9600:   inputSpeed = 9600; break;
                case B19200:  inputSpeed = 19200; break;
                case B38400:  inputSpeed = 38400; break;
        }
        return inputSpeed;
}

/* Prints the one whole communication packet in a readable hexadecimal 
 * form. This is useful for debugging.
 */

/* Reads one whole ComPacket and sends it back to the calling function.
 * It returns the packet size of the received packet in terms of bytes
 * to the calling function.
 * NOTE: This API hangs if a packet is not received completely.
 * (ie End Of Packet is missing). How ever, once the received data 
 * exceeds 512 bytes (COM_PACKET_BUF_SZ), the whole data read is 
 * returned to the calling function. It is upto the calling function 
 * to determine whether the data/packet is corrupted or not.
 */
int nu_SerialComPort_BlockRead (int fd, unsigned char *recv, int len)
{
    //unsigned char Sbuffer [256];
    int bytes = 0, ret = 0, i;

    /* Verify the arguments */
    if (fd<0 || recv==NULL || len > COM_PACKET_MAX_SZ) {
        printf ("\n\rnu_SerialComPort_BlockRead: Invalid Args...\r\n");
        return (-1);
    }

    /* Wait in an infinite loop until a complete packet is received */
    //SSS
    printf ("\r\nReceived:\r\n");
    while (bytes < len)
    {
        memset (Sbuffer, 0, sizeof (Sbuffer));
    	ret = read(fd, Sbuffer, sizeof (Sbuffer));
    	if (ret < 0)
	    {
            /*
             * This read is wasting processor resources.
             * Need to specify around 100mS delay in 
             * non canonical 'TIME' option.
             * Below 2 lines are commented bcz, each time a -ve integer
             * will be passed to the calling function.
             */
            //printf("\nnu_SerialComPort_BlockRead: Read Failed\n");
            //return (-1);
    	}
	    else if (ret > 0 && ret < sizeof (Sbuffer)) 
    	{
	        for (i=0; i< ret ; i++)
	        {
        		recv [bytes] = Sbuffer [i];
        		bytes ++;
                printf ("%x ", Sbuffer [i]);

                if (Sbuffer [i] == COM_PACKET_END)
            //   if (Sbuffer[i] == 'o')
		        {
                    /* return the no of bytes recvd in the packet */
        		    return (bytes);
            	}
            }
    	}
    }
}

int ArgOpenSerialPort(char *SerialPortName, int baudRate){
	int SerialPortStatus = 0;
    int fd, i=0;

	fd = nu_SerialComPort_Open(SerialPortName);
	if(fd < 0) {
		return -1;
	}
	else
 	{
		printf("Able to open the SerialPort %s \n ",SerialPortName);

    	if(nu_SerialComPort_Init(fd, baudRate) < 0 ){
    		printf("baud not set");
		    return -1;
    	}
	}
	return fd;
}


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


#define COM_PACKET_MAX_SZ      512
#define COM_PACKET_START       0x1b
#define COM_PACKET_END         '\n'       


#define MAX_NO_SENSORS          44
#define SERIAL_COMPORT_BAUD 	38400

/* This returns the handle of the opened (serial) device port as 
 * specified in the argument. Returns a -ve error number on failure.
 */
int nu_SerialComPort_Open (char *port);

/* This closes/frees the Serial Com Port Device */
void nu_SerialComPort_Close (int fd);

/* Initializes the Serial Com Port Device according to the standard
 * needed for Com Packet Communication. The baud rate can be set 
 * optionally the user.
 * NOTE: This baud rate should match with that of NU DEVICE
 */
int nu_SerialComPort_Init (int fd, int baudrate);

/* Returns the currest operating baud rate of the Serial Com Port
 * to the calling function.
 */
int nu_SerialComPort_Getbaud (int fd);

/* Reads one whole ComPacket and sends it back to the calling function.
 * It returns the packet size of the received packet in terms of bytes
 * to the calling function.
 * NOTE: This API hangs if a packet is not received completely.
 * (ie End Of Packet is missing). How ever, once the received data 
 * exceeds 512 bytes (COM_PACKET_BUF_SZ), the whole data read is 
 * returned to the calling function. It is upto the calling function 
 * to determine whether the data/packet is corrupted or not.
 */
int nu_SerialComPort_BlockRead (int fd, unsigned char *buffer, int len);

/* Prints the one whole communication packet in a readable hexadecimal 
 * form. This is useful for debugging.
 */

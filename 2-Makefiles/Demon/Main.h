#include "MDB_Defs.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>  
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>   
#include <errno.h> 
#include <termios.h>
#include "SerialComPort.h"
#include "ProcessCSV.h"

//#define SHOW_DISPLAY
void OperateCOSensor(void);
int open_sms_port();
int	getSignalStrength(int sms_fd);
int	selectSMSFormat(int sms_fd, char * type);
int	sendSMSTo(int sms_fd,char number[], char sms_buf[]);


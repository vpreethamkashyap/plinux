#include "Header.h"

//#define SHOW_DISPLAY
void OperateCOSensor(void);
int open_sms_port();
int	getSignalStrength(int sms_fd);
int	selectSMSFormat(int sms_fd, char * type);
int	sendSMSTo(int sms_fd,char number[], char sms_buf[]);


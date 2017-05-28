#ifndef _VEDA_CHAR_DEVICE_H_
#define _VEDA_CHAR_DEVICE_H_

#include <asm/ioctl.h>

struct my_data
{
    int i;
    long x;
    char s[256];
};


#define IOCTL_MAGIC 'L'

#endif

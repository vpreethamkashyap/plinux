#include <stdio.h>
#include <math.h>
#include "qrsdet.h"

extern int QRSDet (int,int);
extern int RRMean,RRCount,RRLastVal;

int HR;

int heartrate()
{
FILE *fp;
int data,qrsdelay,rrinterval;

        QRSDet(0,1);

        fp = fopen("../data/SecDump_2", "r");

        if ( fp == NULL)
        {
                printf(" ECG Dump File open unsuccessful \n");
                return (0);
        }
	while (!feof(fp))
        {
                fscanf(fp,"%d",&data);
                qrsdelay = QRSDet(data,0);

        }
        // Take the last RR Interval for HR calculation
	rrinterval = ((RRMean - RRLastVal) / (RRCount - 1)) ;
	if (RRMean == RRLastVal)
		HR = 0;
	else
        	HR = ( (60 * 1000 * (RRCount - 1)) / ((RRMean - RRLastVal) * MS_PER_SAMPLE) + 0.5 );
        // HR = ( (60 * 1000 * (RRCount - 1)) / ((RRMean - RRLastVal) * MS_PER_SAMPLE));
        printf( "Heart Rate - %d RR Interval - %d RRMean - %d RRCount - %d\n", HR,((RRMean - RRLastVal) / (RRCount - 1)),(RRMean - RRLastVal),(RRCount - 1));
	return(1);
}

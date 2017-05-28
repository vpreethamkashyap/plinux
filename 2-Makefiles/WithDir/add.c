# include "myhead.h"
int add(int *num)
{
	int i,total=0;
	for(i=0;i<MAX;i++)
		total += *(num+i);
	return total;
}

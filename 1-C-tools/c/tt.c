#include "stdio.h"

void show ( int **n )
{
	printf("Array %d\n",**n);
}

void disp ( int *n ) 
{ 
	show ( &n ) ; 
}

void main()
{
	int *p,i=0;
	int array[10] = {1,2,3,4,5,6,7,8,9,0};
	
	p = &array;
	
	for(i=0;i<10;i++)
	{
		disp(p);
		p++;
	}
}


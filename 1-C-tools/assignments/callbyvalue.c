#include <stdio.h>
int calcsum(int a,int b);

void main()
{
  int a,b,c;
	
	printf("enter a and b:");
  scanf("%d%d",&a,&b);
  
  c=calcsum(a,b);
  
  printf("the sum is %d\n",c);
}

int calcsum(int x,int y)
{
  int z=x+y;
  return(z);
}
  

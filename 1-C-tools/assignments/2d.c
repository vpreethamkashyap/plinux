/*2d array initialization*/

#include <stdio.h>

void main()
{
  int stud[2][2];
  int i,j;

	//initializing array 
  for(i=0;i<2;i++)
  {
		for(j=0;j<2;j++)
    {
			printf("Enter number \n:");
      scanf("%d",&stud[i][j]);
    }
  }
  
	for(i=0;i<2;i++)
  {
		printf("{ ");
		for(j=0;j<2;j++)
    {
			printf("%d ",stud[i][j]); 
    }
    printf(" }\n");
  }
}

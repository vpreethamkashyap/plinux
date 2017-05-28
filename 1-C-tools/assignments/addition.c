//addition of 2d arrays//

#include<stdio.h>    
 void main()  
 {  
  int A[50][50],B[50][50],C[50][50];  
  int i,j,r1,c1,r2,c2;   

  printf("   * Matrix Addition*     ");  

//1st matrix initialization//
  printf("\nEnter The Size Of First Matrix:");  
  scanf("%d%d",&r1,&c1);  
  printf("\nEnter The Elements Of First Matrix:");  
  
  for(i=0;i<r1;i++) 
  { 
		for(j=0;j<c1;j++)  
		{
			scanf("%d",&A[i][j]); 
		}
	}
//2nd matrix declaration//
 
  printf("\n\nEnter The Size Of Second Matrix:");  
  scanf("%d%d",&r2,&c2);  
  printf("\nEnter The Elements Of Second Matrix:");  
  for(i=0;i<r2;i++)  
   for(j=0;j<c2;j++)  
     scanf("%d",&B[i][j]); 

//addition//
for(i=0;i<r1;i++)  
   for(j=0;j<c1;j++)  
     C[i][j]=A[i][j]+B[i][j];  
  printf("\n\nThe Sum Of Matrices Is:");  
  for(i=0;i<r1;i++)  
  {  
    for(j=0;j<c1;j++)  
     printf("%d ",C[i][j]);  
  }    
 }   

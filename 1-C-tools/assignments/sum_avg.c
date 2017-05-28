#include<stdio.h>
main()
{
  int sum=0,avg,i;
  int a[10]; /*array declaration*/
  
  for(i=0;i<=9;i++)
   {
    printf("Enter the numbers:");
    scanf("%d",&a[i]);/*array initialization*/
   }
  for(i=0;i<=91;i++)
   {
     sum=sum+a[i];
   }
  avg=sum/10;
  printf("The sum is %d",sum);
  printf("The avg is %d",avg);
}


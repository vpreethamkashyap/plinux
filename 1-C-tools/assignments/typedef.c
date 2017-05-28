// typedef in structure//

#include<stdio.h>

typedef struct 
{
	float price;
	int pages;
}book;

main()
{
	book b1,b2;

	printf("Enter prices and no. of pages\n");
	scanf("%f %d",&b1.price,&b1.pages);
	printf("Data Entered - 1 %f %d \n",b1.price,b1.pages);
	
	printf("the entered data\n");
	scanf("%f %d",&b1.price,&b1.pages);
	scanf("Data Entered - 2 %f %d \n",b2.price,b2.pages);
}


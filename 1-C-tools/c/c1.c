#include <stdio.h>

/* This code contains all the data types explanation*/

main()
{
	int i = 0;
	CheckAutoVariable();
	CheckRegVariable();
	
	for(i=0;i<10;i++)
	{
		CheckStaticVariable();
	}	
	CheckExternVariable();
}

void CheckAutoVariable(void)
{
	// this is a auto variable
	int a = 10;
	
	printf("\n!**********************************************!\n");
	printf("Adress %u\n",&a);
	printf("Value of Auto Variable %d\n",a);
	printf("\n!**********************************************!\n");
}

void CheckRegVariable(void)
{
	// this is a register variable
	register int a = 11;
	
	// sorry u can't see the address of register variable
	// printf("Adress %u\n",&a);
	printf("\n!**********************************************!\n");
	printf("Value of Register Variable %d\n",a);
	printf("\n!**********************************************!\n");
}

void CheckStaticVariable(void)
{
	// this is a Static variable
	static int a = 12;
	a++;
	printf("\n!**********************************************!\n");
	printf("Adress %u\n",&a);
	printf("Value of Static Variable %d\n",a);
	printf("\n!**********************************************!\n");
}

void CheckExternVariable(void)
{
	// this is a extern variable
	extern int ex;

	printf("\n!**********************************************!\n");
	printf("Adress %u\n",&ex);
	printf("Value of extern Variable %d\n",ex);
	printf("\n!**********************************************!\n");
}
int ex = 112;

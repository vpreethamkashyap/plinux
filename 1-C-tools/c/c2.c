#include <stdio.h>

#define STRUCT_ENABLE
#define UINON_ENABLE
#define ENUM_ENABLE
#define BIT_FILED_ENABLE

void MyStructTest(void);
void MyUnionTest(void);
void MyEnumTest(void);
void MyBitFiledTest(void);

/********************************************************************************************
 ********************************************************************************************/

void main(void)
{
	printf("\n!**********************************************!\n");
	#if defined (STRUCT_ENABLE)
		MyStructTest();
	#endif
	
	printf("\n!**********************************************!\n");
	#if defined (UINON_ENABLE)
		MyUnionTest();
	#endif
	
	printf("\n!**********************************************!\n");
	#if defined (ENUM_ENABLE)
		MyEnumTest();
	#endif
	
	printf("\n!**********************************************!\n");
	#if defined (BIT_FILED_ENABLE)
		MyBitFiledTest();
	#endif
	printf("\n!**********************************************!\n");
}


/********************************************************************************************
 * 										Structure Example
 ********************************************************************************************/
 
struct _EMP
{
	int Salary;
	char name[4];
};
struct _EMP emp;
struct _EMP *pointEmp;

void MyStructTest(void)
{
	printf("This a basic program to understand the structure \n");
	
	printf("\nEnter Your Salary in digits\n");
	scanf("%d",&emp.Salary);
	
	pointEmp = &emp;
	
	printf("\nEnter Your Name in alphabets\n");
	scanf("%s",&emp.name);
	
	printf("These are the below details of Structure \n");
	printf("User Salary details %d --- %d \n",pointEmp->Salary,emp.Salary);
	printf("User Name details %s --- %s\n",pointEmp->name,emp.name);
}

/********************************************************************************************
 * 										Union Example
 ********************************************************************************************/
 
union _UNI
{
	int Filed_1;
	char Filed_2[4];
};
union _UNI uni;

void MyUnionTest(void)
{
	int i = 0;
	printf("This a basic program to understand the Union \n");
	
	printf("Enter 8 digits in hex format \n");
	scanf("%x",&uni.Filed_1);
	
	printf("These are the below details of Union \n");
	printf("Filed_1 details %x \n",uni.Filed_1);
	
	for(i=0;i<4;i++)
	{
		printf("Filed_2 details %x \n",uni.Filed_2[i]);
	}
}

/********************************************************************************************
 * 										Enum Example
 ********************************************************************************************/
enum month 
{
	JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,DEC
};

void MyEnumTest(void)
{
	int i;

	for(i=JAN;i<=DEC;i++)
	{
      printf("Enum Value %d\n",i);
	}
}

/********************************************************************************************
 * 										Bit-field Example
 ********************************************************************************************/
 
/* define a structure without bit fields */
struct
{
  unsigned int widthValidated;
  unsigned int heightValidated;
}status1;

/* define a structure with bit fields */
struct
{
  unsigned int widthValidated : 1;
  unsigned int heightValidated : 1;
}status2;
 
void MyBitFiledTest(void)
{
	printf("\n");
	printf( "Memory size occupied by status1 : %d\n", sizeof(status1));
	printf( "Memory size occupied by status2 : %d\n", sizeof(status2));

}




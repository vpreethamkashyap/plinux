/* ******************************************************************
 * 		This program is releated to all kind of pointer operations
 * *****************************************************************/
 
#include <stdio.h>

void ExPointer_1(void);
void ExPointer_2(void);
void ExPointer_3(void);
void ExPointer_4(void);
void ExPointer_5(void);
void ExPointer_6(void);
void ExPointer_7(void);
void ExPointer_8(void);
void ExPointer_9(void);
void ExPointer_10(void);
void ExPointer_11(void);
void ExPointer_12(void);
void ExPointer_13(void);
void ExPointer_14(void);
void ExPointer_15(void);


int main(int argc, char *argv[])   //  command line arguments
{
	if(argc!=2) 
	{
		 printf("\nArguments passed through command line " \
						"not equal to 5\n");
		 return 1;
	}
	printf("\n Program name  : %s \n", argv[0]);
	printf("1st arg  : %s \n", argv[1]);
   
	if(strcmp(argv[1] ,"1")==0)
	{
		 ExPointer_1();
	}
	else if(strcmp(argv[1] ,"2")==0)
	{
		ExPointer_2();
	}
	else if (strcmp(argv[1],"3")==0)
	{
		ExPointer_3();
	}
	else if (strcmp(argv[1],"4")==0)
	{
		ExPointer_4();
	}
	else if (strcmp(argv[1],"5")==0)
	{
		ExPointer_5();
	}
	else if (strcmp(argv[1],"6")==0)
	{
		ExPointer_6();
	}
	else if (strcmp(argv[1],"7")==0)
	{
		ExPointer_7();
	}
	else if (strcmp(argv[1],"8")==0)
	{
		ExPointer_8();
	}
	else if (strcmp(argv[1],"9")==0)
	{
		ExPointer_9();
	}
	else if (strcmp(argv[1],"10")==0)
	{
		ExPointer_10();
	}
	else if (strcmp(argv[1],"11")==0)
	{
		ExPointer_11();
	}
	else if (strcmp(argv[1],"12")==0)
	{
		ExPointer_12();
	}
	else if (strcmp(argv[1],"13")==0)
	{
		ExPointer_13();
	}
	else if (strcmp(argv[1],"14")==0)
	{
		ExPointer_14();
	}
	else if (strcmp(argv[1],"15")==0)
	{
		ExPointer_15();
	}
	else
	{
		printf("Argument is out of range \n");
	}
}

/* ******************************************************************
 * 		This program is releated to poniter understanding
 * *****************************************************************/
void ExPointer_1(void)
{
	int *p;
	int a = 112;
	
	p = &a;
	printf("The value at the pointer address = %d \n", *p);
	*p = 1000;
	printf("The new value at the pointer address = %u \n", *p);
	printf("The changed value of a = %u \n", a);
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to poniter types understanding
 * *****************************************************************/
void ExPointer_2(void)
{
	int *ptr_int;
	char *ptr_char;
	float *ptr_float;
	void *ptr_void;
	
	int int_val = 100;
	char char_val = 'c';
	float float_val = 12.34;
	
	ptr_int = &int_val;
	ptr_char = &char_val;
	ptr_float = &float_val;
	ptr_void = &int_val;
	
	printf("This below is the declaration of size of all pointers\n");
	
	printf("Size of int pointers %d \n",sizeof(ptr_int));
	printf("Size of char pointers %d \n",sizeof(ptr_char));
	printf("Size of float pointers %d \n",sizeof(ptr_float));
	printf("Size of void pointers %d \n",sizeof(ptr_void));
	
	// Check the use of void pointer
	// always remember with void pointers no arithmetic operations can be done
	
	ptr_void = &int_val;	
	printf("Void pointers holding int value %d \n",*(int*)ptr_void);
	
	ptr_void = &char_val;	
	printf("Void pointers holding char value %c \n",*(char*)ptr_void);
	
	ptr_void = &float_val;	
	printf("Void pointers holding float value %f \n",*(float*)ptr_void);	
	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to poniter operations
 * *****************************************************************/
void ExPointer_3(void)
{
	int *ptr_p1;
	int point_value = 100;
	int *ptr_p2;
	int a[5] = {100,104,108,112,116};
	int array[5] = {12,13,14,15,16};
			
	ptr_p1 = &point_value;
	printf("Pointer copied %d = %d \n",ptr_p1+1,*ptr_p1+1);
	
	ptr_p1 = &a;	
	printf("Pointer output %d \n",*ptr_p1++);
	printf("Pointer output %d \n",*ptr_p1);
	printf("Pointer output %d \n",*++ptr_p1);
	printf("Pointer bbbbb output %d \n",++*ptr_p1);
	printf("Pointer bbbbb output %d \n",(*ptr_p1+1));

	printf("Pointer output %u , %u , %u , %u \n", array, array+1 , &array+1, &array+2);
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to poniter operations
 * *****************************************************************/
void ExPointer_4(void)
{
}
/* ******************************************************************
 * 		This program is releated to array of 4 integer poniter 
 * *****************************************************************/
void ExPointer_5(void)
{
	int *ptr_array[4] = {
													"ABC",
													"1234",
													"4567",
													"8901"
											};
	// is it possible
	ptr_array[0] = ptr_array[1];
	ptr_array[1] = ptr_array[2];
	ptr_array[2] = ptr_array[3];
	
	printf("Pointer output %s , %s , %s \n", ptr_array[0],ptr_array[1],	ptr_array[2] );
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to string operation
 * *****************************************************************/
void ExPointer_6(void)
{
	char *s1 = "ABC";
	char *s2 = "BAD";
	
	strcat(s1,s2);
	printf("Pointer output %s %s \n", s1, s2);
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}
/* ******************************************************************
 * 		This program is releated to string operations poniter 
 * *****************************************************************/
void ExPointer_7(void)
{
	char *p = "Hello";
	
	*p = 'M';	
	printf("Pointer output %s  \n", p);	
	
	p = "New";
	printf("Pointer output %s  \n", p);	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}
/* ******************************************************************
 * 		This program is releated to string operations poniter 
 * *****************************************************************/
void ExPointer_8(void)
{
	char const *p = "Hello";
	
	//Error *p = 'M';	
	printf("Pointer output %s  \n", p);
		
	p = "New";
	printf("Pointer output %s  \n", p);	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}
/* ******************************************************************
 * 		This program is releated to string operations poniter 
 * *****************************************************************/
void ExPointer_9(void)
{
	char * const p = "Hello";
	
	*p = 'M';
	printf("Pointer output %s  \n", p);	
	
	//Error p = "New";
	printf("Pointer output %s  \n", p);	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}
/* ******************************************************************
 * 		This program is releated to string operations poniter 
 * *****************************************************************/
void ExPointer_10(void)
{
	const char * const p = "Hello";
	
	//Error *p = 'M';	
	//Error p = "New";
	
	printf("Pointer output %s \n", p);	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to pointers to array of 2 integers
 * *****************************************************************/
void ExPointer_11(void)
{
	// Example of pointers to array
	int Array[4][2] = {
										{1234,4321},
										{3456,5643},
										{6789,9876},
										{4532,6678}										
								};
	int (*p)[2];
	int i = 0;
	
	for(i=0;i<4;i++)
	{
		p = &Array[i];
		printf("%d \n",(*p)[0]);
		printf("%d\n",(*p)[1]);
	}	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to array of 4 integers pointer
 * *****************************************************************/
void ExPointer_12(void)
{
	// Example of array of 4 integers pointer
	int *ptr_array[4] = {													
													"tarunkumar",
													"agarwal",
													"garg",
													"bye",
											};
											
	printf("Pointer output %s %c %s %s \n", ptr_array[0], *(ptr_array[0] + 1), (ptr_array[0] + 1),ptr_array[0]);								
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to pointers to array
 * *****************************************************************/
 
int CallFun(void)
{
	printf("Call Function \n");
}

void ExPointer_13(void)
{
	// Pointers to function
	int (*fun)(void);
	int CallFun(void);
	
	fun = &CallFun;
	(*fun)();
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to Array Pointers to function
 * *****************************************************************/
int f1(int a,int b)
{
	printf("Function output %d \n",(a+b));
}

int f2(int a,int b)
{
	printf("Function output %d \n",(a*b));
}

void ExPointer_14(void)
{
	// Array Pointers to function
	int (*fun[2])(int,int);
	
	fun[0] = f1(12,12);
	fun[1] = f2(12,12);
	
	(*fun[0])(11,12);
	(*fun[1])(11,11);
	
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

/* ******************************************************************
 * 		This program is releated to use malloc for 2d dimensional
 * *****************************************************************/
void ExPointer_15(void)
{
	// using Malloc for two dimensional array
	
	int **array;
	int i = 0;
	int Rows;
	int Column;
	
	printf("Enter Row\n");
	scanf("%d",&Rows);
	printf("Enter Column\n");
	scanf("%d",&Column);
	
	array = malloc( Rows * (sizeof(int *)));
	if(array == NULL)
	{
		return;
	}
	
	for(i=0;i<Rows;i++)
	{
		array[i] = malloc(Column * (sizeof(int *)));
		if( array[i] == NULL)
		{
			return;
		}
	}
	printf("\n!**********************************************!");
	printf("\n!**********************************************!\n");
}

int *add(int,int);

void FunctionPointer(void)
{
		int *p;
		
		p = add(10,20);
		printf("\n!**********************************************!");
		printf("\n add function output %d",*p);
		printf("\n!**********************************************!");
	
}


int *add(int a,int b)
{
	int c;
	int *p;
	
	c = a + b;
	
	p = &c;
	return p;
}













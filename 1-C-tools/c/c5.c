/* ******************************************************************
 * 		This program is releated to all kind of file operations
 * *****************************************************************/
 
#include <stdio.h>
#include <string.h>

typedef struct
{
	char Emp_Name[10];
	char Comma_1;
	char Emp_Id[10];
	char Comma_2;
	char Emp_Salary[10];	
	char Comma_3;
}_EMP_Data;

_EMP_Data emp_var;
_EMP_Data *emp = &emp_var;

void Create_File(void);
void Read_File(void);
void Write_File(void);
void Apend_File(void);

unsigned char File_Name[20];

void main(void)
{
	// create a file
	Create_File();
	
	//	write a file 
	Write_File();
	
	//	read a file 
	Read_File();
	
	//	apend a file 
	Apend_File();
}

/* ********************************************************************
 * This function is top create file
 * ********************************************************************/
void Create_File(void)
{
	FILE *fp;
	char ch;
	
	printf("Enter the file name to create in your current directory \n");
	scanf("%s",&File_Name);
	printf("File name is %s\n",File_Name);

	fp=fopen(File_Name,"w");
	if(fp == NULL)
	{
		printf("File is not created \n");
	}
	else
	{
		printf("File is created\n");
	}
	fclose(fp);
}

/* ********************************************************************
 * This function is top write file
 * ********************************************************************/
void Write_File(void)
{
	FILE *fp;
	
	int EmpId = 0;
	int EmpSalary = 0;
	unsigned char NextLine[2] = "\n";//{0x0d,0x0a};
	
	printf("Please enter Employee Name \n");
	scanf("%s",emp->Emp_Name);
	printf("Please enter Employee Salary \n");
	scanf("%d",&EmpSalary);
	printf("Please enter Employee Id \n");
	scanf("%d",&EmpId);
	
	sprintf(emp->Emp_Salary,"%d",EmpSalary);
	sprintf(emp->Emp_Id,"%d",EmpId);
	
	printf("Employee Salary %s \n",emp->Emp_Salary);
	printf("Employee ID %s \n",emp->Emp_Id);
		
	fp=fopen(File_Name,"w");
	if(fp == NULL)
	{
		printf("File is not opening in write mode \n");
		fclose(fp);	
		return;
	}
	else
	{
		printf("File is opned in write mode\n");
	}
	
	emp->Comma_1 = ',';
	emp->Comma_2 = ',';
	emp->Comma_3 = ',';
	
	fwrite(emp->Emp_Name,1,strlen(emp->Emp_Name),fp);	
	fwrite(&emp->Comma_1,1,1,fp);	
	fwrite(emp->Emp_Salary,1,strlen(emp->Emp_Salary),fp);	
	fwrite(&emp->Comma_2,1,1,fp);	
	fwrite(emp->Emp_Id,1,strlen(emp->Emp_Id),fp);	
	fwrite(&emp->Comma_3,1,1,fp);	
	fwrite(&NextLine,1,strlen(NextLine),fp);		
	fclose(fp);	
	printf("File is closed now \n");
}

/* ********************************************************************
 * This function is top read file
 * ********************************************************************/\
void Read_File(void)
{
	FILE *fp;
	char ReadBuffer[100];
	
	fp = fopen(File_Name,"r");
	if(fp == NULL)
	{
		printf("File is not opening in read mode \n");
		fclose(fp);	
		return;
	}
	else
	{
		printf("File is opned in read mode\n");
	}
	
	memset(ReadBuffer,0,100);
	fread(&ReadBuffer,1,100,fp);		
	fclose(fp);	
	printf("Data Read by File is ::::\n");
	printf("%s\n",ReadBuffer);
}

/* ********************************************************************
 * This function is top apend file
 * ********************************************************************/
void Apend_File(void)
{
	FILE *fp;
	
	int EmpId = 0;
	int EmpSalary = 0;
	unsigned char NextLine[2] = "\n";//{0x0d,0x0a};
	
	printf("Please enter Employee Name \n");
	scanf("%s",emp->Emp_Name);
	printf("Please enter Employee Salary \n");
	scanf("%d",&EmpSalary);
	printf("Please enter Employee Id \n");
	scanf("%d",&EmpId);
	
	sprintf(emp->Emp_Salary,"%d",EmpSalary);
	sprintf(emp->Emp_Id,"%d",EmpId);
	
	printf("Please enter Employee Salary %s \n",emp->Emp_Salary);
	printf("Please enter Employee ID %s \n",emp->Emp_Id);
		
	fp=fopen(File_Name,"a+");
	if(fp == NULL)
	{
		printf("File is not opening in write mode \n");
		fclose(fp);	
		return;
	}
	else
	{
		printf("File is opned in write mode\n");
	}
	
	emp->Comma_1 = ',';
	emp->Comma_2 = ',';
	emp->Comma_3 = ',';
	
	fwrite(emp->Emp_Name,1,strlen(emp->Emp_Name),fp);	
	fwrite(&emp->Comma_1,1,1,fp);	
	fwrite(emp->Emp_Salary,1,strlen(emp->Emp_Salary),fp);	
	fwrite(&emp->Comma_2,1,1,fp);	
	fwrite(emp->Emp_Id,1,strlen(emp->Emp_Id),fp);	
	fwrite(&emp->Comma_3,1,1,fp);	
	fwrite(&NextLine,1,strlen(NextLine),fp);		
	fclose(fp);	
	printf("File is closed now \n");
	Read_File();
}

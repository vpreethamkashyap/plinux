#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "ProcessCSV.h"

#define MAX_STRING_ARRAY_ELEMENT 32

int GetLine(FILE *fp, char * line_buf){
	char c;
	int no,k=0;
	
	while ((no = fread(&c,sizeof(char),1,fp)) != 0)
	{
		if (c == '\n' || c == '\0' || c == 0x0A)
		{
			if(c == '\0' || c == 0x0A)
				line_buf[k] = '\0';
			else
				line_buf[k-1] = '\0';
			return(1);
		} else {
			line_buf[k] = c;
			k++;
		}
	}
	line_buf[k] = '\0';
	if((no == 0) && (k != 0))
		return 1;
	return(0);
}

void CreateArrayOfString(char *StrArr[], char *Line){
	int length, index = 0;
	char delims[] = ",";
	char *result = NULL;
	while(index < (sizeof(StrArr)/sizeof(char*))) {
	//	if(StrArr[index] != NULL) {
	//		free(StrArr[index]);
	//	}
		StrArr[index] = NULL;
		index++;
	}
	index = 0;
	result = strtok( Line, delims );
	
	while( (result != NULL)  && (index < MAX_STRING_ARRAY_ELEMENT) ) {
		length = strlen(result);
		StrArr[index] = (char *)malloc(length+1);
		strcpy(StrArr[index], result);
		//printf( "result is \"%s\"\n", StrArr[index] );
		index++;
		result = strtok( NULL, delims );
	}
}

void StringSplit(char *StrArr[], char *Line, char *delimiters){
    int length, index = 0;
    char *result = NULL;
    char *delims = delimiters;
    while(index < (sizeof(StrArr)/sizeof(char*))) {
    //    if(StrArr[index] != NULL) {
    //        free(StrArr[index]);
    //    }
        StrArr[index] = NULL;
        index++;
    }
    index = 0;
    result = strtok( Line, delims );
   
    while( (result != NULL)  && (index < MAX_STRING_ARRAY_ELEMENT) ) {
        length = strlen(result);
        StrArr[index] = (char *)malloc(length+1);
        strcpy(StrArr[index], result);
        //printf( "result is \"%s\"\n", StrArr[index] );
        index++;
        result = strtok( NULL, delims );
    }
}


void PrintArrayOfString(char *StrArr[]) {
	int index = 0;
	while(StrArr[index] != NULL) {
		//printf("result is : %s\n", StrArr[index]);
		index++;
	}
}

int FreeArrayOfString(char * Ptr[]){
	int index = 0;
	while( (Ptr[index] != NULL)){
		//printf("%s **\n", Ptr[index]);
		free(Ptr[index]);
		index++;
	}
}
/************Experimant purpose******************/
#if 0
int main (){
	//char str[] = "now ,is the time for all ,good men to come to the ,aid of their country";
	char str[] = ",,,,,,,,,,,,";
/*
	char delims[] = "#";
	char *result = NULL;
	result = strtok( str, delims );
	while( result != NULL ) {
		printf( "result is \"%s\"\n", result );
		result = strtok( NULL, delims );
	}
*/
	char *StrArr[MAX_STRING_ARRAY_ELEMENT];
	CreateArrayOfString(StrArr, str);
	PrintArrayOfString(StrArr);
	FreeArrayOfString(StrArr);
}
#endif
/************Experimant purpose******************/


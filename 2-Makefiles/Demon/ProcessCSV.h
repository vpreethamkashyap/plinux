#ifndef PROCESS_CSV
#define PROCESS_CSV

int FreeArrayOfString(char * Ptr[]);
void PrintArrayOfString(char *StrArr[]);
void CreateArrayOfString(char *StrArr[], char *Line);
void StringSplit(char *StrArr[], char *Line, char *delimiters);
int GetLine(FILE *fp, char * line_buf);

#endif

#ifndef PROCESS_CSV
#define PROCESS_CSV

int FreeArrayOfString(char * Ptr[]);
void PrintArrayOfString(char *StrArr[]);
void CreateArrayOfString(char *StrArr[], char *Line);
int GetLine(FILE *fp, char * line_buf);

#endif

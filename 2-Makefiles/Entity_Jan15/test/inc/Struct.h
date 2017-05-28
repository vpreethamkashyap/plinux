
typedef struct{
	char Weight[10];
	char Comma;
	char Hight[10];
	char Comma2;
	char Gender[10];
	char Comma3;
	char Age[10];
}_INPUT_DATA_STRUCT;

typedef struct{
	char *Name;
	char *Password;
}_LOGIN_DATA_STRUCT;

typedef struct{
	char InBuf[10];
}_IN_FILE_STRUCT;


typedef struct{
	char Weight[10];
	char Comma;
	char BmiValue[10];
}_BMI_TEST_STRUCT;

typedef struct{
	char SysP[10];
	char Comma1;
	char DiaP[10];
	char Comma2;
	char PulseRate[10];
	char Comma3;
	char ErrorCode[4];
}_BP_TEST_STRUCT;

typedef struct{
	char BliValue[10];
}_BLI_TEST_STRUCT;

typedef struct{
	char LoginReply[15];
	char Name[64];
	char Age[8];
	char Gender[8];
}_LOGIN_TEST_STRUCT;




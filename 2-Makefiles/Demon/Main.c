#include "Main.h"
#include <sys/time.h>
#include <sqlite3.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#define BAUDRATE B38400

#define IN_TEXT_FILE                "MDB/in.txt"
#define IN_BP_FILE				"MDB/abort.txt"
#define IN_ENTERY_FILE           "MDB/Inpt.csv"
#define OT_TEXT_FILE               "MDB/out.txt"
#define OT_ENTERY_FILE          "MDB/Data.csv"
#define USER_INFO_FILE           "MDB/user.csv"
//-----Used by UI---
#define LOGIN_SUMMARY_FILE		"MDB/login_sum.csv"
#define BMI_SUMMARY_FILE		"MDB/bmi_sum.csv"
#define BMI_RAW_FILE			"MDB/bmi_raw.csv"
#define BP_SUMMARY_FILE			"MDB/bp_sum.csv"
#define BF_SUMMARY_FILE			"MDB/bf_sum.csv"
#define BF_RAW_FILE			"MDB/bf_raw.csv"
#define CO_SUMMARY_FILE			"MDB/co_sum.csv"
#define BP_DUMPS_FILE			"MDB/bp_dumps.csv"

#define SMS_SEND_FILE 			"MDB/SMS.txt"
#define DAEMON_DB_FILE			"MDB/bmi.db"
//-----Used by UI---
#define USER_SUMMARY_FILE		"MDB/user_summary.csv"

#define WEIGHT_CHECK_TIMEOUT_SEC	30
#define BF_CHECK_TIMEOUT_SEC		30
#define CO_CHECK_TIMEOUT_SEC		90
#define BP_CHECK_TIMEOUT_SEC		150

volatile int WELLTH_CHECK_TIMEOUT_SEC=180;
#define EVENT_DEMO

#define CO_PORT_OPEN_TIMEOUT_SEC	3

char openCO_port ();

typedef struct{
	char Weight[10];
	char Comma;
	char Hight[10];
	char Comma2;
	char Gender[10];
	char Comma3;
	char Age[10];
}_INPUT_DATA;
_INPUT_DATA Din;


typedef struct{
	char *Name;
	char *Password;
}_LOGIN_DATA;
_LOGIN_DATA Uin;
char CurRFIDScaned[16]; 

typedef struct{
	char InBuf[10];
}_IN_FILE;
_IN_FILE Indata;

typedef struct{
	char Weight[10];
	char Comma;
	char BmiValue[10];
}_BMI_TEST;
_BMI_TEST Bmi;

typedef struct{
	char SysP[10];
	char Comma1;
	char DiaP[10];
	char Comma2;
	char PulseRate[10];
	char Comma3;
	char ErrorCode[4];
}_BP_TEST;
_BP_TEST Bp;

typedef struct{
	char BliValue[10];
}_BLI_TEST;
_BLI_TEST Bli;

typedef struct{
	char LoginReply[15];
	char Name[64];
	char Age[8];
	char Gender[8];
}_LOGIN_TEST;
_LOGIN_TEST login;


char *SerialPortName[] = {	"/dev/ttyUSB0",
							"/dev/ttyUSB1",
							"/dev/ttyUSB2",
							"/dev/ttyUSB3",
							"/dev/ttyUSB4",
							"/dev/ttyUSB5",
							"/dev/ttyUSB6",
							"/dev/ttyUSB7",
							"/dev/ttyUSB8",
							"/dev/ttyUSB9",    
							"/dev/ttyS0",
							"/dev/ttyS1",                                                           
							"/dev/ttyS2",
							"/dev/ttyS3",
							"/dev/ttyS4",
							"/dev/ttyS5",
							"/dev/ttyS6",
							"/dev/ttyS7",
							"/dev/ttyS8",
							"/dev/ttyS9"
						};
char UName[32];

/********************************************************************************************
			Function Declarations
*********************************************************************************************/
void CheckTest(void);
void CallWhileLoop(void);
void ReadInputFile(void);
void CheckAbortFile(void);
void CheckUserInfo(void);
void CheckEndOfTest(void);
void DisplayMessage(void);
char OpenSerialPort(void);   	
void CompareUserInfo(void);
float ConvertHexToFloat(void);
void ClearDemonInputFile();
void clearSummaryFile(void);
void f(void);
extern unsigned char  ModbusOP(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer, unsigned char  numRetries);
extern unsigned char  ConstructRequest(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer,MDB_REQ_ADU *MbReqAdu, MDB_RSP_ADU *MbRspAdu);
extern int flush_flag;
/********************************************************************************************
			Variable Declarations
*********************************************************************************************/
int fd, RFID_fd, CO_fd;
FILE *fp;

FILE* fp1, *fpUI, *sms_fp;

float BMIValue;
float BLIValue;
int baud,TestNo;
char cbuf, UserMode=0;
char SerialPortStatus = 0;
short int MdbResponse = 0;	
int Hight=0,TempWeight;
int Age = 0;
char Gender[10];
char UserName[10];
char UserPassword[10];
unsigned char MdbFlag = 0;
unsigned char RxBuf[100];
unsigned char TxBuf[30];
unsigned char BmiBuf[10];
unsigned char TempBuf[10];
volatile unsigned int LoopCase = 1;
unsigned char Buf[5];
float Weight,Sub,Mul;
char sms_buf[512];
char number[16];
	
extern volatile unsigned char BmiTestEn;
extern volatile unsigned char BpTestEn;
extern volatile unsigned char BliTestEn;
extern unsigned char HoldingReg[10];
extern int HR;


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	int rowpr=argc-1;
	NotUsed=0;

	for(i=0; i<rowpr; i++)
		printf("%s ",azColName[i]);

	printf("%s\n",azColName[rowpr]);

	for(i=0; i<rowpr; i++){
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		printf("%s ",  argv[i] ? argv[i] : "NULL");
	}
	printf("%s\n",  argv[rowpr] ? argv[rowpr] : "NULL");

	return 0;
}
/********************************************************************************************
			Main Starts Here
*********************************************************************************************/
int main(void){
    //CompareUserInfo();
    //while(1);

	ClearDemonInputFile();
    OpenSerialPort();
	memset(CurRFIDScaned, 0, 16);
#if 0
	sleep(15);
	// Send Dummy SMS
	strcpy(number,"919980521263");
	strcpy(sms_buf,"Wellth Station Booted Up \n");
	printf("SMS to---------- %s", number);
	printf("SMS is --\n %s", sms_buf);
	//use prolific (pl2303) USB-serial convertor
	int sms_fd = open_sms_port();
	//getSignalStrength(sms_fd);
	selectSMSFormat(sms_fd, "text");
	sendSMSTo(sms_fd, number, sms_buf);
	nu_SerialComPort_Close (sms_fd);
	sleep(15);
	//sleep(200);
	strcpy(number,"919980521263");
	strcpy(sms_buf,"Wellth Station Booted Up \n");
	printf("SMS to---------- %s", number);
	printf("SMS is --\n %s", sms_buf);
	//use prolific (pl2303) USB-serial convertor
	sms_fd = open_sms_port();
	//getSignalStrength(sms_fd);
	selectSMSFormat(sms_fd, "text");
	sendSMSTo(sms_fd, number, sms_buf);
	nu_SerialComPort_Close (sms_fd);
#endif
/*
	while(1){
		memset(CurRFIDScaned, 0, 16);
		read(RFID_fd, CurRFIDScaned, 16);
		printf("%s",CurRFIDScaned);
	}
*/
//	system("/bin/dmesg | grep \"pl2303 converter now\" > /home/ab.c");
	//system("/bin/xinput\ set-prop 11 'Coordinate Transformation Matrix' 8 0 0 0 8 0 0 0 1");
	//system("/bin/xinput\ set-prop 10 'Coordinate Transformation Matrix' 8 0 0 0 8 0 0 0 1");

    if(SerialPortStatus==1){
        LoopCase = 1;
        MdbFlag = 0;
        printf(" Wellth System is running \n");
        CallWhileLoop();
        close(fd);
    }
    else{
    	return 0;
    }
}

void ReadInputFile(void){
    FILE *ffp,*fp;
    ffp = fopen (IN_TEXT_FILE, "r");
    if(ffp<0){
        printf(" System is not able to open file \n");
       LoopCase = 0;    
    }
    else{
        fread(&Indata,sizeof(Indata),1,ffp);
        fclose(ffp);
        if(strcmp(Indata.InBuf,"WeTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 1;
        }
        else if(strcmp(Indata.InBuf,"BpTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 2;
        }
        else if(strcmp(Indata.InBuf,"BliTest") == 0){
            memset(Indata.InBuf,0,10);
            TestNo = 3;
        }
	else if (strcmp(Indata.InBuf,"CoTest") == 0) {
		memset(Indata.InBuf,0,10);
		TestNo = 4;
	}
	else if (strcmp(Indata.InBuf,"EcgTest") == 0) {
		memset(Indata.InBuf,0,10);
		TestNo = 6;
	}
	else if (strcmp(Indata.InBuf,"EcgCheck") == 0) {
		memset(Indata.InBuf,0,10);
		TestNo = 7;
	}
    else if(strcmp(Indata.InBuf,"Login") == 0){
			printf("\n*******login flag set\n");
            memset(Indata.InBuf,0,10);
            UserMode = 1;
        }
	else if (strcmp(Indata.InBuf,"Swipe") == 0) {
		memset(Indata.InBuf,0,10);
		// flush RFID input
		tcflush(RFID_fd,TCIOFLUSH);
		UserMode = 2;
	}
	else if (strcmp(Indata.InBuf,"SMS") == 0) {
		memset(Indata.InBuf,0,10);
		TestNo = 5;
	}
        else{
            TestNo =0;
			UserMode = 0;
        }
       LoopCase = 1;    
    }
	//printf("loop case=%s", Indata.InBuf);
}

struct timeval start, end;
long prevSecVal = 0;
int testStartTime =0;
char tmpBLIValue[10];
char tmpBLIValue1[10];
float temp_bli_val;
char query[512];

void CallWhileLoop(void){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char timeBuf[64];
	char Line[512];
	FILE *fpt;
	struct timeval tv;
	int tod_flag,ret;
	char syscommand[128];
	int GenderVal;
	float Duerenberg,OttoHassler;
	float TmpBLIVal, TmpBMIVal;

	FILE * app_fp = fopen("/home/time_app.c", "w");
	system("/bin/chmod 777 /home/time_app.c");
	fchmod (app_fp, S_IROTH | S_IWOTH | S_IXOTH);
	fclose(app_fp);	
	tod_flag = 0;
	while(1){
		if (LoopCase != 1){
			/*****************************
			check the time if it is more than 2 min then 
			1) clear the daemon input files
			2) give a msg to the UI that sensors are not responding
			3) change loopcase to 1
			*************************/
 			gettimeofday(&start, NULL);
			if(prevSecVal != start.tv_sec){
				prevSecVal = start.tv_sec;
				testStartTime++;
				printf("\n__%d__\n", testStartTime);
			}
		} else {
			testStartTime = 0;
		}
		if(testStartTime > WELLTH_CHECK_TIMEOUT_SEC){
			LoopCase = 1;
			ClearDemonInputFile();	
			printf("/**********************/\nRetry Test..! No Responce From Sensor resetted the Daemon....!\n/**********************/\n");
		}
		if(BpTestEn ==1){
			CheckAbortFile();
		}

		switch(LoopCase){		
			case 1:
				usleep(40000);
				ReadInputFile();
				CheckTest();
				CheckUserInfo();
			break;
	//*************************Sensor No 1 Interface*********************************//
			case 2:
				printf("Entered Case 2 \n");
				WELLTH_CHECK_TIMEOUT_SEC = WEIGHT_CHECK_TIMEOUT_SEC;

				printf(" loop case value is = %d", LoopCase);
				HoldingReg[1] = 0x00;   
				HoldingReg[0] = 0x01;
				MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000A, 0x000l, (unsigned char *)HoldingReg,1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				} else{
					printf("Modbus Error Response %d \n",MdbResponse);
					HoldingReg[1] = 0x00;   
					HoldingReg[0] = 0x00;
					LoopCase = LoopCase +1;
				}
			break;			
			case 3:
				printf(" loop case value is = %d", LoopCase);
				MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
				if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
					LoopCase = LoopCase +1;
					BmiTestEn = 1;
				}
			break;
			case 4:   
				printf(" loop case value is = %d", LoopCase);   
				MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000A, 0x0002, (unsigned char *)HoldingReg, 1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				} else {  
					Weight = ConvertHexToFloat();
					printf("Modbus Got Sensor Response\n");
					printf("Your Weight is = %f\n",Weight); 
					if(Weight < 0)
						Weight *= (-1);

					BMIValue  = (Weight/Hight)*10000;
					BMIValue = BMIValue / Hight;
					printf("Your BMI Level is = %f\n",BMIValue);   
					Buf[0] = '1';
					memset(TempBuf,0,10);
					sprintf(TempBuf,"%f",Weight);
					strcpy(Bmi.Weight,TempBuf);
					memset(TempBuf,0,10);
					sprintf(TempBuf,"%f",BMIValue);
					strcpy(Bmi.BmiValue,TempBuf);
					memset(TempBuf,0,10);

					fp = fopen (OT_ENTERY_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(&Bmi,sizeof(Bmi),1,fp);
						fclose(fp);
					}

					fpUI = fopen (BMI_SUMMARY_FILE, "w"); //open file in append mode now onwards
					printf("1>>BMI summary file opened : %s\n", BMI_SUMMARY_FILE);
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						printf("BMI summary file opened : %s\n", BMI_SUMMARY_FILE);
						printf(">>>>>>>>weight:%s bmi-%s height-- %s",Bmi.Weight, Bmi.BmiValue, Din.Hight);
						Bmi.Comma = ',';
						fwrite(Bmi.Weight,strlen(Bmi.Weight),1,fpUI);
						fwrite(&Bmi.Comma,1,1,fpUI);
						fwrite(Bmi.BmiValue,strlen(Bmi.BmiValue),1,fpUI);
						fwrite(&Bmi.Comma,1,1,fpUI);
						fwrite(Din.Hight, strlen(Din.Hight), 1, fpUI);
						fclose(fpUI);
					}
					/**************************raw write************************/

					fpUI = fopen (BMI_RAW_FILE, "w"); //open file in append mode now onwards
					printf("1>>BMI summary file opened : %s\n", BMI_RAW_FILE);
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(Bmi.Weight,strlen(Bmi.Weight),1,fpUI);
						fclose(fpUI);
					}		
					/*************************database loging**************************/
					system("/bin/date > /home/time.c");
					fpt = fopen("/home/time.c", "r");
					while( GetLine(fpt, Line) != 0){
						strcpy(timeBuf, Line);
						//printf("%s\n", Line);
					}
					sprintf(query, "insert into bmi_t (weight, bmi, height, log_time) values ('%s', '%s', '%s', '%s') ", Bmi.Weight, Bmi.BmiValue, Din.Hight, timeBuf);
					if (sqlite3_open(DAEMON_DB_FILE, &db) != SQLITE_OK)
					{
						fprintf(stderr, "Can't open database: \n");
						sqlite3_close(db);
						exit(1);
					}
					rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
					if( rc!=SQLITE_OK ){
						fprintf(stderr, "SQL error: %s\n", zErrMsg);
					}
					sqlite3_close(db);
					//fclose(fpUI);

					fp = fopen (OT_TEXT_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					}
					else{
						fwrite(&Buf,1,1,fp);
						fclose(fp);
					}
					printf(" Demon has completed the  Wellth BMI Test\n");
					BmiTestEn = 0;
					LoopCase = 1;
					printf("LoopCase Value is %d\n",LoopCase);
					fp  = fopen(IN_ENTERY_FILE,"w");
					fclose(fp);
					fp = fopen(IN_TEXT_FILE,"w");
					fclose(fp);                    
				}
			break;
			case 5:
			break;
             //*************************Sensor No 2 Interface*********************************//
			case 6:	
				WELLTH_CHECK_TIMEOUT_SEC = BP_CHECK_TIMEOUT_SEC;
				BpTestEn = 1;
				printf(" loop case value is = %d", LoopCase);	
				HoldingReg[1] = 0x00;   
				HoldingReg[0] = 0x01;
				MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000B, 0x000l, (unsigned char *)HoldingReg,1);
				if(MdbResponse!=0){
					// #if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					// #endif
				}
				else{
					HoldingReg[1] = 0x00;   
					HoldingReg[0] = 0x00;
					LoopCase = LoopCase +1;
				}
			break;			
			case 7:
			if (tod_flag == 0)
			{
				gettimeofday( &tv,NULL);
				printf(" Case 7 : Time - %d - \n",tv.tv_sec);
				tod_flag = 1;
			}
				printf(" loop case value is = %d", LoopCase);
				MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
				if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
					LoopCase = LoopCase +1;
					BpTestEn = 1;
				}
			break;
			case 8:  
				printf(" loop case value is = %d", LoopCase);    
				MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000B, 0x0002, (unsigned char *)HoldingReg, 1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				} else {  
					printf("Modbus Got Sensor Response\n");
					printf("Systolic Pressure is = %d\n",BmiBuf[0]);   
					printf("Diastolic Pressure is = %d\n",BmiBuf[1]);   
					printf("Pulse Rate is = %d\n",BmiBuf[2]); 
					printf("Error Code is = %d\n",BmiBuf[3]);   
					BpTestEn = 0;

					sprintf(Bp.SysP,"%d",BmiBuf[0]);
					sprintf(Bp.DiaP,"%d",BmiBuf[1]);
					sprintf(Bp.PulseRate,"%d",BmiBuf[2]);
					sprintf(Bp.ErrorCode,"%d",BmiBuf[3]);

					fp = fopen (OT_ENTERY_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					}
					else{
						fwrite(&Bp,sizeof(Bp),1,fp);
						fclose(fp);
					}
					Buf[0] = ',';
					/**************************Summary file************************/
					fpUI = fopen (BP_SUMMARY_FILE, "w"); //open file
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(Bp.SysP,strlen(Bp.SysP),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.DiaP,strlen(Bp.DiaP),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.PulseRate,strlen(Bp.PulseRate),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.ErrorCode,strlen(Bp.ErrorCode),1,fpUI);
						strcpy(Buf, "\r\n");
						fwrite(Buf, 2, 1, fpUI);
						fclose(fpUI);
					}
					/**************************raw write************************/
					fpUI = fopen (BP_DUMPS_FILE, "a"); //open file in append mode now onwards
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(Bp.SysP,strlen(Bp.SysP),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.DiaP,strlen(Bp.DiaP),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.PulseRate,strlen(Bp.PulseRate),1,fpUI);
						fwrite(&Buf[0],1,1,fpUI);
						fwrite(Bp.ErrorCode,strlen(Bp.ErrorCode),1,fpUI);
						strcpy(Buf, "\r\n");
						fwrite(Buf, 2, 1, fpUI);
						fclose(fpUI);
					}
					/**************************database loging************************/
					system("/bin/date > /home/time.c");
					fpt = fopen("/home/time.c", "r");
					while( GetLine(fpt, Line) != 0){
						strcpy(timeBuf, Line);
						//printf("%s\n", Line);
					}
					sprintf(query, "insert into bp_t (sbp_val, dbp_val, pr_val, log_time) values ('%s', '%s', '%s', '%s') ", Bp.SysP, Bp.DiaP, Bp.PulseRate, timeBuf);

					if (sqlite3_open(DAEMON_DB_FILE, &db) != SQLITE_OK)
					{
						fprintf(stderr, "Can't open database: \n");
						sqlite3_close(db);
						exit(1);
					}
					rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
					if( rc!=SQLITE_OK ){
						fprintf(stderr, "SQL error: %s\n", zErrMsg);
					  }
					  sqlite3_close(db);

					Buf[0] = '1';
					fp = fopen (OT_TEXT_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					}
					else{
						fwrite(&Buf,1,1,fp);
						fclose(fp);
					}
					printf(" Demon has completed the  Wellth BMI Test\n");
					LoopCase = 1;
					printf("LoopCase Value is %d\n",LoopCase);
					fp  = fopen(IN_ENTERY_FILE,"w");
					fclose(fp);
					fp = fopen(IN_TEXT_FILE,"w");
					fclose(fp);   
				}
			break;       
         //*************************Sensor No 3 Interface*********************************//
			case 9:
				printf(" loop case value is = %d", LoopCase);
				LoopCase = LoopCase +1;
			break;  			 	  
			case 10:
				WELLTH_CHECK_TIMEOUT_SEC = BF_CHECK_TIMEOUT_SEC;

				printf(" loop case value is = %d", LoopCase);		
				HoldingReg[1] = 0x00;   
				HoldingReg[0] = 0x01;
				MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000C, 0x000l, (unsigned char *)HoldingReg,1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				} else {
					HoldingReg[1] = 0x00;   
					HoldingReg[0] = 0x00;
					LoopCase = LoopCase +1;
				}
			break;			
			case 11:
				printf(" loop case value is = %d", LoopCase);
				MdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
				if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01)){
					LoopCase = LoopCase +1;
					BpTestEn = 1;
				}
			break;
			case 12:    
				printf(" loop case value is = %d", LoopCase);  
				MdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000C, 0x0002, (unsigned char *)HoldingReg, 1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				} else {  
					BliTestEn =  1;
					BLIValue = ConvertHexToFloat();
					printf("Modbus Got Sensor Response\n");
					printf("Sensor Response is  = %f\n",BLIValue); 
					sprintf(tmpBLIValue,"%f", BLIValue);
					tmpBLIValue[5] = 0;  
					temp_bli_val = atof(tmpBLIValue);
					if( (temp_bli_val >= 3.276) || (temp_bli_val <= 0.000) ) {
						strcpy(Bli.BliValue, "-1");
					} else {
						BLIValue  = BLIValue*10000;
						Mul = (Hight*Hight)/BLIValue;
						Sub  = 12.297 + (0.287*Mul);
						BLIValue  = 0.697 * TempWeight;
						printf("temp weight %d", TempWeight);
						BLIValue = BLIValue  - Sub;
						printf("Your BMI Level is = %f\n",BLIValue);   
						LoopCase = 1;
						BliTestEn =  0;
						Buf[0] = '1';
						if (BLIValue < 30.0)
						{
						memset(TempBuf,0,10);
						sprintf(TempBuf,"%f",BLIValue);
						strcpy(Bli.BliValue,TempBuf);
						memset(TempBuf,0,10);
						}
						else
						{
						
							if ( (strcmp(Gender,"Male") == 0) || (strcmp(Gender,"MALE") == 0 ) || (strcmp(Gender,"male") == 0 ) )
								GenderVal = 1;
							else
								GenderVal = 0;
							
						printf ("BMI Calc - Weight - %d Height - %d  GenderVal - %d ",TempWeight,Hight,GenderVal);

							Duerenberg = (( (1.2 * TempWeight * 10000) / (Hight * Hight)) + (0.23 * Age ) - (10.8 * GenderVal ) - 5.4);

							if (GenderVal)
							OttoHassler =  ((( 0.9 * TempWeight * 10000) / (Hight * Hight) ) - 8.2 );
							else
							OttoHassler = (( (0.94 * TempWeight * 10000 ) / (Hight * Hight) ) + 4.3 );

							if (GenderVal)
							{
								TmpBLIVal = ( BLIValue + Duerenberg ) / 2;

							}
							else
							{
								TmpBMIVal = ( TempWeight * 10000) / ( Hight * Hight) ;
								if ( TmpBMIVal > 23.0 )
								{
								if ( BLIValue > OttoHassler)
									TmpBLIVal = OttoHassler;
								else
									TmpBLIVal = BLIValue;



								}
								else
								{

								if ( BLIValue > Duerenberg )
									TmpBLIVal = Duerenberg;
								else
									TmpBLIVal = BLIValue;

								}



							}
						printf(" BLI Calc  Duerenberg - %f OttoHassler - %f BLIVal - %f \n", Duerenberg, OttoHassler,TmpBLIVal);

						memset(TempBuf,0,10);
						sprintf(TempBuf,"%f",TmpBLIVal);
						strcpy(Bli.BliValue,TempBuf);
						memset(TempBuf,0,10);



						}


					}
					fp = fopen (OT_ENTERY_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					}
					else{
						fwrite(&Bli,sizeof(Bli),1,fp);
						fclose(fp);
					}
					/**************************raw write************************/
					fpUI = fopen (BF_RAW_FILE, "w"); //open file in append mode now onwards
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(tmpBLIValue,strlen(tmpBLIValue),1,fpUI);
						fclose(fpUI);
					}
					/**************************summary file write************************/
					fpUI = fopen (BF_SUMMARY_FILE, "w"); //open file in append mode now onwards
					if(fpUI<0){
						printf(" System is not able to open file \n");
					} else {
						fwrite(Bli.BliValue,strlen(Bli.BliValue),1,fpUI);
						fclose(fpUI);
					}
					
					fp = fopen (OT_TEXT_FILE, "w");
					if(fp<0){
						printf(" System is not able to open file \n");
					}
					else{
						fwrite(&Buf,1,1,fp);
						fclose(fp);
					}
					printf(" Demon has completed the  Wellth BLI Test\n");
					BliTestEn = 0;
					BpTestEn = 0;
					LoopCase = 1;
					printf("LoopCase Value is %d\n",LoopCase);
					fp  = fopen(IN_ENTERY_FILE,"w");
					//fflush(fp);
					fclose(fp);
					//fclose(fp);
					fp = fopen(IN_TEXT_FILE,"w");
					//fflush(fp);
					fclose(fp);            
					#if 1
						/**************************database loging************************/
						system("/bin/date > /home/time.c");
						fpt = fopen("/home/time.c", "r");
						while( GetLine(fpt, Line) != 0){
							strcpy(timeBuf, Line);
							//printf("%s\n", Line);
						}
						sprintf(query, "insert into bf_t (bf_val, log_time) values ('%s', '%s') ", Bli.BliValue, timeBuf);

						if (sqlite3_open(DAEMON_DB_FILE, &db) != SQLITE_OK)
						{
							fprintf(stderr, "Can't open database: \n");
							sqlite3_close(db);
							exit(1);
						}
						rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
						if( rc!=SQLITE_OK ){
							fprintf(stderr, "SQL error: %s\n", zErrMsg);
						}
						sqlite3_close(db);
					#endif
				}
			break; 
			//*************************Sensor No 4 Interface (CO-smoke)*********************************//
			case 13:
				WELLTH_CHECK_TIMEOUT_SEC = CO_CHECK_TIMEOUT_SEC;
				printf(" loop case value is = %d", LoopCase);
				printf("\ngoing to operate CO-sensor\n");
				OperateCOSensor();
			break;
			case 14:
				printf(" loop case value is = %d", LoopCase);	
				HoldingReg[1] = 0xAA;   
				HoldingReg[0] = 0xAA;
				MdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000B, 0x000l, (unsigned char *)HoldingReg,1);
				if(MdbResponse!=0){
					#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",MdbResponse);
					#endif
				}
				else{
					HoldingReg[1] = 0x00;   
					HoldingReg[0] = 0x00;
					LoopCase = 1;
					BpTestEn = 0;
					fp = fopen (IN_BP_FILE , "w");
					fflush(fp);
					fclose(fp);
					// fp = fopen (BP_SUMMARY_FILE , "w");
					// fflush(fp);
					// fclose(fp);
				}
			break;
				case 15:
				printf(" sendin sms - loop case value is = %d", LoopCase);
				sms_fp = fopen(SMS_SEND_FILE, "r"); //read sms from file
				if(sms_fp == NULL){
					printf("Sms file can't open");
				} else {
					fread(sms_buf, sizeof(sms_buf), 1, sms_fp);
					fclose(sms_fp);
				}

				fp = fopen (IN_ENTERY_FILE, "r"); //read number to which msg to send
				if(fp<0){
					printf(" System is not able to open file \n");
				}
				else{
					fread(number,sizeof(number),1,fp);
					fclose(fp);
				}
				printf("SMS to---------- %s", number);
				printf("SMS is --\n %s", sms_buf);
				//use prolific (pl2303) USB-serial convertor
				int sms_fd = open_sms_port();
				//getSignalStrength(sms_fd);
				selectSMSFormat(sms_fd, "text");
				sendSMSTo(sms_fd, number, sms_buf);
				nu_SerialComPort_Close (sms_fd);
				LoopCase = 1;
				printf("LoopCase Value is %d\n",LoopCase);
				fp  = fopen(IN_ENTERY_FILE,"w");
				fflush(fp);
				fclose(fp);
				//fclose(fp);
				fp = fopen(IN_TEXT_FILE,"w");
				fflush(fp);
				fclose(fp);            
				//fclose(fp);
			break;
        case 16 :
                sleep(1);
                ret = ecgread();
		if (ret)
		{
                ret = readdump();
		ret = heartrate();
        //        system("split -d -nl/2 ../data/FirstDump_2 ../data/ecgplot_firstch");
         //       system("split -d -nl/2 ../data/SecDump_2 ../data/ecgplot_secch");
                //system("gnuplot ecgscript");
          //      system("gnuplot ecgplotscript");

		sprintf(syscommand,"./plotfile %d ",HR);
		system(syscommand);

		sprintf(syscommand,"cp ../plot/ecgplot.png ../plot/ecgplot_%s.png",UName);
		system(syscommand);
		}
		else
		{
		system("cp ../plot/blankplot.png ../plot/ecgplot.png");

		}


                LoopCase = 1;
                Buf[0] = '1';
                    fp = fopen (OT_TEXT_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Buf,1,1,fp);
                        fclose(fp);
                    }
            fp  = fopen(IN_ENTERY_FILE,"w");
                        fflush(fp);
            fclose(fp);
            //fclose(fp);
            fp = fopen(IN_TEXT_FILE,"w");
                        fflush(fp);
            fclose(fp);
                break;

        case 17 :
                sleep(1);
                ret = autoscan();


                LoopCase = 1;
                Buf[0] = '1';
                    fp = fopen (OT_TEXT_FILE, "w");
                    if(fp<0){
                        printf(" System is not able to open file \n");
                    }
                    else{
                        fwrite(&Buf,1,1,fp);
                        fclose(fp);
                    }
		fp = fopen (OT_ENTERY_FILE, "w");
		if (ret)
			Buf[0] = '1';
		else
			Buf[0] = '0';

		fwrite(&Buf,1,1,fp);
		fclose(fp);

            fp  = fopen(IN_ENTERY_FILE,"w");
                        fflush(fp);
            fclose(fp);

            fp = fopen(IN_TEXT_FILE,"w");
                        fflush(fp);
            fclose(fp);
                break;
			default:
			break;
		}
	}
}

void OperateCOSensor(void){
	FILE *fp, *fpUI;
	char co_sensor_val[32];
	char CharArr[512];
    char *ArrStr[4];
    char *ArrOfStr[32];
    char *StrPtr;
    char StrSerialPortName[64];
    int len, co_started, i, st_co_reading, prev_co_reading, cur_co_reading;
    int delta, blowing_started;
    char co_start, out_char;
    float ratio;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char timeBuf[64];
	char Line[512];
	FILE *fpt;

	//	close(fd);
	//	close(RFID_fd);
	//	close(CO_fd);
	//	OpenSerialPort();
	//	openCO_port();
	printf("opening serial port is done\n");

	co_start = 0;
	prevSecVal = 0;
	co_started = 0;
	st_co_reading = 0;
	prev_co_reading = 0;
	cur_co_reading = 0;
	delta = 0; blowing_started = 0;
	printf("%cskjhdkjdshkfjhds\n--",co_start);
	while( 1 ){
		printf("%c--%d",co_start, LoopCase);
		if (LoopCase == 13){
			/*****************************
			check the time if it is more than 2 min then 
			1) clear the daemon input files
			2) give a msg to the UI that sensors are not responding
			3) change loopcase to 1
			*************************/
			gettimeofday(&start, NULL);
			if(prevSecVal != start.tv_sec){
				prevSecVal = start.tv_sec;
				testStartTime++;
				printf("\n__%d__\n", testStartTime);
			}
		} else {
			testStartTime = 0;
		}
		if(testStartTime > WELLTH_CHECK_TIMEOUT_SEC){
			LoopCase = 1;
			ClearDemonInputFile();
			printf("/**********************/\nRetry Test..! No Responce From Sensor resetted the Daemon....!\n/**********************/\n");
			break;
		}
		if(co_started == 0){
			//while(read(CO_fd, &co_start, sizeof(co_start)) <= 0);
			//read(CO_fd, &co_start, sizeof(co_start));
			nu_SerialComPort_BlockRead(CO_fd, &co_start, sizeof(co_start));
			//printf("%d -- %c\n",CO_fd, co_start);
		}
		if(co_start == 'A' || co_start == '5'){
			for(i=0; i<32; i++){
				ArrOfStr[i] = NULL;
			}
			memset(CharArr, 0, sizeof(CharArr));
			printf("enterin in serial reads");
			prev_co_reading = cur_co_reading;
			nu_SerialComPort_BlockRead(CO_fd, CharArr, sizeof(CharArr));
			printf("entering in split");
			StringSplit(ArrOfStr , CharArr, " ");
			if(st_co_reading == 0) {
				printf("\nCo-sensor start value = %d\n", st_co_reading);
				if(ArrOfStr[18] != NULL) {
					st_co_reading = atoi(ArrOfStr[9]);
					cur_co_reading = st_co_reading;
					co_started = 1;
					printf("\nCo-sensor start value = %d\n", st_co_reading);
				}
			} else {
				cur_co_reading = atoi(ArrOfStr[9]);
				printf("\nCo-sensor  value = %d\n", cur_co_reading);
				//if(prev_co_reading < cur_co_reading)
				delta =    st_co_reading - cur_co_reading;
				if(delta > 1000)
				blowing_started = 1;
				if(blowing_started == 1){
					if(prev_co_reading < cur_co_reading) {
						ratio = (float)st_co_reading / (float)cur_co_reading;
						break;
					}
				}
			}
			//co_started = 1;
			FreeArrayOfString(ArrOfStr);
		}
	}
	printf("%s\n",ArrOfStr[9]);
	//FreeArrayOfString(ArrOfStr);
	printf("the ratio is = %f\n", ratio);
	sprintf(co_sensor_val, "%f", ratio);
	/****************************/
	fp = fopen (OT_ENTERY_FILE, "w");
	if(fp<0){
		printf(" System is not able to open file \n");
	} else {
		fwrite(co_sensor_val, strlen(co_sensor_val), 1, fp);
		fclose(fp);
	}
	/****************************/
	fpUI = fopen (CO_SUMMARY_FILE, "w"); //open file in append mode now onwards
	if(fpUI<0){
		printf(" System is not able to open file \n");
	} else {
		fwrite(co_sensor_val, strlen(co_sensor_val), 1, fpUI);
		fclose(fpUI);
	}

	//----------------------database loging--------------------------------------------------
	system("/bin/date > /home/time.c");
	fpt = fopen("/home/time.c", "r");
	while( GetLine(fpt, Line) != 0){
		strcpy(timeBuf, Line);
		//printf("%s\n", Line);
	}
	sprintf(query, "insert into co_t (co_val, log_time) values ('%s', '%s') ", co_sensor_val, timeBuf);

	if (sqlite3_open(DAEMON_DB_FILE, &db) != SQLITE_OK)
	{
		fprintf(stderr, "Can't open database: \n");
		sqlite3_close(db);
		exit(1);
	}
	rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	}
	sqlite3_close(db);
	/****************************/
	out_char = '1';
	fp = fopen (OT_TEXT_FILE, "w");
	if(fp<0){
		printf(" System is not able to open file \n");
	}
	else{
		fwrite(&out_char,1,1,fp);
		fclose(fp);
	}
	printf(" Demon has completed the  Wellth CO Test\n");
	LoopCase = 1;
	/****************************/
	printf("LoopCase Value is %d\n",LoopCase);
	fp  = fopen(IN_ENTERY_FILE,"w");
	fclose(fp);
	fp = fopen(IN_TEXT_FILE,"w");
	fclose(fp);     
}

char MODBUS_USB[32];
char CO_PORT_USB[32];
char RFID_PORT_USB[32];
char ECG_PORT_USB[32];
int SRL_index;

char OpenSerialPort(void){
	FILE *rfid_fp;
	char PrevLine[512];
	char Line[512];
	char *ArrStr[4], cha = 0;
	char *StrPtr, co_start;
	char StrSerialPortName[64];
	int len, i, dum_fd;
	int j,ecg_fd,ret,ECG_Port_Found;
	struct termios options;
	speed_t baudRate;
	char readBuf[64];
	char rfid_junk_reads[64];
	/********************Open RFID connected serial port*********************/
		system("/bin/dmesg | grep \"FTDI USB Serial Device converter now\" > /home/ab.c");
		rfid_fp = fopen("/home/ab.c", "r");
		while( GetLine(rfid_fp, Line) != 0){
			//StrPtr = strstr(Line, "FTDI USB Serial Device converter now attached to");
			//if(StrPtr != NULL){
			//	strcpy(PrevLine, Line);
			//}
			strcpy(PrevLine, Line);
			//printf("%s\n", Line);
		}
		printf("---\n %s\n", PrevLine);
		StrPtr = strstr(PrevLine, "FTDI USB Serial Device converter now attached to");
		if(StrPtr == NULL) {
			printf("\n******************************************\nError : The RFID Sensor is not connected\n******************************************\n");
		} else {
			StrPtr = strstr(PrevLine, "tty");
			strcpy(StrSerialPortName, "/dev/");
			strcat(StrSerialPortName, StrPtr);
			len = strlen(StrSerialPortName);
			printf(">>> %s -- %d\n", StrSerialPortName, len);
			StrSerialPortName[len] = 0;
			strcpy(RFID_PORT_USB,StrSerialPortName);
			RFID_fd = ArgOpenSerialPort(StrSerialPortName, 9600);
			if (RFID_fd > 0)
			{
				read(RFID_fd, rfid_junk_reads,33);
				for (i = 0; i < 10; i++)
				{
					if ( strcmp(SerialPortName[i],RFID_PORT_USB) == 0)
					{
						SRL_index = i;
						break;
					}
				}
				close(RFID_fd);
				RFID_fd = -1;
			}
		}

	

	/********************Open Co-Processor connected serial port*********************/

	memset(MODBUS_USB, 0, sizeof(MODBUS_USB));
	fd=-1;

	fd = ArgOpenSerialPort("/dev/ttyO4", 9600);
		if (fd < 0){
			printf("\nAlert: reconnect the master co-processor port USB and restart the daemon");
			return 0;
		} else {
			SerialPortStatus = 1;
		}
	if(fd < 0) {
		printf("__Error : The Co-Processor is not connected __");
		return 0;
	}

#if 0
	system("/bin/dmesg | grep \"pl2303 converter now\" > /home/ab.c");
	//system("/bin/dmesg | grep \"cp210x converter now\" > /home/ab.c");
	rfid_fp = fopen("/home/ab.c", "r");
	while( GetLine(rfid_fp, Line) != 0){
		strcpy(PrevLine, Line);
		//printf("%s\n", Line);
	}
	printf("---\n %s\n", PrevLine);
	StrPtr = strstr(PrevLine, "pl2303 converter now attached to");
	//StrPtr = strstr(PrevLine, "cp210x converter now attached to");
	if(StrPtr == NULL) {
		printf("\n******************************************\nError : The Co-Processor is not connected\n******************************************\n");
		return 0;
	} else {
		StrPtr = strstr(PrevLine, "tty");
		strcpy(StrSerialPortName, "/dev/");
		strcat(StrSerialPortName, StrPtr);
		len = strlen(StrSerialPortName);
		printf(">>>%s -- %d\n", StrSerialPortName, len);
		StrSerialPortName[len] = 0;
		strcpy(MODBUS_USB, StrSerialPortName);
		fd = ArgOpenSerialPort(StrSerialPortName, 9600);
		if (fd < 0){
			printf("\nAlert: reconnect the master co-processor port USB and restart the daemon");
			return 0;
		} else {
			SerialPortStatus = 1;
		}
	}
	if(fd < 0) {
		printf("__Error : The Co-Processor is not connected __");
		return 0;
	}
#endif
#if 0
	/********************Open CO-sensor connected serial port*********************/
	prevSecVal= 100;
	testStartTime = 0;
    i=0;
	memset(CO_PORT_USB, 0, sizeof(CO_PORT_USB));
	CO_fd = -1;
    while(i<20){
		if (strcmp(SerialPortName[i], MODBUS_USB) ) {
			printf("\n-----%s----\n", SerialPortName[i]);
		  	dum_fd = ArgOpenSerialPort(SerialPortName[i], 9600);//nu_SerialComPort_Open(SerialPortName[i]);
			if(dum_fd < 0) {
				//printf("\nAlert: reconnect the CO sensor ( CO- sensor USB) and restart the daemon");
				//return 0;
				//break;
		    }
			else{
				testStartTime = 0;
				while( 1 ){
					//printf("%c--",co_start);
					/*****************************
					check the time if it is more than 2 min then 
					1) clear the daemon input files
					2) give a msg to the UI that sensors are not responding
					3) change loopcase to 1
					*************************/
					gettimeofday(&start, NULL);
					if(prevSecVal != start.tv_sec){
						prevSecVal = start.tv_sec;
						testStartTime++;
						//printf("\n__%d__\n", testStartTime);
					}

					if(testStartTime > CO_PORT_OPEN_TIMEOUT_SEC+1){
						//printf("/**********************/\nRetry Test..! No Responce From Sensor resetted the Daemon....!\n/**********************/\n");
						break;
					}
					read(dum_fd, &co_start, sizeof(co_start));
					//nu_SerialComPort_BlockRead(fd, &co_start, sizeof(co_start));
					//printf("-%d%c-",fd, co_start);
					if(co_start == 'A'){
						//this is the CO sensor port**************************
						printf("CO sensor is connected to %s discriptor=%d\n ",SerialPortName[i], dum_fd);
						strcpy(CO_PORT_USB, SerialPortName[i]);
						CO_fd = dum_fd;
						//SerialPortStatus = 1;
				        break;
					}
				}
				if(CO_fd > 0) {
					break; //break;
				}
			}
		}
	    i++;
    }


	printf("--%d--\n", CO_fd);
#endif

	/***************Identify ECG Port**********************************/

	sleep(1);
	memset(ECG_PORT_USB, 0, sizeof(ECG_PORT_USB));
        i = 0;
	ECG_Port_Found = 0;

        while ( i < 10 )
        {
                printf ( "Serial Port : %s \n",SerialPortName[i]);
		if (strcmp (SerialPortName[i],RFID_PORT_USB) == 0)
		{
			i++;
			continue;
		}
                ecg_fd = open (SerialPortName[i], O_RDWR | O_NOCTTY | O_NONBLOCK);
                if (ecg_fd < 0)
                {
                        i++;
                        continue;
                }
                else
                {
                        printf (" %s port opened \n", SerialPortName[i]);
                        bzero(&options, sizeof(options));
                        options.c_cflag =  BAUDRATE | CS8 | CLOCAL | CREAD;
                        options.c_iflag = IGNPAR;
                        options.c_oflag = 0;

                        baudRate = B38400;
                        cfsetispeed(&options, baudRate);
                        cfsetospeed(&options, baudRate);

                        /* set input mode (non-canonical, no echo,...) */
                        options.c_lflag = 0;

                        options.c_cc[VTIME]    = 0;
                        options.c_cc[VMIN]     = 0;

                        tcflush(ecg_fd, TCIOFLUSH);
                        ret =  tcsetattr(ecg_fd,TCSANOW,&options);
                        if ( ret < 0)
                        {
                                printf("tcsetattr failed for %s \n",SerialPortName[i]);
                        }

                        // Try Ten Times
                        j = 0;

                        while ( j < 10)
                        {

				if (flush_flag)
				{
					tcflush(ecg_fd,TCIOFLUSH);
					flush_flag = 0;
				}
                                ret = write (ecg_fd, "N" , 1);
                                if ( ret < 0)
                                {
                                        perror("write failed \n");
                                }

                                bzero(&readBuf,sizeof(readBuf));
                                ret = read ( ecg_fd, readBuf , 10 );
                                if ( ret < 0)
                                {
                                        perror("read failed \n");
                                }
                                else
                                {
                                        printf("-%s- \n",readBuf);

                                }

				if (( ret > 0) && ( ret < 10))
					flush_flag = 1;

                                if ((readBuf[0] == 'S') && (readBuf[9] == 'T'))
                                {
                                        printf ("ECG Port is : %s \n",SerialPortName[i]);
                                        // return(1);
					strcpy(ECG_PORT_USB, SerialPortName[i]);
					ECG_Port_Found = 1;
					break;

                                }


                                usleep(7700);
                                j++;

                        }

			if (ECG_Port_Found)
				break;
                        i++;
			tcflush(ecg_fd,TCIOFLUSH);
                        close(ecg_fd);
                        // continue;


                }
        }
        if ( i >= 10)
        {

                printf("ECG Port not connected or not working properly \n");
                // return(0);
        }
	if (ecg_fd > 0)
		close (ecg_fd);







	/********************Open RFID connected serial port*********************/

#if 0
	i = 0; RFID_fd = -1;
	char rfid_junk_reads[64];

    while(i<20){
		printf("%s\n", SerialPortName[i]);
		if ( (! strcmp(SerialPortName[i], MODBUS_USB)) || (! strcmp(SerialPortName[i], CO_PORT_USB)) || (! strcmp(SerialPortName[i], MODBUS_USB))) {
		} else {
			RFID_fd = ArgOpenSerialPort(SerialPortName[i], 9600);
			if(RFID_fd < 0) {
				printf("Alert: reconnect the RFID port USB and restart the daemon \n");
			//return 0;
			} else {
				break;
			}
		}
		i++;
	}
	if(RFID_fd > 0){
		printf("RFID is connected to %s discriptor=%d\n ",SerialPortName[i], RFID_fd);
		read(RFID_fd, rfid_junk_reads,33);
		close(RFID_fd);
		SRL_index = i;
		RFID_fd = -1;
	}
#endif
	//================**oo**oo**=============================================


/*
		fd = ArgOpenSerialPort("/dev/ttyUSB0", 9600);
		if(fd < 0) {
			//printf("\nNOTE: reconnect the ttyUSB2 ( CO- sensor USB)----");
			printf("\n-- OR -- Connect co-processor USB 1st, RFID USB 2nd & CO-sensor 3rd..\n");
		} else {
			printf("\n---------------- The Co-Processor is connected--------------\n");
			SerialPortStatus = 1;
		}	


		RFID_fd = ArgOpenSerialPort("/dev/ttyUSB1", 9600);
		if(RFID_fd < 0) {
			//printf("\nNOTE: reconnect the ttyUSB2 ( CO- sensor USB)----");
			printf("\n-- OR -- Connect co-processor USB 1st, RFID USB 2nd & CO-sensor 3rd..\n");
		} else {
			printf("\n----------------RFID is connected to USB1--------------\n");
		}
    int i=0;
    while(i<20){
      	fd = nu_SerialComPort_Open(SerialPortName[i]);
	    if(fd < 0) {
        }
	    else{
 	        printf("Able to open the SerialPort %s \n ",SerialPortName[i]);
  	        SerialPortStatus = 1;
            break;
	    }
	    i++;
	    
    }

    if(SerialPortStatus != 0){
        baud = 9600;    //atoi(argv[2]);
    	if(nu_SerialComPort_Init(fd, baud) < 0 ){
    		printf("baud not set");
		    return 0;
    	} 
    }
    else{
            printf("Unable to open the SerialPort \n ");
   		    return ;
    }
    return 1;
*/
}

char openCO_port(){
	char co_start;
	int i;
/********************Open CO-sensor connected serial port*********************/
	prevSecVal= 100;
	testStartTime = 0;
    i=0;
	memset(CO_PORT_USB, 0, sizeof(CO_PORT_USB));
	CO_fd = -1;
    while(i<20){
		if (strcmp(SerialPortName[i], MODBUS_USB) ) {
			printf("\n-----%s----\n", SerialPortName[i]);
		  	fd = nu_SerialComPort_Open(SerialPortName[i]);
			if(fd < 0) {
//				printf("\nAlert: reconnect the CO sensor ( CO- sensor USB) and restart the daemon");
//				return 0;
		    }
			else{
				testStartTime = 0;
				while( 1 ){
					//printf("%c--",co_start);
					/*****************************
					check the time if it is more than 2 min then 
					1) clear the daemon input files
					2) give a msg to the UI that sensors are not responding
					3) change loopcase to 1
					*************************/
					gettimeofday(&start, NULL);
					if(prevSecVal != start.tv_sec){
						prevSecVal = start.tv_sec;
						testStartTime++;
						//printf("\n__%d__\n", testStartTime);
					}

					if(testStartTime > CO_PORT_OPEN_TIMEOUT_SEC+2){
						//printf("/**********************/\nRetry Test..! No Responce From Sensor resetted the Daemon....!\n/**********************/\n");
						break;
					}
					read(fd, &co_start, sizeof(co_start));
					//nu_SerialComPort_BlockRead(fd, &co_start, sizeof(co_start));
					//printf("-%d%c-",fd, co_start);
					if(co_start == 'A'){
						//this is the CO sensor port**************************
						printf("Able to open the SerialPort %s \n ",SerialPortName[i]);
						strcpy(CO_PORT_USB, SerialPortName[i]);
						CO_fd = fd;
						//SerialPortStatus = 1;
				        break;
					}
				}
			}
		}
		if(CO_fd > 0)
			break;
	    i++;
    }
	printf("--%d--", CO_fd);
}
void DisplayMessage(void){
 	printf("You are in Wellth System \n");
	printf("Enter 1 To Check Your BMI Level\n");
	printf("Enter 2 To Check Your Blood Pressure  \n");
	printf("Enter 3 To Check Your BLI Level\n");
}

float ConvertHexToFloat(void){
        float Result;
        signed int Bmi;
        long int Byte1=0,Byte2=0,Byte3=0,Byte4=0;
        
        if(BliTestEn){
          Byte1 = BmiBuf[1];
            Byte2  = BmiBuf[0];
            Byte2 = (Byte2<<8);
            Byte3 = BmiBuf[3];
            Byte3 = (Byte3<<16);
            Byte4= BmiBuf[2];
            Byte4  = (Byte4<<24);
        }        
        else
        {        
            Byte1 = BmiBuf[0];
            Byte2  = BmiBuf[1];
            Byte2 = (Byte2<<8);
            Byte3 = BmiBuf[2];
            Byte3 = (Byte3<<16);
            Byte4= BmiBuf[3];
            Byte4  = (Byte4<<24);
        }        
        Bmi = (Byte1| Byte2| Byte3|Byte4);    
        printf("The int value is %x \n",Bmi);    
        Result = *((float *)&Bmi);     
        return Result;
}

void CheckTest(void){
    if(TestNo == 1){
         LoopCase = 2;    
        printf("Demon Code has received the Hight = ");
        fp = fopen (IN_ENTERY_FILE, "r");
        if(fp<0){
            printf(" System is not able to open file \n");
        }
        else{
            fread(&Din,sizeof(Din),1,fp);
            fclose(fp);
        }
        sscanf(Din.Hight,"%d",&Hight);
        //memset(Din.Hight,0,10);
        printf("%d\n",Hight);
        printf("\n");     
        printf("BMI Test Starts Now \n");             
    }
    else if(TestNo == 2){
        printf("Bp Test Starts Now \n");
        LoopCase = 6;    
    }
    else if(TestNo == 3){
        printf("BLI Test Starts now \n");      
        printf("Demon Code has received the Hight = ");
        fp = fopen (IN_ENTERY_FILE, "r");
        if(fp<0){
            printf(" System is not able to open file \n");
        }
        else{
            fread(&Din,sizeof(Din),1,fp);
            fclose(fp);
        }
        sscanf(Din.Weight,"%d",&TempWeight);
        sscanf(Din.Hight,"%d",&Hight);
	strcpy(Gender,Din.Gender);
        sscanf(Din.Age,"%d",&Age);
        memset(Din.Weight,0,10);
        memset(Din.Hight,0,10);
        memset(Din.Gender,0,10);
        memset(Din.Age,0,10);
        printf("The Hight Value %d\n",Hight);
        printf("%d\n",Hight);
        printf("The Weight Value %d\n",TempWeight);
        printf("The Gender Value %s\n",Gender);
        printf("The Age  Value %d\n",Age);
        printf("BLI Test Starts now \n");      
        LoopCase = 9;  
        printf("\n");     
    }
	else if(TestNo == 4){
		LoopCase = 13;   
		printf("Co Test Starts now \n");
	}
	else if(TestNo == 5){
		LoopCase = 15;   
		printf("Sending sms starts now \n");
	}
	else if(TestNo == 6){
		LoopCase = 16;   
		printf("Taking ecg starts now \n");
	}
	else if(TestNo == 7){
		LoopCase = 17;   
		printf("Checking ecg starts now \n");
	}
    else{
        LoopCase = 1;    
    }
}

char Line[512];
char *DemonArrOfCol[8];
char *ArrayOfCol[32];

void CheckUserInfo(void){
	char CharArr[12];
        int cu_scb_ret;

	memset(CurRFIDScaned, 0, 16);
	if(UserMode==1){
    	printf("Demon Code has received the User Login information\n ");
	    fp = fopen (IN_ENTERY_FILE, "r");
	    if(fp<0){
	        printf(" System is not able to open file \n");
	    }
	    else{
			if(GetLine(fp,Line)){
				//printf("size of array of string %d", sizeof(DemonArrOfCol));
				//printf("size of array of column %d", sizeof(ArrayOfCol));
				CreateArrayOfString(DemonArrOfCol,Line);					
			}	
	        fclose(fp);
	    }
	   	Uin.Name = DemonArrOfCol[0];
		Uin.Password  = DemonArrOfCol[1];
		strcpy(UName,Uin.Name);
		printf("The User Name %s\n",Uin.Name);
		printf("The User Password %s\n",Uin.Password);
		printf("DataBase Test Starts now \n");          
		CompareUserInfo();
	}
	else if (UserMode == 2){
			//if(GetLine(fp,Line)){
	if(RFID_fd == -1){
//		RFID_fd = ArgOpenSerialPort("/dev/ttyUSB0", 9600);
		RFID_fd = ArgOpenSerialPort(SerialPortName[SRL_index], 9600);
		if(RFID_fd < 0) {
			printf("Alert: reconnect the RFID port USB and restart the daemon \n");
			//return 0;
		}
		if(RFID_fd > 0){
			printf("RFID is connected to %s discriptor=%d\n ","/dev/ttyUSB0", RFID_fd);
		}
	}
//			nu_SerialComPort_BlockRead(RFID_fd, CurRFIDScaned, 1);
			printf("%s", CurRFIDScaned);
			read(RFID_fd, CurRFIDScaned,1);
//			read(RFID_fd, CurRFIDScaned, 13);
//			read(RFID_fd,CurRFIDScaned, 2);
			if(CurRFIDScaned[0] != 0) {
				printf("swipe");
				nu_SerialComPort_BlockRead(RFID_fd, CurRFIDScaned, 13);
				printf("%s\n",CurRFIDScaned);
				printf("%s\n",CurRFIDScaned);
				printf("%s\n",CurRFIDScaned);
				if(CurRFIDScaned[0] != 0){
					CompareUserInfo();
				}
			}
		//}
	}
	// printf("Out of check user info \n");
}

void CompareUserInfo(void){
		FILE* fp1, *fpUI;
        char Buf,NoOfCommas =0,Index=0;
        char TempUserName[20], ch;
		unsigned char UNMatched = 0, PWDMatched = 0, RFIDMatched = 0;
		unsigned char UNColNum = 11;
		unsigned char PWDColNum = 12;  
		unsigned char NameColNum = 8;
		unsigned char AgeColNum = 13;
		unsigned char RFIDColNum = 14;
		unsigned char GenderColNum = 4;
		char *ptr_CurRFIDScaned, *ptr_nxtline, *ptr_CSV_RFIDStored;
		printf("compairing user info");
		if(UserMode == 2){
//			if(CurRFIDScaned[0] != 0){
				ptr_CurRFIDScaned = strstr(CurRFIDScaned,"80");
				if(ptr_CurRFIDScaned == NULL){
					close(RFID_fd);
					RFID_fd = -1;
					return;
				} else {
					close(RFID_fd);
					RFID_fd = -1;
				}
				ptr_nxtline = strchr(CurRFIDScaned, '\n');
				*ptr_nxtline = '\0';
				printf("\n-------------%s", CurRFIDScaned);
//			}
		}
        printf("\nDemon Code has started the comparison of  Login information\n ");
        UNMatched = 0; PWDMatched = 0; RFIDMatched = 0;
        fp1 = fopen (USER_INFO_FILE, "r");
        if(fp1<0){
            printf(" System is not able to open file \n");
        }
        else{
			while(1){
				if(GetLine(fp1,Line)){
					printf("----> Line: %s\n", Line);
					CreateArrayOfString(ArrayOfCol,Line);
					if(UserMode == 1){
/**** Login success for key pad case
						if (strcmp(ArrayOfCol[UNColNum-1],Uin.Name) == 0) {
							UNMatched = 1;
							if(strcmp(ArrayOfCol[PWDColNum-1],Uin.Password) == 0){
								PWDMatched = 1;
							}
						}
********/
			UNMatched = 1;
			PWDMatched = 1;
						if(UNMatched == 1 && PWDMatched == 1) {
							strcpy(login.LoginReply, "LOGIN_SUCCESS");
							strcpy(login.Name, ArrayOfCol[NameColNum-1]);
							strcpy(login.Age, ArrayOfCol[AgeColNum-1]);
							strcpy(login.Gender, ArrayOfCol[GenderColNum-1]);
							clearSummaryFile();
							if(RFID_fd != -1){
								close(RFID_fd);
								RFID_fd = -1;
							}
							break;
						} else {
							//printf("--wrong user name / PWD---- \n");
							strcpy(login.LoginReply, "LOGIN_FAILED");
							strcpy(login.Name, "NULL");
							strcpy(login.Age, "NULL");
							strcpy(login.Gender, "NULL");
							if(RFID_fd != -1){
								close(RFID_fd);
								RFID_fd = -1;
							}
						}
					}
					if(UserMode == 2){
					printf("\ncompairing\n");
						//if(strcmp(ArrayOfCol[RFIDColNum-1], CurRFIDScaned) == 0){
						printf("\n--%s-- == --%s--\n", ArrayOfCol[RFIDColNum-1], ptr_CurRFIDScaned);
						ptr_CSV_RFIDStored = ArrayOfCol[RFIDColNum-1]+1;
//						if(strcmp(ArrayOfCol[RFIDColNum-1], ptr_CurRFIDScaned) == 0) {
						if(strcmp(ptr_CSV_RFIDStored, ptr_CurRFIDScaned) == 0) {
							RFIDMatched = 1;
						}
						printf("\nafter compairing\n");
						if (RFIDMatched == 1){ 
							strcpy(login.LoginReply, "LOGIN_SUCCESS");
							strcpy(login.Name, ArrayOfCol[NameColNum-1]);
							strcpy(login.Age, ArrayOfCol[AgeColNum-1]);
							strcpy(login.Gender, ArrayOfCol[GenderColNum-1]);
							clearSummaryFile();
							close(RFID_fd);
							RFID_fd = -1;
							break;
						} else {
							close(RFID_fd);
							RFID_fd = -1;
						}
					}

				} else {
					break;
				}
			}
			fclose(fp1); // close USER_INFO_FILE
			
			if(UserMode == 2){
				if( RFIDMatched == 0 ) {
					memset(CurRFIDScaned, 0, sizeof(CurRFIDScaned));
					close(RFID_fd);
					RFID_fd = -1;
					return;
				}
			}
			
            fp1 = fopen (OT_ENTERY_FILE, "w");
            if(fp1<0){
                printf(" System is not able to open file \n");
            }
            else{
                fwrite(login.LoginReply, strlen(login.LoginReply), 1, fp1);
				ch = ',';
				fwrite(&ch, 1, 1, fp1);
				fwrite(login.Name, strlen(login.Name), 1, fp1);
				fwrite(&ch, 1, 1, fp1);
				fwrite(login.Age, strlen(login.Age), 1, fp1);
				fwrite(&ch, 1, 1, fp1);
				fwrite(login.Gender, strlen(login.Gender), 1, fp1);
				
				fpUI = fopen(LOGIN_SUMMARY_FILE, "w");
				if(fp1<0){
                	printf(" System is not able to open file \n");
	            } else {
					fwrite(login.Name, strlen(login.Name), 1, fpUI);
					fwrite(&ch, 1, 1, fpUI);
					fwrite(login.Age, strlen(login.Age), 1, fpUI);
					fwrite(&ch, 1, 1, fpUI);
					fwrite(login.Gender, strlen(login.Gender), 1, fpUI);
					fclose(fpUI);
				}
				
				//ch = '\0';
				//fwrite(&ch, 1, 1, fp1);
                //fclose(fp);
            }
            fclose(fp1); // close OT_ENTERY_FILE

			UserMode= 0;
			Buf = '1';
            fp1 = fopen (OT_TEXT_FILE, "w");
            if(fp1<0){
                printf(" System is not able to open file \n");
            }
            else{
                fwrite(&Buf,1,1,fp1);
            }
			fclose(fp1); // close OT_TEXT_FILE

			FreeArrayOfString(DemonArrOfCol);
			FreeArrayOfString(ArrayOfCol);
			ClearDemonInputFile();
        }
	// printf("Out of COmpare User Info \n");
}

void ClearDemonInputFile(){
	FILE *fp1;
	fp1 = fopen (IN_TEXT_FILE, "w");
	fclose(fp1);
	fp1 = fopen (IN_ENTERY_FILE, "w");
	fclose(fp1);
	fp1 = fopen (IN_BP_FILE, "w");
	fclose(fp1);
}
void CheckAbortFile(void){
	FILE *ffp;
	char in_bp_buf[10];

    ffp = fopen (IN_BP_FILE, "r");
    if(ffp<0){
        printf(" System is not able to open file \n");
       LoopCase = 0;    
    } else {
		fread(in_bp_buf,sizeof(in_bp_buf),1,ffp);
		fclose(ffp);
		ClearDemonInputFile();
		//printf("----------------in abort");
		if (strcmp(in_bp_buf,"Abort") == 0) {
			memset(in_bp_buf,0,10);
			TestNo = 0;
			BpTestEn = 0;
			LoopCase = 14;
			testStartTime = WELLTH_CHECK_TIMEOUT_SEC-1;
		}
	}
}

void clearSummaryFile(void){
	fpUI = fopen (BF_SUMMARY_FILE, "w"); 
	fclose(fpUI);
	fpUI = fopen (BMI_SUMMARY_FILE, "w");
	fclose(fpUI);
	fpUI = fopen (BP_SUMMARY_FILE, "w");
	fclose(fpUI);
	fpUI = fopen (CO_SUMMARY_FILE, "w");
	fclose(fpUI);
}
	

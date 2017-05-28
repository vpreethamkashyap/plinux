#include"../inc/Header.h"

// Declaration of Local variables

extern _INPUT_DATA_STRUCT		Din;
extern _LOGIN_DATA_STRUCT		Uin;
extern _IN_FILE_STRUCT 			Indata;
extern _BMI_TEST_STRUCT 			Bmi;
extern _BP_TEST_STRUCT				Bp;
extern _BLI_TEST_STRUCT			Bli;
extern _LOGIN_TEST_STRUCT		login;

extern int LoopState;
extern int Hight,TempWeight; 
extern unsigned char RxBuf[100];
extern unsigned char HoldingReg[10];
extern unsigned short int BpTestEn;
extern unsigned short int BmiTestEn;
extern unsigned short int BliTestEn;

// Declaration of Local variables

float BMIValue;
float Weight,Sub,Mul;

unsigned char Buf[5];
unsigned char BmiMdbResponse = 0;
unsigned char BmiSwitchIndex = 0;


// Declaration of functions
void RunBmiMdbTest(void);
void CalculateBmi(void );
void UpdateBmi_RawFile(void );
void UpdateBmi_DataBase(void );
void UpdateBmi_SummaryFile(void );	

/*************************************************************************************************************
**		function 	 		:	 	RunBmiMdbTest
**		Definition   	:		Read the weight value from Co-Processor Board
**
**************************************************************************************************************/
void RunBmiMdbTest(void)
{
	switch(BmiSwitchIndex)
	{
		case 0:
			//WELLTH_CHECK_TIMEOUT_SEC = WEIGHT_CHECK_TIMEOUT_SEC;
			HoldingReg[1] = 0x00;   
			HoldingReg[0] = 0x01;
			BmiMdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000A, 0x000l, (unsigned char *)HoldingReg,1);
			if(BmiMdbResponse!=0)
			{
				#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",BmiMdbResponse);
				#endif
			} 
			else
			{
				printf("Modbus Error Response %d \n",BmiMdbResponse);
				HoldingReg[1] = 0x00;   
				HoldingReg[0] = 0x00;
				BmiSwitchIndex = BmiSwitchIndex +1;
			}
		break;		
		case 1:
			BmiMdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
			if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01))
			{
				BmiSwitchIndex = BmiSwitchIndex +1;
				BmiTestEn = 1;
			}
		break;

		case 2:   
			BmiMdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000A, 0x0002, (unsigned char *)HoldingReg, 1);
			if(BmiMdbResponse!=0)
			{
				#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",BmiMdbResponse);
				#endif
			} 
			else 
			{  
				Weight = ConvertHexToFloat();
				printf("Modbus Got Sensor Response\n");
				printf("Your Weight is = %f\n",Weight); 
				if(Weight < 0)
				{
					Weight *= (-1);
				}
				CalculateBmi();
				#ifndef GTK_DISABLE
					UpdateBmi_SummaryFile();		
					UpdateBmi_RawFile();
					UpdateBmi_DataBase();
				#endif
				LoopState = DO_LOOP_TEST;	
				return;
			}
		break;
	}
	return;
}

/********************************************************************************************************
**
**	Function Name	: 	CalculateBmi
** Description 		:		This function clculates the BMI value and update to file that shared by  GTK UI
**
*********************************************************************************************************/
void CalculateBmi(void)
{
	FILE *fp;
	
	unsigned char TempBuf[10];
	
	// Calculate BMI Value
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
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
		fwrite(&Bmi,sizeof(Bmi),1,fp);
		fclose(fp);
	}
}

/********************************************************************************************************
**
**	Function Name	: 	UpdateBmi_SummaryFile
** Description 		:		This function clculates the BMI value and update to Summary file 
**
*********************************************************************************************************/

void	UpdateBmi_SummaryFile(void)
{
	FILE *fpUI;
	//open file in append mode now onwards
	fpUI = fopen (BMI_SUMMARY_FILE, "w"); 
	printf("1>>BMI summary file opened : %s\n", BMI_SUMMARY_FILE);
	if(fpUI<0)
	{
		printf(" System is not able UpdateBmi_RawFileto open file \n");
	} 
	else 
	{
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
}

/********************************************************************************************************
**
**	Function Name		: 	UpdateBmi_RawFile
**  Description 		:		This function clculates the BMI value and update to Raw file 
**
*********************************************************************************************************/

void UpdateBmi_RawFile(void)
{
	FILE *fp;
	/**************************raw write************************/

	fp = fopen (BMI_RAW_FILE, "w"); //open file in append mode now onwards
	printf("1>>BMI summary file opened : %s\n", BMI_RAW_FILE);
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
		fwrite(Bmi.Weight,strlen(Bmi.Weight),1,fp);
		fclose(fp);
	}	
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
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

/********************************************************************************************************
**
**	Function Name		: 	UpdateBmi_DataBase
** 	Description 		:		This function clculates the BMI value and update to Database file 
**
*********************************************************************************************************/

void UpdateBmi_DataBase(void)
{	
	#if defined DATABASE_INTERFACE_EN
	
		FILE *fpt,*fp;
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char timeBuf[64];
		char Line[512];
		char query[512];
		/*************************database loging**************************/
		system("/bin/date > /home/time.c");
		fpt = fopen("/home/time.c", "r");
		while( GetLine(fpt, Line) != 0)
		{
			strcpy(timeBuf, Line);
		}
		sprintf(query, "insert into bmi_t (weight, bmi, height, log_time) values ('%s', '%s', '%s', '%s') ", Bmi.Weight, Bmi.BmiValue, Din.Hight, timeBuf);
		
		if (sqlite3_open(DAEMON_DB_FILE, &db) != SQLITE_OK)
		{
			fprintf(stderr, "Can't open database: \n");
			sqlite3_close(db);
			exit(1);
		}
		
		rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
		
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		}
		sqlite3_close(db);

		fp = fopen (OT_TEXT_FILE, "w");
		if(fp<0)
		{
			printf(" System is not able to open file \n");
		}
		else
		{
			fwrite(&Buf,1,1,fp);
			fclose(fp);
		}
		printf(" Demon has completed the  Wellth BMI Test\n");
		BmiTestEn = 0;
		BmiSwitchIndex = 1;
		printf("BmiSwitchIndex Value is %d\n",BmiSwitchIndex);
		fp  = fopen(IN_ENTERY_FILE,"w");
		fclose(fp);
		fp = fopen(IN_TEXT_FILE,"w");
		fclose(fp); 
	#endif       
}



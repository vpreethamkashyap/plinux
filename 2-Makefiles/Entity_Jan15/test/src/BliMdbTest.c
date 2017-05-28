#include"../inc/Header.h"

struct timeval tv;

// Declaration of functions

void RunBliTest(void);
void CalculateBli(void);
void UpdateBli_RawFile(void );
void UpdateBli_DataBase(void );
void UpdateBli_SummaryFile(void );		
extern int callback(void *NotUsed, int argc, char **argv, char **azColName);

// Declaration of extern variables

extern _INPUT_DATA_STRUCT		Din;
extern _LOGIN_DATA_STRUCT		Uin;
extern _IN_FILE_STRUCT 			Indata;
extern _BMI_TEST_STRUCT 			Bmi;
extern _BP_TEST_STRUCT				Bp;
extern _BLI_TEST_STRUCT			Bli;
extern _LOGIN_TEST_STRUCT		login;

extern int LoopState;
extern int Hight,TempWeight;
extern unsigned char MdbRawBuf[10];
extern unsigned short int BmiTestEn;
extern unsigned short int BpTestEn;
extern unsigned short int BliTestEn;
extern unsigned char HoldingReg[10];
extern unsigned char RxBuf[100];

// Declaration of Local variables

int GenderVal;
float BLIValue;
float RawBliVal;
float Weight,Mul,Sub;
float Duerenberg,OttoHassler;
float TmpBLIVal, TmpBMIVal;

unsigned char Buf[5];
unsigned char tmpBLIValue[10];
unsigned char tmpBLIValue1[10];
unsigned char BliMdbResponse = 0;
unsigned char BliSwitchIndex = 0;

/*************************************************************************************************************
**		function 	 		:	 	RunBliMdbTest
**		Definition   	:		Tests the Body Level FAT
**
**************************************************************************************************************/

void RunBliMdbTest(void)
{
	switch(BliSwitchIndex)
	{
		case 0: 			 	  
		//WELLTH_CHECK_TIMEOUT_SEC = BF_CHECK_TIMEOUT_SEC;
		printf(" loop case value is = %d", BliSwitchIndex);		
		HoldingReg[1] = 0x00;   
		HoldingReg[0] = 0x01;
		BliMdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000C, 0x000l, (unsigned char *)HoldingReg,1);
		if(BliMdbResponse!=0)
		{
			#if defined	SHOW_DISPLAY
				printf("Modbus Error Response %d \n",BliMdbResponse);
			#endif
		} 
		else 
		{
			HoldingReg[1] = 0x00;   
			HoldingReg[0] = 0x00;
			BliSwitchIndex = BliSwitchIndex +1;
		}
		break;			
		
		case 1:
			printf(" loop case value is = %d", BliSwitchIndex);
			BliMdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
			if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01))
			{
				BliSwitchIndex = BliSwitchIndex +1;
				BpTestEn = 1;
			}
		break;
		
		case 2:    
			printf(" loop case value is = %d", BliSwitchIndex);  
			BliMdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000C, 0x0002, (unsigned char *)HoldingReg, 1);
			if(BliMdbResponse!=0)
			{
				#if defined	SHOW_DISPLAY
				printf("Modbus Error Response %d \n",BliMdbResponse);
				#endif
			} 
			else 
			{  
				BliTestEn =  1;
				BLIValue = ConvertHexToFloat();
				printf("Modbus Got Sensor Response\n");
				printf("Sensor Response is  = %f\n",BLIValue); 
				sprintf(tmpBLIValue,"%f", BLIValue);
				tmpBLIValue[5] = 0;  
				RawBliVal = atof(tmpBLIValue);
				if( (RawBliVal >= 3.276) || (RawBliVal <= 0.000) ) 
				{
					strcpy(Bli.BliValue, "-1");
				} 
				else 
				{
					CalculateBli();
					#ifndef GTK_DISABLE
						UpdateBli_RawFile();
						UpdateBli_DataBase();
						UpdateBli_SummaryFile();
					#endif
					LoopState = DO_LOOP_TEST;	
					return;			
				}
			}
		break; 
	}
}

/********************************************************************************************************
**
**	Function Name		: 	CalculateBli
** 	Description 		:		This function clculates the BLI value and update to file that shared by  GTK UI
**
*********************************************************************************************************/
void CalculateBli(void)
{
	FILE *fp;
	int Age = 0;
	char Gender[10];
	unsigned char TempBuf[10];
	
	BLIValue  = BLIValue*10000;
	Mul = (Hight*Hight)/BLIValue;
	Sub  = 12.297 + (0.287*Mul);
	BLIValue  = 0.697 * TempWeight;
	printf("temp weight %d", TempWeight);
	BLIValue = BLIValue  - Sub;
	printf("Your BMI Level is = %f\n",BLIValue);   
	BliSwitchIndex = 1;
	BliTestEn =  0;
	Buf[0] = '1';
	if (BLIValue < 30.0)
	{
		memset(TempBuf,0,10);
		sprintf(TempBuf,"%f",BLIValue);
		strcpy(Bli.BliValue,TempBuf);
		memset(TempBuf,GenderVal,10);
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
	
	fp = fopen (OT_ENTERY_FILE, "w");
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	}
	else
	{
		fwrite(&Bli,sizeof(Bli),1,fp);
		fclose(fp);
	}
}		

/********************************************************************************************************
**
**	Function Name		: 	UpdateBli_RawFile
** 	Description 		:		This function clculates the BLI value and update to Raw file 
**
*********************************************************************************************************/

void UpdateBli_RawFile(void )
{
	FILE *fpUI;
	fpUI = fopen (BF_RAW_FILE, "w"); //open file in append mode now onwards
	if(fpUI<0)
	{
		printf(" System is not able to open file \n");
	}
	else 
	{
		fwrite(tmpBLIValue,strlen(tmpBLIValue),1,fpUI);
		fclose(fpUI);
	}
}

/********************************************************************************************************
**
**	Function Name		: 	UpdateBli_SummaryFile
** 	Description 		:		This function clculates the BLI value and update to Summary file 
**
*********************************************************************************************************/

void UpdateBli_SummaryFile(void )
{
	FILE *fpUI,*fp;
	fpUI = fopen (BF_SUMMARY_FILE, "w"); //open file in append mode now onwards
	if(fpUI<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
		fwrite(Bli.BliValue,strlen(Bli.BliValue),1,fpUI);
		fclose(fpUI);
	}

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
	printf(" Demon has completed the  Wellth BLI Test\n");
	BliTestEn = 0;
	BpTestEn = 0;
	BliSwitchIndex = 1;
	printf("BliSwitchIndex Value is %d\n",BliSwitchIndex);
	fp  = fopen(IN_ENTERY_FILE,"w");
	fclose(fp);
	
	fp = fopen(IN_TEXT_FILE,"w");
	fclose(fp); 
}

/********************************************************************************************************
**
**	Function Name		: 	UpdateBmi_DataBase
** 	Description 		:		This function clculates the BMI value and update to Database file 
**
*********************************************************************************************************/

void UpdateBli_DataBase(void )
{
	#if defined DATABASE_INTERFACE_EN

		FILE *fpt,*fp;
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char timeBuf[64];
		char Line[512];
		char query[512];
		/**************************database loging************************/
		system("/bin/date > /home/time.c");
		fpt = fopen("/home/time.c", "r");
		while( GetLine(fpt, Line) != 0)
		{
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
		
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		}
		sqlite3_close(db);

	#endif
}

#include"../inc/Header.h"

struct timeval tv;

// Declaration of functions
void RunBpTest(void);
void CalculateBp(void );
void UpdateBp_RawFile(void );
void UpdateBp_DataBase(void );
void UpdateBp_SummaryFile(void );		

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
extern unsigned short int BmiTestEn;
extern unsigned short int BpTestEn;
extern unsigned short int BliTestEn;
extern unsigned char HoldingReg[10];
extern unsigned char RxBuf[100];

// Declaration of Local variables
int tod_flag;
unsigned char Buf[5];
unsigned char BpMdbResponse = 0;
unsigned char BpSwitchIndex = 0;

extern unsigned char BpBuffer[25];
extern unsigned char MdbRawBuf[10];
extern int callback(void *NotUsed, int argc, char **argv, char **azColName);

/*************************************************************************************************************
**		function 	 		:	 	RunBpMdbTest
**		Definition   	:		Tests the BP through PIC Co-Processor
**
**************************************************************************************************************/
void RunBpMdbTest(void)
{
	switch(BpSwitchIndex)
	{
		case 0:            
			//WELLTH_CHECK_TIMEOUT_SEC = BP_CHECK_TIMEOUT_SEC;
			BpTestEn = 1;
			printf(" loop case value is = %d", LoopState);	
			HoldingReg[1] = 0x00;   
			HoldingReg[0] = 0x01;
			BpMdbResponse = ModbusOP(0x01,FC_WRITE_SINGLE_COIL, 0x000B, 0x000l, (unsigned char *)HoldingReg,1);
			if(BpMdbResponse!=0){
				#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",BpMdbResponse);
				#endif
			}
			else
			{
				HoldingReg[1] = 0x00;   
				HoldingReg[0] = 0x00;
				BpSwitchIndex = BpSwitchIndex +1;
			}
			break;			
			
		case 1:
			if (tod_flag == 0)
			{
				gettimeofday( &tv,NULL);
				printf(" Case 7 : Time - %d - \n",tv.tv_sec);
				tod_flag = 1;
			}
			printf(" loop case value is = %d", BpSwitchIndex);
			BpMdbResponse = ModbusOP(0x01,FC_READ_COILS, 0x000F, 0x0000, (unsigned char *)HoldingReg, 1);
			if((RxBuf[0] == 0x01) && (RxBuf[1] == 0x01) && (RxBuf[2] == 0x01) && (RxBuf[3] == 0x01))
			{
				BpSwitchIndex = BpSwitchIndex +1;
				BpTestEn = 1;
			}
		break;
			
		case 2:  
			printf(" loop case value is = %d", BpSwitchIndex);    
			BpMdbResponse = ModbusOP(0x01,FC_READ_HOLD_REGS, 0x000B, 0x0002, (unsigned char *)HoldingReg, 1);
			if(BpMdbResponse!=0)
			{
				#if defined	SHOW_DISPLAY
					printf("Modbus Error Response %d \n",BpMdbResponse);
				#endif
			} 
			else 
			{  
				CalculateBp();
				#ifndef GTK_DISABLE
					UpdateBp_SummaryFile();		
					UpdateBp_RawFile();
					UpdateBp_DataBase();
				#endif
				tod_flag = 0;
				LoopState = DO_LOOP_TEST;	
				return;
 			}
		break;     
	}
}

/********************************************************************************************************
**
**	Function Name	: 	CalculateBp
** Description 		:		This function clculates the Bp value and update to file that shared by  GTK UI
**
******************************************************************************************************** */

void CalculateBp(void)
{
	FILE *fp;
	
	#if defined W2_INTERFACE_EN
		printf("Modbus Got Sensor Response\n");
		printf("Systolic Pressure is = %d\n",MdbRawBuf[0]);   
		printf("Diastolic Pressure is = %d\n",MdbRawBuf[1]);   
		printf("Pulse Rate is = %d\n",MdbRawBuf[2]); 
		printf("Error Code is = %d\n",MdbRawBuf[3]);   
		BpTestEn = 0;

		sprintf(Bp.SysP,"%d",MdbRawBuf[0]);
		sprintf(Bp.DiaP,"%d",MdbRawBuf[1]);
		sprintf(Bp.PulseRate,"%d",MdbRawBuf[2]);
		sprintf(Bp.ErrorCode,"%d",MdbRawBuf[3]);	
	#else
		BpTestEn = 0;
		sprintf(Bp.SysP,"%d",BpBuffer[2]);
		sprintf(Bp.DiaP,"%d",BpBuffer[4]);
		sprintf(Bp.PulseRate,"%d",BpBuffer[16]);
		//sprintf(Bp.ErrorCode,"%d",BpBuffer[]);
	#endif
	
	fp = fopen (OT_ENTERY_FILE, "w");
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	}
	else
	{
		fwrite(&Bp,sizeof(Bp),1,fp);
		fclose(fp);
	}
	Buf[0] = ',';
}


/********************************************************************************************************
**
**	Function Name	: 	UpdateBp_SummaryFile
** Description 		:		This function calculates the Bp value and update to Summary file 
**
******************************************************************************************************** */
void UpdateBp_SummaryFile(void)
{		
	FILE *fpUI;		
	fpUI = fopen (BP_SUMMARY_FILE, "w"); //open file
	if(fpUI<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
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
}

/********************************************************************************************************
**
**	Function Name		: 	UpdateBp_RawFile
**  Description 		:		This function calculates the Bp value and update to Raw file 
**
******************************************************************************************************** */

void UpdateBp_RawFile(void)
{
	FILE *fpUI;	

	fpUI = fopen (BP_DUMPS_FILE, "a"); 
	if(fpUI<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
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
}

/********************************************************************************************************
**
**	Function Name		: 	UpdateBp_DataBase
** 	Description 		:		This function calculates the Bp value and update to Database file 
**
******************************************************************************************************** */


void UpdateBp_DataBase(void)
{
	#if defined DATABASE_INTERFACE_EN
		FILE *fpt,*fp;
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char timeBuf[64];
		char Line[512];
		char query[512];
		
		system("/bin/date > /home/time.c");
		fpt = fopen("/home/time.c", "r");
		while( GetLine(fpt, Line) != 0)
		{
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
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		}
		sqlite3_close(db);

		Buf[0] = '1';
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
		printf(" Demon has completed the  Wellth BP Test\n");
		LoopState = DO_LOOP_TEST;
		printf("LoopCase Value is %d\n",LoopState);
		fp  = fopen(IN_ENTERY_FILE,"w");
		fclose(fp);
		fp = fopen(IN_TEXT_FILE,"w");
		fclose(fp);  
	#endif
}

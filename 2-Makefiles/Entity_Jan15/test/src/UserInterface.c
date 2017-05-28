#include"../inc/Header.h"

// Declaration of Local variables

extern _INPUT_DATA_STRUCT		Din;
extern _LOGIN_DATA_STRUCT		Uin;
extern _IN_FILE_STRUCT 			Indata;
extern _BMI_TEST_STRUCT 			Bmi;
extern _BP_TEST_STRUCT				Bp;
extern _BLI_TEST_STRUCT			Bli;
extern _LOGIN_TEST_STRUCT		login;

extern int MDB_fd,RFID_fd;
extern int testStartTime;
extern int UserMode,LoopState;

extern unsigned char MdbRawBuf[10];
extern unsigned short int BmiTestEn;
extern unsigned short int BpTestEn;
extern unsigned short int BliTestEn;
extern unsigned char HoldingReg[10];

int SRL_index;
char Line[512];
char UName[32];
char *DemonArrOfCol[8];
char *ArrayOfCol[32];
char CurRFIDScaned[16];

int Hight,TempWeight; 
unsigned char UNMatched = 0;
unsigned char PWDMatched = 0;
unsigned char RFIDMatched = 0;
unsigned char NameColNum = 8;
unsigned char AgeColNum = 13;
unsigned char RFIDColNum = 14;
unsigned char GenderColNum = 4;
	
char *SerialPortName[] = {	
							"/dev/ttyUSB0",
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

/*************************************************************************************************************
										List of Function Declaration
**************************************************************************************************************/
void GetUserInputs(void);
void CheckUserInfo(void);
void ReadInputFile(void);
void CheckAbortFile(void);
void UpdateEntryFile(void);
void clearSummaryFile(void);
void ClearDemonInputFile(void);
void CompareDataByRfidMode(void);
void CompareDataByEntryMode(void);

float ConvertHexToFloat(void);

/********************************************************************************************************
**
**	Function Name		: 	ReadInputFile
**  Description 		:		This function read the input from GTK UI
**
*********************************************************************************************************/

void ReadInputFile(void)
{	
	FILE *ffp,*fp;
	int Age = 0;
	char Gender[10];
	
 	ffp = fopen (IN_TEXT_FILE, "r");
    	
	if(ffp<0)
	{
		printf(" System is not able to open GTK Input file \n");
  }
	else
	{
		fread(&Indata,sizeof(Indata),1,ffp);
		fclose(ffp);
  }

	// BMI Test Input
  if(strcmp(Indata.InBuf,"WeTest") == 0)
	{
		#if defined BMI_INTERFACE_EN
			memset(Indata.InBuf,0,10);
			LoopState = DO_BMI_TEST;    
		
			// IF BMI TEST SELECTED THEN USER SHOULD READ THE HIGHT FROM ENTRY FILE
			fp = fopen (IN_ENTERY_FILE, "r");
			if(fp<0)
			{
				printf(" System is not able to open file \n");
			}
			else
			{
				fread(&Din,sizeof(Din),1,fp);
				fclose(fp);
			}
			sscanf(Din.Hight,"%d",&Hight);
			printf("Demon Code has received the Hight = ");
			printf("%d\n",Hight);
			printf("\n");    
			printf("BMI Test Starts Now \n");     
		#endif        
  }
  // BP Test Input
	else if(strcmp(Indata.InBuf,"BpTest") == 0)
	{
		#if defined BP_INTERFACE_EN
			memset(Indata.InBuf,0,10);	
			printf("Bp Test Starts Now \n");
			LoopState = DO_BP_TEST;    
		#endif
	}
	
	// BLI Test Input
	else if(strcmp(Indata.InBuf,"BliTest") == 0)
	{
		#if defined BLI_INTERFACE_EN
			printf("BLI Test Starts now \n");      
			printf("Demon Code has received the Hight = ");
			fp = fopen (IN_ENTERY_FILE, "r");
			if(fp<0)
			{
				printf(" System is not able to open file \n");
			}
			else
			{
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
			LoopState = DO_BLI_TEST;  
			printf("\n");  
		#endif   
  }
  
  // CO Test Input
	else if (strcmp(Indata.InBuf,"CoTest") == 0) 
	{
		#if defined CO_INTERFACE_EN
			LoopState = DO_CO_TEST;
			printf("Co Test Starts now \n");
		#endif
	}
	
	// SMS Test Input
	else if (strcmp(Indata.InBuf,"SMS") == 0) 
	{
		#if defined GSM_INTERFACE_EN
			LoopState = DO_SMS_TEST;   
			printf("Sending sms starts now \n");
		#endif
	}
	
	// ECG Test Input
	else if (strcmp(Indata.InBuf,"EcgTest") == 0) 
	{
		#if defined ECG_INTERFACE_EN
			LoopState = DO_ECG_TEST;   
			printf("Taking ecg starts now \n");
		#endif
	}
	
	// ECG CHECK Test Input
	else if (strcmp(Indata.InBuf,"EcgCheck") == 0) 
	{
		printf("Checking ecg starts now \n");
	}
	
	// LOGIN Input BY DATA ENTRY MODE
	else if(strcmp(Indata.InBuf,"Login") == 0)
	{
		#if defined DATA_ENTRY_MODE_EN
			printf("\n*******login flag set\n");
			memset(Indata.InBuf,0,10);
			UserMode = DATA_ENTRY_MODE;
		#endif
  }
  
  // LOGIN Input BY RFID
	else if (strcmp(Indata.InBuf,"Swipe") == 0) 
	{
		#if defined RFID_ENTRY_MODE_EN
			memset(Indata.InBuf,0,10);
			tcflush(RFID_fd,TCIOFLUSH);
			UserMode = DATA_RFID_MODE;
		#endif
	}	
  else
	{
		UserMode = 0;
    LoopState = DO_LOOP_TEST;    
	}
}

/*************************************************************************************************************
**		function 		:	 	CheckUserInfo
**		Definition  :		Compare the user entered data through Database
**
**************************************************************************************************************/

void CheckUserInfo(void)
{
	memset(CurRFIDScaned, 0, 16);	
	
	if ( UserMode == DATA_ENTRY_MODE )
	{
		// check if user in Data entry mode
		CompareDataByEntryMode();
	}
	else if ( UserMode == DATA_RFID_MODE )
	{
		// check if user in RFID mode
		CompareDataByRfidMode();
	}
}

/*************************************************************************************************************
**		function 		:	 	CompareDataByEntryMode
**		Definition  :		Compare the user entered data through Data Entry Database
**
**************************************************************************************************************/

void CompareDataByEntryMode(void)
{
	FILE *fp1,*fp;
	
	UNMatched = 0; 
	PWDMatched = 0; 
	RFIDMatched = 0;
	
	printf("Demon Code has received the User Login information\n ");
	
	// Get the user information from the Entry file	
	fp = fopen (IN_ENTERY_FILE, "r");
	if(fp<0)
	{
		printf(" System is not able to open file \n");
	}
	else
	{
		if(GetLine(fp,Line))
		{
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
		
	// compare the user given information from WELLTH Database    
	
	// open up the user information file
	
	fp1 = fopen (USER_INFO_FILE, "r");
	if(fp1<0)
	{
		printf(" System is not able to open file \n");
	}
	else
	{
		while(1)
		{
			// Read the continous line
			if(GetLine(fp1,Line))
			{
				printf("----> Line: %s\n", Line);
				CreateArrayOfString(ArrayOfCol,Line);
				
				// Check Data Entry Databse 
				if(UserMode == DATA_ENTRY_MODE)
				{
					UNMatched = 1;
					PWDMatched = 1;
					if(UNMatched == 1 && PWDMatched == 1) 
					{
							strcpy(login.LoginReply, "LOGIN_SUCCESS");
							strcpy(login.Name, ArrayOfCol[NameColNum-1]);
							strcpy(login.Age, ArrayOfCol[AgeColNum-1]);
							strcpy(login.Gender, ArrayOfCol[GenderColNum-1]);
							clearSummaryFile();
							if(RFID_fd != -1)
							{
								close(RFID_fd);
								RFID_fd = -1;
							}
						break;
					} 
				}
			}
			else 
			{
					break;
			}
		}
	}
	fclose(fp1); // close USER_INFO_FILE
	UpdateEntryFile();
	FreeArrayOfString(DemonArrOfCol);
	FreeArrayOfString(ArrayOfCol);
	ClearDemonInputFile();
	
}

/*************************************************************************************************************
**		function 		:	 	CompareDataByRfidMode
**		Definition  :		Compare the user entered data through RFID Database
**
**************************************************************************************************************/

void CompareDataByRfidMode(void)
{
	FILE* fp1, *fp;
	char *ptr_CurRFIDScaned, *ptr_nxtline, *ptr_CSV_RFIDStored;

	// Check thBMI_INTERFACE_ENe RFID data if it is not null then only proceed
	printf("compairing user info");
	
	if(RFID_fd == -1)
	{
		//RFID_fd = ArgOpenSerialPort("/dev/ttyUSB0", 9600);
		RFID_fd = ArgOpenSerialPort(SerialPortName[SRL_index], 9600);
		if(RFID_fd < 0) 
		{
			printf("Alert: reconnect the RFID port USB and restart the daemon \n");
		}
		if(RFID_fd > 0)
		{
			printf("RFID is connected to %s discriptor=%d\n ","/dev/ttyUSB0", RFID_fd);
		}
	}

	printf("%s", CurRFIDScaned);
	read(RFID_fd, CurRFIDScaned,1);
	if(CurRFIDScaned[0] != 0) 
	{
		printf("swipe");
		nu_SerialComPort_BlockRead(RFID_fd, CurRFIDScaned, 13);
		printf("%s\n",CurRFIDScaned);
		printf("%s\n",CurRFIDScaned);
		printf("%s\n",CurRFIDScaned);
	}
	
	if(CurRFIDScaned[0] != 0)
	{
		ptr_CurRFIDScaned = strstr(CurRFIDScaned,"80");
		if(ptr_CurRFIDScaned == NULL)
		{
			close(RFID_fd);
			RFID_fd = -1;
			return;
		} 
		else 
		{
			close(RFID_fd);
			RFID_fd = -1;
		}
		ptr_nxtline = strchr(CurRFIDScaned, '\n');
		*ptr_nxtline = '\0';
		printf("\n-------------%s", CurRFIDScaned);
		printf("\nDemon Code has started the comparison of  Login information\n ");
		UNMatched = 0; 
		PWDMatched = 0; 
		RFIDMatched = 0;
		
		// open up the user information file
		
		fp1 = fopen (USER_INFO_FILE, "r");
		if(fp1<0)
		{
			printf(" System is not able to open file \n");
		}
		else
		{
			while(1)
			{
				// Read the continous line
				if(GetLine(fp1,Line))
				{
					printf("----> Line: %s\n", Line);
					CreateArrayOfString(ArrayOfCol,Line);					
					printf("\ncompairing\n");
					printf("\n--%s-- == --%s--\n", ArrayOfCol[RFIDColNum-1], ptr_CurRFIDScaned);
					ptr_CSV_RFIDStored = ArrayOfCol[RFIDColNum-1]+1;
					if(strcmp(ptr_CSV_RFIDStored, ptr_CurRFIDScaned) == 0) 
					{
						RFIDMatched = 1;
					}
					printf("\nafter compairing\n");
					if (RFIDMatched == 1)
					{ 
							strcpy(login.LoginReply, "LOGIN_SUCCESS");
							strcpy(login.Name, ArrayOfCol[NameColNum-1]);
							strcpy(login.Age, ArrayOfCol[AgeColNum-1]);
							strcpy(login.Gender, ArrayOfCol[GenderColNum-1]);
							clearSummaryFile();
							close(RFID_fd);
							RFID_fd = -1;
							break;
					} 
					else 
					{
						close(RFID_fd);
						RFID_fd = -1;
					}				
				} 
				else 
				{
						break;
				}
			}
			// end of while loop
			
			fclose(fp1); // close USER_INFO_FILE
					
			if( RFIDMatched == 0 ) 
			{
				memset(CurRFIDScaned, 0, sizeof(CurRFIDScaned));
				close(RFID_fd);
				RFID_fd = -1;
				return;
			}			
			UpdateEntryFile();
			FreeArrayOfString(DemonArrOfCol);
			FreeArrayOfString(ArrayOfCol);
			ClearDemonInputFile();
		}
	}
}

/*************************************************************************************************************
**		function 			:	 	UpdateEntryFile
**		Definition   	:		Updates the output entry file for GTK 
**
**************************************************************************************************************/
void UpdateEntryFile(void)
{
		FILE* fp1, *fpUI;
		unsigned char Buf,ch;
				
		fp1 = fopen (OT_ENTERY_FILE, "w");
		if(fp1<0)
		{
			printf(" System is not able to open file \n");
		}
	 	else
		{
		 	fwrite(login.LoginReply, strlen(login.LoginReply), 1, fp1);
			ch = ',';
			fwrite(&ch, 1, 1, fp1);
			fwrite(login.Name, strlen(login.Name), 1, fp1);
			fwrite(&ch, 1, 1, fp1);
			fwrite(login.Age, strlen(login.Age), 1, fp1);
			fwrite(&ch, 1, 1, fp1);
			fwrite(login.Gender, strlen(login.Gender), 1, fp1);
		
			fpUI = fopen(LOGIN_SUMMARY_FILE, "w");
			if(fp1<0)
			{
		 		printf(" System is not able to open file \n");
			} 
			else 
			{
				fwrite(login.Name, strlen(login.Name), 1, fpUI);
				fwrite(&ch, 1, 1, fpUI);
				fwrite(login.Age, strlen(login.Age), 1, fpUI);
				fwrite(&ch, 1, 1, fpUI);
				fwrite(login.Gender, strlen(login.Gender), 1, fpUI);
				fclose(fpUI);
			}
		}
	  fclose(fp1); // close OT_ENTERY_FILE
	
		UserMode= 0;
		Buf = '1';
		fp1 = fopen (OT_TEXT_FILE, "w");
		if(fp1<0)
		{
			printf(" System is not able to open file \n");
		}
		else
		{
			fwrite(&Buf,1,1,fp1);
		}

		fclose(fp1); // close OT_TEXT_FILE
}

/*************************************************************************************************************
**		function 			:	 
**		Definition   	:
**
**************************************************************************************************************/
void CheckAbortFile(void)
{
	FILE *ffp;
	char AbortBuffer[10];

	ffp = fopen (IN_BP_FILE, "r");

	if(ffp<0)
	{
		printf(" System is not able to open file \n");
	} 
	else 
	{
		fread(AbortBuffer,sizeof(AbortBuffer),1,ffp);
		fclose(ffp);
		ClearDemonInputFile();
		if (strcmp(AbortBuffer,"Abort") == 0) 
		{
			memset(AbortBuffer,0,10);
			BpTestEn = 0;
			LoopState = 14;
			testStartTime = WELLTH_CHECK_TIMEOUT_SEC-1;
		}
	}
}

/*************************************************************************************************************
**		function 			:	 
**		Definition   	:
**
**************************************************************************************************************/
void clearSummaryFile(void)
{
	FILE *fpUI;
	fpUI = fopen (BF_SUMMARY_FILE, "w"); 
	fclose(fpUI);
	fpUI = fopen (BMI_SUMMARY_FILE, "w");
	fclose(fpUI);
	fpUI = fopen (BP_SUMMARY_FILE, "w");
	fclose(fpUI);
	fpUI = fopen (CO_SUMMARY_FILE, "w");
	fclose(fpUI);
}


/*************************************************************************************************************
**		function 			:	 
**		Definition   	:
**
**************************************************************************************************************/
               	
void ClearDemonInputFile()
{
	FILE *fp1;
	
	fp1 = fopen (IN_TEXT_FILE, "w");
	fclose(fp1);
	fp1 = fopen (IN_ENTERY_FILE, "w");
	fclose(fp1);
	fp1 = fopen (IN_BP_FILE, "w");
	fclose(fp1);
}

/*************************************************************************************************************
**		function 			:	 
**		Definition   	:
**
**************************************************************************************************************/
float ConvertHexToFloat(void)
{
	float Result;
	signed int IntValue;
	long int Byte1=0,Byte2=0,Byte3=0,Byte4=0;
        
	if(BliTestEn)
	{
		Byte1 = MdbRawBuf[1];
		Byte2 = MdbRawBuf[0];
		Byte2 = (Byte2<<8);
		Byte3 = MdbRawBuf[3];
		Byte3 = (Byte3<<16);
		Byte4 = MdbRawBuf[2];
		Byte4 = (Byte4<<24);
	}        
	else
	{        
		Byte1 = MdbRawBuf[0];
		Byte2 = MdbRawBuf[1];
		Byte2 = (Byte2<<8);
		Byte3 = MdbRawBuf[2];
		Byte3 = (Byte3<<16);
		Byte4 = MdbRawBuf[3];
		Byte4 = (Byte4<<24);
	}        
	IntValue = (Byte1| Byte2| Byte3|Byte4);    
	printf("The int value is %x \n",IntValue);    
	Result = *((float *)&IntValue);     
	return Result;
}


/*************************************************************************************************************
**		function 			:		GetUserInputs
**		Definition   	:		Get the user inputs directly from terminal to test the sensors 
**											through PIC without using any GTK
**
**************************************************************************************************************/
void GetUserInputs(void)
{
	unsigned int SensorTest =0;
	
	printf("You can test the Sensors without GTK\n");
	printf("Press 1 for BMI Sesnor Test\n");
	printf("Press 2 for BP Sesnor Test\n");
	printf("Press 3 for BLI Sesnor Test\n");
	printf("Press 4 for GSM Sesnor Test\n");
	printf("Press 5 for RFID Sesnor Test\n");
	while(SensorTest == 0)		
	{
		scanf("%d",&SensorTest);
	}
	
	switch(SensorTest)
	{
		case 1:
			printf("Enter your Hight \n");
			scanf("%d",&Hight);
			LoopState = DO_BMI_TEST;
		break;
		case 2:
			LoopState = DO_BP_TEST;
		break;
		case 3:
			printf("Enter your Hight \n");
			scanf("%d",&Hight);
			printf("Enter your Weight \n");
			scanf("%d",&TempWeight);
			LoopState = DO_BLI_TEST;
		break;
		case 4:
			LoopState = DO_SMS_TEST;
		break;
		case 5:
			LoopState = DO_RFID_TEST;
		break;
		default:
		break;
	}
}		



#include"include/main.h"

typedef struct _Private Private;
static struct _Private
{
};

static struct Private* priv = NULL;

static GtkWidget* CreateHomeScreen(void);
void ReadDataEntry(void);
void MainViewList_0(void);
void MainViewList_1(void);
void MainViewList_2(void);
void MainViewList_3(void);
void GoToMainScreen(void);

extern void GoToPopUPMainScreen(void);
extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToConfigScreen(void);
extern void GoToSettingScreen(void);

/*****************************************************************************************************************
                              Variable Declaration
******************************************************************************************************************/
GtkBuilder *HomeBuilder;
extern int MainWindowEn,SetWindowEn,ConfWindowEn,MainWindowEn,MainWindowEn;
extern GtkBuilder *ConfBuilder, *SetBuilder, *BpBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*SettingWindow;

GtkWidget *MainBtn0,*MainBtn1,*MainBtn2,*MainBtn3;
GtkWidget *Button1,*Button2,*Button3,*Button4,*Button5;
GtkImage  *imageBG;	

int Main_V0_Index = 0;
int Main_V1_Index = 0;
int Main_V2_Index = 0;
int Main_V3_Index = 0;

volatile int Main_V0_Index_Cnt = 0;
volatile int Main_V1_Index_Cnt = 0;
volatile int Main_V2_Index_Cnt = 0;
volatile int Main_V3_Index_Cnt = 0;

volatile char Main_DBMS_Path_0[30] = "./src/dbms/";
volatile char Main_DBMS_Path_1[30];
volatile char Main_DBMS_Path_2[30];
volatile char Main_DBMS_Path_3[30];
volatile char Main_DBMS_Path_4[30];

volatile char *Main_View_0_Buffer[100]; 
volatile char *Main_View_1_Buffer[100]; 
volatile char *Main_View_2_Buffer[100]; 
volatile char *Main_View_3_Buffer[100]; 

volatile char	Main_DisableCallBack0 = 0;
volatile char Main_DisableCallBack1 = 0;
volatile char Main_DisableCallBack2 = 0;
volatile char Main_DisableCallBack3 = 0;

volatile char Main_vbox0En;
volatile char Main_vbox1En;
volatile char Main_vbox2En;
volatile char Main_vbox3En;

GtkWidget *vbox0,*vbox1,*vbox2,*vbox3;
GtkWidget *entry0,*entry1,*entry2,*entry3,*entry4,*entry5,*entry6;
DIR  *ptrDir0Main,*ptrDir1Main,*ptrDir2Main,*ptrDir3Main;
struct dirent *dirlistdel0,*dirlistdel1,*dirlistdel2,*dirlistdel3;
static GtkComboBoxText *Main_View_0_List,*Main_View_1_List,*Main_View_2_List,*Main_View_3_List;

volatile unsigned char ReadDirPath_3[30];
volatile unsigned char Main_Path_0[10];
volatile unsigned char Main_Path_1[10];
volatile unsigned char Main_Path_2[10];
volatile unsigned char Main_Path_3[10];
 
/*****************************************************************************************************************
                             Main Code Starts Here 
******************************************************************************************************************/
static void CallBackFrom_Main_View_0( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	char *string = gtk_combo_box_text_get_active_text( Main_View_0_List );

	Main_V1_Index = 0;
	Main_V2_Index = 0;
	Main_V3_Index = 0;
	
	if(Main_DisableCallBack0)
	{
		printf("\n Main_DisableCallBack0 \n");
		return;
	}
	gtk_combo_box_set_active_id(Main_View_0_List, string);
	
	if(string == NULL)
		return;
		
	g_print( "CallBackFrom_Main_View_0: >> %s <<\n", ( string ? string : "NULL" ) );
	
	Main_V0_Index_Cnt = 0;
	Main_DisableCallBack1 = 1;
	ptrDir0Main = opendir(Main_DBMS_Path_0);
	if (ptrDir0Main)
	{
		while ((dirlistdel0 = readdir(ptrDir0Main)) != NULL)
		{
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Main_View_0_Buffer[Main_V0_Index_Cnt]=dirlistdel0->d_name;
				printf("Data %s\n", Main_View_0_Buffer[Main_V0_Index_Cnt]);				
				Main_V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0Main);
	}
			
	for(i=0;i<Main_V0_Index_Cnt;i++)
	{
		if(strcmp(Main_View_0_Buffer[i],string) == 0)
		{
			Main_V0_Index = i;	
			memset(Main_Path_0,0,10);
			strcat(Main_Path_0,Main_View_0_Buffer[Main_V0_Index]);
			printf("Main_Path_0 %s \n",Main_Path_0);
			if(Main_Path_0[0] == NULL)
			{
				printf("Sorry Path 0 is empty \n");
				return;
			}
			g_free( string );
			memset(Main_DBMS_Path_1,0,30);
			memset(Main_DBMS_Path_2,0,30);
			memset(Main_DBMS_Path_3,0,30);
			strcat(Main_DBMS_Path_1,"./src/dbms/");
			strcat(Main_DBMS_Path_1,Main_Path_0);
			printf("Calling MainViewList_0 with Path %s \n",Main_DBMS_Path_1);
			MainViewList_1();	
			return;
		}
	}	
	g_free( string );
}

static void CallBackFrom_Main_View_1( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Main_View_1_List );

	if(Main_DisableCallBack1 == 1)
	{
		printf("\n Main_DisableCallBack1 \n");
		return;
	}

	gtk_combo_box_set_active_id(Main_View_1_List, string);
	
	if(string == NULL)
		return;	
		
	g_print("CallBackFrom_Main_View_1: >> %s <<\n", ( string ? string : "NULL" ) );
	
	Main_V2_Index = 0;
	Main_V3_Index = 0;
	
	Main_V1_Index_Cnt = 0;	
	ptrDir1Main = opendir(Main_DBMS_Path_1);
	if (ptrDir1Main)
	{
		while ((dirlistdel1 = readdir(ptrDir1Main)) != NULL)
		{
			printf("%s\n", dirlistdel1->d_name);
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Main_View_1_Buffer[Main_V1_Index_Cnt]=dirlistdel1->d_name;
				g_print("Data %s\n", Main_View_1_Buffer[Main_V1_Index_Cnt]);				
				Main_V1_Index_Cnt++;
			}			
		}
		closedir(ptrDir1Main);
	}
			
	for(i=0;i<Main_V1_Index_Cnt;i++)
	{
		if(strcmp(Main_View_1_Buffer[i],string) == 0)
		{				
			Main_V1_Index = i;	
			memset(Main_Path_1,0,10);
			strcat(Main_Path_1,Main_View_1_Buffer[Main_V1_Index]);
			printf("Main_Path_0 %s \n",Main_Path_1);

			if(Main_Path_1[0] == NULL)
			{
				printf("Sorry Path 1 is empty \n");
				return;
			}
			printf("Main_View_1_Buffer[0] %s \n",Main_Path_1);
			g_free( string );
			memset(Main_DBMS_Path_2,0,30);
			memset(Main_DBMS_Path_3,0,30);
			strcat(Main_DBMS_Path_2,Main_DBMS_Path_1);
			strcat(Main_DBMS_Path_2,"/");
			strcat(Main_DBMS_Path_2,Main_Path_1);
			printf("Calling MainViewList_1 with Path%s \n",Main_DBMS_Path_2);
			MainViewList_2();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_Main_View_2( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Main_View_2_List );

	if(Main_DisableCallBack2 == 1)
	{
		printf("\n Main_DisableCallBack2 \n");
		return;
	}			
	
	if(string == NULL)
		return;	

	gtk_combo_box_set_active_id(Main_View_2_List, string);
	g_print("CallBackFrom_Main_View_2: >> %s <<\n", ( string ? string : "NULL" ) );

	Main_V3_Index = 0;
	Main_V2_Index_Cnt = 0;

	ptrDir2Main = opendir(Main_DBMS_Path_2);
	if (ptrDir2Main)
	{
		while ((dirlistdel2 = readdir(ptrDir2Main)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Main_View_2_Buffer[Main_V2_Index_Cnt]=dirlistdel2->d_name;
				g_print("Data %s\n", Main_View_2_Buffer[Main_V2_Index_Cnt]);				
				Main_V2_Index_Cnt++;
			}			
		}
		closedir(ptrDir2Main);
	}	
		
	for(i=0;i<Main_V2_Index_Cnt;i++)
	{
		if(strcmp(Main_View_2_Buffer[i],string) == 0)
		{				
			Main_V2_Index = i;	
			memset(Main_Path_2,0,10);
			strcat(Main_Path_2,Main_View_2_Buffer[Main_V2_Index]);
			printf("Main_Path_2 %s \n",Main_Path_2);
			if(Main_Path_2[0] == NULL)
			{
				printf("Sorry Path 2 is empty \n");
				return;
			}
			printf("Main_View_2_Buffer[0] %s \n",Main_Path_2);
			g_free( string );
			memset(Main_DBMS_Path_3,0,30);
			strcat(Main_DBMS_Path_3,Main_DBMS_Path_2);
			strcat(Main_DBMS_Path_3,"/");
			strcat(Main_DBMS_Path_3,Main_Path_2);
			printf("Calling MainViewList_2 with  Path %s \n",Main_DBMS_Path_3);
			MainViewList_3();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_Main_View_3( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Main_View_3_List );
	
	if(string == NULL)
		return;			

	gtk_combo_box_set_active_id(Main_View_3_List, string);

	if(Main_DisableCallBack3 == 1)
		return;
		
	Main_V3_Index_Cnt = 0;

	ptrDir3Main = opendir(Main_DBMS_Path_3);
	if (ptrDir3Main)
	{
		while ((dirlistdel3 = readdir(ptrDir3Main)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Main_View_3_Buffer[Main_V3_Index_Cnt]=dirlistdel3->d_name;
				g_print("CallBackFrom_Main_View_2 %s\n", Main_View_3_Buffer[Main_V3_Index_Cnt]);				
				Main_V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3Main);
	}	
			
	for(i=0;i<Main_V3_Index_Cnt;i++)
	{
		if(strcmp(Main_View_3_Buffer[i],string) == 0)
		{				
			Main_V3_Index = i;	

			memset(Main_Path_3,0,10);
			strcat(Main_Path_3,Main_View_3_Buffer[Main_V3_Index]);
			printf("Main_Path_3 %s \n",Main_Path_3);
			if(Main_Path_3[0] == NULL)
			{
				printf("Sorry Path 3 is empty \n");
				return;
			}
			
			printf("Main_Path = Main_View_3_Buffer[0] %s \n",Main_Path_3);
			g_free( string );
			memset(Main_DBMS_Path_4,0,30);
			strcat(Main_DBMS_Path_4,Main_DBMS_Path_3);
			strcat(Main_DBMS_Path_4,"/");
			strcat(Main_DBMS_Path_4,Main_Path_3);
			printf("New Main_Path %s \n",Main_DBMS_Path_4);	
			
			
			memset(ReadDirPath_3,0,30);
			strcpy(ReadDirPath_3,Main_DBMS_Path_3);
			strcat(ReadDirPath_3,"/");
			strcat(ReadDirPath_3,Main_Path_3);
			ReadDataEntry();
						
			return;
		}
	}
		g_free( string );
}
	
void Main_ResetDisables(void)
{
	Main_DisableCallBack0 = 0;
	Main_DisableCallBack1 = 0;
	Main_DisableCallBack2 = 0;
}

void MainViewList_0(void)
{
	Main_vbox1En = 0;
	Main_vbox2En = 0;
	Main_vbox3En = 0;
	Main_V0_Index = 0;
	
	printf("***********************   MainViewList_0   **********************\n");
	/********************************************************************************************
																						Vbox 0 
	*********************************************************************************************/
	Main_DisableCallBack0 = 1;
	Main_DisableCallBack1 = 1;
	Main_DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_0_List));

	ptrDir0Main = opendir(Main_DBMS_Path_0);
	if (ptrDir0Main)
	{
		Main_V0_Index_Cnt = 0;
		while ((dirlistdel0 = readdir(ptrDir0Main)) != NULL)
		{
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Main_View_0_Buffer[Main_V0_Index_Cnt]=dirlistdel0->d_name;                         
				Main_V0_Index_Cnt++;
			}	
		}
	}
	
	if(Main_V0_Index_Cnt == 0)
	{
		printf("\nSorry Main_V0_Index_Cnt is %d\n",Main_V0_Index_Cnt);
		Main_ResetDisables();
		return;
	}
		
	ptrDir0Main = opendir(Main_DBMS_Path_0);
	if (ptrDir0Main)
	{
		Main_V0_Index_Cnt = 0;
		while ((dirlistdel0 = readdir(ptrDir0Main)) != NULL)
		{
			//printf("%s\n", dirlistdel0->d_name);
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Main_View_0_Buffer[Main_V0_Index_Cnt]=dirlistdel0->d_name;
				printf("Vbox 0 Adding %s , %d \n", Main_View_0_Buffer[Main_V0_Index_Cnt],Main_V0_Index);	
				if(Main_V0_Index_Cnt == Main_V0_Index)
				{
					memset(Main_Path_0,0,10);
					strcat(Main_Path_0,Main_View_0_Buffer[Main_V0_Index_Cnt]);
					printf("Main_Path_0 %s \n",Main_Path_0);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Main_View_0_List), Main_View_0_Buffer[Main_V0_Index_Cnt]);
				Main_V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0Main);
	}
	
	if(Main_V0_Index_Cnt == 0)
	{
		printf("\nSorry Main_V0_Index_Cnt is %d\n",Main_V0_Index_Cnt);
		Main_ResetDisables();
		return;
	}
	
	if(Main_Path_0[0] == NULL)
	{
		printf("List Path 0 is empty \n");
		Main_ResetDisables();
		return;
	}
			
	memset(Main_DBMS_Path_1,0,30);
	strcat(Main_DBMS_Path_1,"./src/dbms/");
	strcat(Main_DBMS_Path_1,Main_Path_0);
	printf("New Path for VBox 1 %s \n",Main_DBMS_Path_1);
	gtk_combo_box_set_active((GtkComboBox *)(Main_View_0_List),Main_V0_Index);
	g_signal_connect( G_OBJECT( Main_View_0_List ), "changed", G_CALLBACK( CallBackFrom_Main_View_0), NULL );
	Main_V0_Index = 0;
	printf("******** MainViewList_0 Bye **********\n");
	MainViewList_1();
}

void MainViewList_1(void)
{
	int i = 0;		

	Main_V1_Index = 0;
	printf("***********************   MainViewList_1   **********************\n");
	Main_DisableCallBack0 = 0;
	Main_DisableCallBack1 = 1;
	Main_DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_1_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_3_List));
	
	ptrDir1Main = opendir(Main_DBMS_Path_1);
	if (ptrDir1Main)
	{
		Main_V1_Index_Cnt = 0;
		while ((dirlistdel1 = readdir(ptrDir1Main)) != NULL)
		{
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Main_View_1_Buffer[Main_V1_Index_Cnt]=dirlistdel1->d_name;                          
				Main_V1_Index_Cnt++;
			}	
		}
	}
	
	if(Main_V1_Index_Cnt == 0)
	{
		printf("\nSorry Main_V1_Index_Cnt is %d\n",Main_V1_Index_Cnt);
		Main_ResetDisables();
		return;
	}
	memset(Main_Path_1,0,10);
	ptrDir1Main = opendir(Main_DBMS_Path_1);
	if (ptrDir1Main)
	{
		Main_V1_Index_Cnt = 0;
		while ((dirlistdel1 = readdir(ptrDir1Main)) != NULL)
		{
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Main_View_1_Buffer[Main_V1_Index_Cnt]=dirlistdel1->d_name;
				printf("Vox 1 Adding %s , %d \n", Main_View_1_Buffer[Main_V1_Index_Cnt],Main_V1_Index);				
				if(Main_V1_Index_Cnt == Main_V1_Index)
				{
					strcat(Main_Path_1,Main_View_1_Buffer[Main_V1_Index_Cnt]);
					printf("Main_Path_1 %s \n",Main_Path_1);
				}
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Main_View_1_List), Main_View_1_Buffer[Main_V1_Index_Cnt]);                               
				Main_V1_Index_Cnt++;
			}	
		}
		closedir(ptrDir1Main);
	}

	if(Main_V1_Index_Cnt == 0)
	{
		printf("\nSorry Main_V1_Index_Cnt is %d\n",Main_V1_Index_Cnt);
		Main_ResetDisables();
		return;
	}

	if(Main_Path_1[0] == NULL)
	{
		printf("List Path 1 is empty \n");
		Main_ResetDisables();
		return;
	}
			
	memset(Main_DBMS_Path_2,0,30);
	strcat(Main_DBMS_Path_2,Main_DBMS_Path_1);
	strcat(Main_DBMS_Path_2,"/");
	strcat(Main_DBMS_Path_2,Main_Path_1);
	printf("New Path for Box 2 %s \n",Main_DBMS_Path_2);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Main_View_1_List),Main_V1_Index);
	g_signal_connect( G_OBJECT( Main_View_1_List ), "changed", G_CALLBACK( CallBackFrom_Main_View_1 ), NULL );	
	Main_V1_Index = 0;
	printf("******** MainViewList_1 Bye **********\n");
	MainViewList_2();
}

void MainViewList_2(void)
{
	int i = 0;
	
	Main_V2_Index = 0;
	Main_DisableCallBack0 = 0;
	Main_DisableCallBack1 = 0;
	Main_DisableCallBack2 = 1;

	printf("***********************   MainViewList_2   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_3_List));
	
	ptrDir2Main = opendir(Main_DBMS_Path_2);
	if (ptrDir2Main)
	{
		Main_V2_Index_Cnt = 0;
		while ((dirlistdel2 = readdir(ptrDir2Main)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Main_View_2_Buffer[Main_V2_Index_Cnt]=dirlistdel2->d_name;
				printf("Vox 2 Adding %s , %d \n", Main_View_2_Buffer[Main_V2_Index_Cnt],Main_V2_Index);	                            
				Main_V2_Index_Cnt++;
			}	
		}
	}
	
	if(Main_V2_Index_Cnt == 0)
	{
		printf("\nSorry Main_V2_Index_Cnt is %d\n",Main_V2_Index_Cnt);
		Main_ResetDisables();
		return;
	}		

	ptrDir2Main = opendir(Main_DBMS_Path_2);
	if (ptrDir2Main)
	{
		Main_V2_Index_Cnt = 0;
		while ((dirlistdel2 = readdir(ptrDir2Main)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Main_View_2_Buffer[Main_V2_Index_Cnt]=dirlistdel2->d_name;
				printf("Vox 2 Adding %s , %d \n", Main_View_2_Buffer[Main_V2_Index_Cnt],Main_V2_Index);				
				if(Main_V2_Index_Cnt == Main_V2_Index)
				{
					memset(Main_Path_2,0,10);
					strcat(Main_Path_2,Main_View_2_Buffer[Main_V2_Index_Cnt]);
					printf("Main_Path_2 %s \n",Main_Path_2);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Main_View_2_List), Main_View_2_Buffer[Main_V2_Index_Cnt]);                               
				Main_V2_Index_Cnt++;
			}	
		}
		closedir(ptrDir2Main);
	}

	if(Main_V2_Index_Cnt == 0)
	{
		printf("\nSorry Main_V2_Index_Cnt is %d\n",Main_V2_Index_Cnt);
		Main_ResetDisables();
		return;
	}	

	if(Main_Path_2[0] == NULL)
	{
		printf("List Path 2 is empty \n");
		Main_ResetDisables();
		return;
	}		
	memset(Main_DBMS_Path_3,0,30);
	strcat(Main_DBMS_Path_3,Main_DBMS_Path_2);
	strcat(Main_DBMS_Path_3,"/");
	strcat(Main_DBMS_Path_3,Main_Path_2);
	printf("New Path for Box 3 %s \n",Main_DBMS_Path_3);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Main_View_2_List),Main_V2_Index);
	g_signal_connect( G_OBJECT( Main_View_2_List ), "changed", G_CALLBACK( CallBackFrom_Main_View_2 ), NULL );	

	Main_V2_Index = 0;
	printf("******** MainViewList_2 Bye **********\n");
	MainViewList_3();	
}

void MainViewList_3(void)
{
	int i = 0;	
	
	Main_V3_Index = 0;
	Main_DisableCallBack0 = 0;
	Main_DisableCallBack1 = 0;
	Main_DisableCallBack2 = 1;
	Main_DisableCallBack3 = 1;
	
	printf("***********************   MainViewList_3   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Main_View_3_List));
	ptrDir3Main = opendir(Main_DBMS_Path_3);
	printf("New Path for Box 3 %s \n",Main_DBMS_Path_3);
	if (ptrDir3Main)
	{
		Main_V3_Index_Cnt = 0;
		while ((dirlistdel3 = readdir(ptrDir3Main)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Main_View_3_Buffer[Main_V3_Index_Cnt]=dirlistdel3->d_name;                          
				Main_V3_Index_Cnt++;
			}	
		}
	}
	
	if(Main_V3_Index_Cnt == 0)
	{
		printf("\nSorry Main_V3_Index_Cnt is %d\n",Main_V3_Index_Cnt);
		Main_ResetDisables();
		return;
	}	

	ptrDir3Main = opendir(Main_DBMS_Path_3);
	if (ptrDir3Main)
	{
		Main_V3_Index_Cnt = 0;
		while ((dirlistdel3 = readdir(ptrDir3Main)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Main_View_3_Buffer[Main_V3_Index_Cnt]=dirlistdel3->d_name;   
				printf("Vox 3 Adding %s , %d \n", Main_View_3_Buffer[Main_V3_Index_Cnt],Main_V3_Index);			
				if(Main_V3_Index_Cnt == 0)
				{
					memset(Main_Path_3,0,10);
					strcat(Main_Path_3,Main_View_3_Buffer[0]);
					printf("Main_Path_3 %s \n",Main_Path_3);
					memset(ReadDirPath_3,0,30);
					strcpy(ReadDirPath_3,Main_DBMS_Path_3);
					strcat(ReadDirPath_3,"/");
					strcat(ReadDirPath_3,Main_Path_3);
					
				}		
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Main_View_3_List), Main_View_3_Buffer[Main_V3_Index_Cnt]);
				Main_V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3Main);
	}

	if(Main_V3_Index_Cnt == 0)
	{
		printf("\nSorry Main_V3_Index_Cnt is %d\n",Main_V3_Index_Cnt);
		Main_ResetDisables();
		return;
	}
	if(Main_Path_3[0] == NULL)
	{
		printf("List Path 3 is empty \n");
		Main_ResetDisables();
	}
	
	memset(Main_DBMS_Path_4,0,30);
	strcat(Main_DBMS_Path_4,Main_DBMS_Path_3);
	strcat(Main_DBMS_Path_4,"/");
	strcat(Main_DBMS_Path_4,Main_Path_3);
	printf("New Main_DBMS_Path_4 %s \n",Main_DBMS_Path_4);	
	
	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Main_View_3_List),Main_V3_Index);
	g_signal_connect( G_OBJECT( Main_View_3_List ), "changed", G_CALLBACK( CallBackFrom_Main_View_3), NULL );	
	Main_DisableCallBack2 = 0;
	Main_DisableCallBack3 = 0;	
	Main_V3_Index = 0;
	printf("******** MainViewList_3 Bye **********\n");
	ReadDataEntry();
}

void ReadDataEntry(void)
{
	FILE *fp1,*fp2,*fp3;
	unsigned RawBuf[30];
	unsigned char FilePath[50];
	unsigned char Buf0[20],Buf1[20],Buf2[20];
	
	memset(FilePath,0,50);
	printf("ReadDirPath_3 %s \n",ReadDirPath_3);
	strcpy(FilePath,ReadDirPath_3);
	strcat(FilePath,"/name.txt");		
	printf("Path 1 %s \n",FilePath);
	
	fp1 = fopen (FilePath, "r");	
	if(fp1<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf0,15,1,fp1);
		printf("Name %s\n",Buf0);
		memset(RawBuf,0,30);
		strcpy(RawBuf,"Name : ");
		
		if( (Buf0[0]>= 'a' && Buf0[0]<= 'z') || (Buf0[0]>= 'A' && Buf0[0] <= 'Z') || (Buf0[0]>= 0 && Buf0[0] <= 9) )
		{
			strcat(RawBuf,Buf0);
		}
		gtk_entry_set_text(entry0,RawBuf);
	}
	fclose(fp1);	
			
	memset(FilePath,0,50);
	strcat(FilePath,ReadDirPath_3);
	strcat(FilePath,"/man.txt");		
	printf("Path 1 %s \n",FilePath);
	fp2 = fopen (FilePath, "r");
	if(fp2<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf1,15,1,fp2);
		printf("Manufacture %s\n",Buf1);
		memset(RawBuf,0,30);
		strcpy(RawBuf,"Manufacture : ");		
		if( (Buf1[0]>= 'a' && Buf1[0]<= 'z') || (Buf1[0]>= 'A' && Buf1[0] <= 'Z') || (Buf1[0]>= 0 && Buf1[0] <= 9) )
		{
			strcat(RawBuf,Buf1);
		}
		gtk_entry_set_text(entry1,RawBuf);
	}
	fclose(fp2);	
		
	memset(FilePath,0,50);
	strcat(FilePath,ReadDirPath_3);
	strcat(FilePath,"/geo.txt");		
	printf("Path 1 %s \n",FilePath);
	fp3 = fopen (FilePath, "r");
	if(fp3<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf2,15,1,fp3);			
		printf("Geo Location %s\n",Buf2);
		memset(RawBuf,0,30);
		strcpy(RawBuf,"Geo Location : ");
		if( (Buf2[0]>= 'a' && Buf2[0]<= 'z') || (Buf2[0]>= 'A' && Buf2[0] <= 'Z') || (Buf2[0]>= 0 && Buf2[0] <= 9) ) 
		{
			strcat(RawBuf,Buf2);
		}
		gtk_entry_set_text(entry2,RawBuf);
	}		
	fclose(fp3);
}

int StartGtk(void)
{
	GoToMainScreen();	
	gtk_main ();
	g_free (priv);
	return 0;
}

void GoToMainScreen(void)
{
	MainWindowEn = 1;
	if(SetWindowEn == 1)
	{
		SetWindowEn = 0;
		g_object_unref (SetBuilder);
		gtk_widget_hide(SettingWindow);
		gtk_widget_hide(SettingWindow);
	}
	
	Main_vbox0En = 0;
	Main_vbox1En	= 0;
	Main_vbox2En	= 0;
	Main_vbox3En	= 0;
	
	Main_V0_Index = 0;
	Main_V1_Index = 0;
	Main_V2_Index = 0;
	Main_V3_Index = 0;
	
	Main_V0_Index_Cnt = 0;
	Main_V1_Index_Cnt = 0;
	Main_V2_Index_Cnt = 0;
	Main_V3_Index_Cnt = 0;

	MainWindowEn = 1;		
	MainWindow = CreateHomeScreen();
	gtk_widget_show_all (MainWindow);
}

static GtkWidget* CreateHomeScreen (void)
{	
	GtkWidget *PtrSetingButton,*PtrConfigButton,*PtrModeButton,*PtrHelpButton;
	GtkImage  *imageBG;	
	GError* error = NULL;
	HomeBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (HomeBuilder, UI_FILE_0, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	
	gtk_builder_connect_signals (HomeBuilder, NULL);
	MainWindow = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, TOP_WINDOW));
	if(!MainWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",TOP_WINDOW,UI_FILE_0);
	}

	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);
	
   
	PtrSetingButton = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "setting"));
	g_signal_connect (G_OBJECT (PtrSetingButton), "clicked", G_CALLBACK (GoToSettingScreen), NULL);	
	
	PtrConfigButton = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "config"));
	g_signal_connect (G_OBJECT (PtrConfigButton), "clicked", G_CALLBACK (GoToConfigScreen), NULL);	

	PtrModeButton = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "mode"));
	//g_signal_connect (G_OBJECT (PtrModeButton), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	PtrHelpButton = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "help"));
	//g_signal_connect (G_OBJECT (PtrHelpButton), "clicked", G_CALLBACK (GoToBliScreen), NULL);	

	entry0 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry0"));
	entry1 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry1"));
	entry2 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry2"));
	entry3 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry3"));
	entry4 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry4"));
	entry5 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry5"));
	entry6 = GTK_WIDGET (gtk_builder_get_object (HomeBuilder, "entry6"));
	
	system("clear");
	if(Main_vbox0En == 0)
	{
		vbox0 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(MainWindow),vbox0 );
		GtkFrame *gvp = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (HomeBuilder,"view"));
		gtk_box_pack_start( GTK_BOX( vbox0 ), gvp, FALSE, FALSE, 0 );
		Main_View_0_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp ), Main_View_0_List );
		Main_vbox0En = 1;
	}

	if(Main_vbox1En == 0)
	{
		vbox1 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(MainWindow),vbox1 );			
		GtkFrame *gvp1 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (HomeBuilder,"view1"));
		gtk_box_pack_start( GTK_BOX( vbox1 ), gvp1, FALSE, FALSE, 0 );			
		Main_View_1_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp1 ), Main_View_1_List );
		Main_vbox1En = 1;
	}
	
	if(Main_vbox2En == 0)
	{
		vbox2 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(MainWindow),vbox2 );			
		GtkFrame *gvp2 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (HomeBuilder,"view2"));
		gtk_box_pack_start( GTK_BOX( vbox2 ), gvp2, FALSE, FALSE, 0 );			
		Main_View_2_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp2 ), Main_View_2_List );
		Main_vbox2En = 1;
	}

	if(Main_vbox3En == 0)
	{
		vbox3 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(MainWindow),vbox3 );
		GtkFrame *gvp3 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (HomeBuilder,"view3"));
		gtk_box_pack_start( GTK_BOX( vbox3), gvp3, FALSE, FALSE, 0 );
		Main_View_3_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp3 ), Main_View_3_List );
		Main_vbox3En = 1;
	}
		
	MainViewList_0();	
	priv = g_malloc (sizeof (struct _Private));
	g_object_unref (HomeBuilder);	
	return MainWindow;
}




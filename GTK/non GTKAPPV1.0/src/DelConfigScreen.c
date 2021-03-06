#include"include/main.h"

void GoToConfigDeleteScreen(void);
void QuitConfigDeleteWindow(void);
void DelViewList_0(void);
void DelViewList_1(void);
void DelViewList_2(void);
void DelViewList_3(void);

extern void GoToPopUPDelScreen(void);
extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToMainScreen(void);
extern void GoToSettingScreen(void);

/*****************************************************************************************************************
                              Variable Declaration
******************************************************************************************************************/

extern int MainWindowEn,SetWindowEn,ConfWindowEn,ConfDeleteWindowEn,ConfDeleteWindowEn;
extern GtkBuilder *ConfBuilder,*ConfDeleteBuilder, *SetBuilder, *BpBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*ConfDeleteWindow,*SettingWindow;

GtkWidget *DelBtn0,*DelBtn1,*DelBtn2,*DelBtn3;
GtkWidget *Button1,*Button2,*Button3,*Button4,*Button5;
GtkImage  *imageBG;	

volatile int Del_Config_Vbox0En = 0;
volatile int Del_Config_Vbox1En = 0;
volatile int Del_Config_Vbox2En = 0;
volatile int Del_Config_Vbox3En = 0;

volatile int Del_V0_Index_Cnt = 0;
volatile int Del_V1_Index_Cnt = 0;
volatile int Del_V2_Index_Cnt = 0;
volatile int Del_V3_Index_Cnt = 0;

volatile char Del_DBMS_Path_0[30] = "./src/dbms/";
volatile char Del_DBMS_Path_1[30];
volatile char Del_DBMS_Path_2[30];
volatile char Del_DBMS_Path_3[30];
volatile char Del_DBMS_Path_4[30];


volatile char *Del_View_0_Buffer[100]; 
volatile char *Del_View_1_Buffer[100]; 
volatile char *Del_View_2_Buffer[100]; 
volatile char *Del_View_3_Buffer[100]; 

volatile char	Del_DisableCallBack0 = 0;
volatile char Del_DisableCallBack1 = 0;
volatile char Del_DisableCallBack2 = 0;
volatile char Del_DisableCallBack3 = 0;

volatile char Del_vbox0En;
volatile char Del_vbox1En;
volatile char Del_vbox2En;
volatile char Del_vbox3En;
int Del_V0_Index = 0,Del_V1_Index = 0,Del_V2_Index=0,Del_V3_Index=0;

DIR  *ptrDir0Del,*ptrDir1Del,*ptrDir2Del,*ptrDir3Del;
GtkWidget *vbox0,*vbox1,*vbox2,*vbox3;
struct dirent *dirlistdel0,*dirlistdel1,*dirlistdel2,*dirlistdel3;
static GtkComboBoxText *Del_View_0_List,*Del_View_1_List,*Del_View_2_List,*Del_View_3_List;

volatile char Del_NewDirPath_0[30];
volatile char Del_NewDirPath_1[30];  
volatile char Del_NewDirPath_2[30];  
volatile char Del_NewDirPath_3[30]; 

volatile int DelConfig_Vbox0En = 0;
volatile int DelConfig_Vbox1En = 0;
volatile int DelConfig_Vbox2En = 0;
volatile int DelConfig_Vbox3En = 0;
volatile unsigned char Del_Path_0[10];
volatile unsigned char Del_Path_1[10];
volatile unsigned char Del_Path_2[10];
volatile unsigned char Del_Path_3[10];
 
/*****************************************************************************************************************
                             Main Code Starts Here 
******************************************************************************************************************/

static void DelConfig_Vbox0(void)
{	
	DelConfig_Vbox0En = 1;
	printf("DelConfig_Vbox0 called \n");	
	memset(Del_NewDirPath_0,0,30);
	strcpy(Del_NewDirPath_0,Del_DBMS_Path_1);
	printf("Del_NewDirPath_0 Path %s \n",Del_NewDirPath_0);
	
	g_object_unref (ConfDeleteBuilder);
	gtk_widget_hide(ConfDeleteWindow);
	
	GoToPopUPDelScreen();
}

static void DelConfig_Vbox1(void)
{
	DelConfig_Vbox1En = 1;
	printf("DelConfig_Vbox1 called \n");	
	memset(Del_NewDirPath_1,0,30);
	strcpy(Del_NewDirPath_1,Del_DBMS_Path_2);
	printf("Del_NewDirPath_1 Path %s \n",Del_NewDirPath_1);
	
	g_object_unref (ConfDeleteBuilder);
	gtk_widget_hide(ConfDeleteWindow);
	
	GoToPopUPDelScreen();
}

static void DelConfig_Vbox2(void)
{
	DelConfig_Vbox2En = 1;
	printf("DelConfig_Vbox2 called \n");	
	memset(Del_NewDirPath_2,0,30);
	strcpy(Del_NewDirPath_2,Del_DBMS_Path_3);
	printf("Del_NewDirPath_2 Path %s \n",Del_NewDirPath_2);
	
	g_object_unref (ConfDeleteBuilder);
	gtk_widget_hide(ConfDeleteWindow);
	
	GoToPopUPDelScreen();
}

static void DelConfig_Vbox3(void)
{
	DelConfig_Vbox3En = 1;
	printf("DelConfig_Vbox3 called \n");	
	memset(Del_NewDirPath_3,0,30);
	strcpy(Del_NewDirPath_3,Del_DBMS_Path_4);
	printf("Del_NewDirPath_3 Path %s \n",Del_NewDirPath_3);	
	g_object_unref (ConfDeleteBuilder);
	gtk_widget_hide(ConfDeleteWindow);	
	GoToPopUPDelScreen();	
}

static void CallBackFrom_Del_View_0( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	char *string = gtk_combo_box_text_get_active_text( Del_View_0_List );

	Del_V1_Index = 0;
	Del_V2_Index = 0;
	Del_V3_Index = 0;
	
	if(Del_DisableCallBack0)
	{
		printf("\n Del_DisableCallBack0 \n");
		return;
	}
			
	if(DelConfig_Vbox0En)
		return;		

	gtk_combo_box_set_active_id(Del_View_0_List, string);
	
	if(string == NULL)
		return;
		
	g_print( "CallBackFrom_Del_View_0: >> %s <<\n", ( string ? string : "NULL" ) );
	
	Del_V0_Index_Cnt = 0;
	Del_DisableCallBack1 = 1;
	ptrDir0Del = opendir(Del_DBMS_Path_0);
	if (ptrDir0Del)
	{
		while ((dirlistdel0 = readdir(ptrDir0Del)) != NULL)
		{
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Del_View_0_Buffer[Del_V0_Index_Cnt]=dirlistdel0->d_name;
				printf("Data %s\n", Del_View_0_Buffer[Del_V0_Index_Cnt]);				
				Del_V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0Del);
	}
			
	for(i=0;i<Del_V0_Index_Cnt;i++)
	{
		if(strcmp(Del_View_0_Buffer[i],string) == 0)
		{
			Del_V0_Index = i;	
			memset(Del_Path_0,0,10);
			strcat(Del_Path_0,Del_View_0_Buffer[Del_V0_Index]);
			printf("Del_Path_0 %s \n",Del_Path_0);
			if(Del_Path_0[0] == NULL)
			{
				printf("Sorry Path 0 is empty \n");
				return;
			}
			g_free( string );
			memset(Del_DBMS_Path_1,0,30);
			memset(Del_DBMS_Path_2,0,30);
			memset(Del_DBMS_Path_3,0,30);
			strcat(Del_DBMS_Path_1,"./src/dbms/");
			strcat(Del_DBMS_Path_1,Del_Path_0);
			printf("Calling DelViewList_0 with Path %s \n",Del_DBMS_Path_1);
			DelViewList_1();	
			return;
		}
	}	
	g_free( string );
}

static void CallBackFrom_Del_View_1( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Del_View_1_List );

	if(Del_DisableCallBack1 == 1)
	{
		printf("\n Del_DisableCallBack1 \n");
		return;
	}
		
	if(DelConfig_Vbox1En)
		return;
	
	gtk_combo_box_set_active_id(Del_View_1_List, string);
	
	if(string == NULL)
		return;	
		
	g_print("CallBackFrom_Del_View_1: >> %s <<\n", ( string ? string : "NULL" ) );
	
	Del_V2_Index = 0;
	Del_V3_Index = 0;
	
	Del_V1_Index_Cnt = 0;	
	ptrDir1Del = opendir(Del_DBMS_Path_1);
	if (ptrDir1Del)
	{
		while ((dirlistdel1 = readdir(ptrDir1Del)) != NULL)
		{
			printf("%s\n", dirlistdel1->d_name);
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Del_View_1_Buffer[Del_V1_Index_Cnt]=dirlistdel1->d_name;
				g_print("Data %s\n", Del_View_1_Buffer[Del_V1_Index_Cnt]);				
				Del_V1_Index_Cnt++;
			}			
		}
		closedir(ptrDir1Del);
	}
			
	for(i=0;i<Del_V1_Index_Cnt;i++)
	{
		if(strcmp(Del_View_1_Buffer[i],string) == 0)
		{				
			Del_V1_Index = i;	
			memset(Del_Path_1,0,10);
			strcat(Del_Path_1,Del_View_1_Buffer[Del_V1_Index]);
			printf("Del_Path_0 %s \n",Del_Path_1);

			if(Del_Path_1[0] == NULL)
			{
				printf("Sorry Path 1 is empty \n");
				return;
			}
			printf("Del_View_1_Buffer[0] %s \n",Del_Path_1);
			g_free( string );
			memset(Del_DBMS_Path_2,0,30);
			memset(Del_DBMS_Path_3,0,30);
			strcat(Del_DBMS_Path_2,Del_DBMS_Path_1);
			strcat(Del_DBMS_Path_2,"/");
			strcat(Del_DBMS_Path_2,Del_Path_1);
			printf("Calling DelViewList_1 with Path%s \n",Del_DBMS_Path_2);
			DelViewList_2();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_Del_View_2( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Del_View_2_List );

	if(Del_DisableCallBack2 == 1)
	{
		printf("\n Del_DisableCallBack2 \n");
		return;
	}	
		
	if(DelConfig_Vbox2En)
		return;
		
	if(string == NULL)
		return;	

	gtk_combo_box_set_active_id(Del_View_2_List, string);
	g_print("CallBackFrom_Del_View_2: >> %s <<\n", ( string ? string : "NULL" ) );

	Del_V3_Index = 0;
	Del_V2_Index_Cnt = 0;

	ptrDir2Del = opendir(Del_DBMS_Path_2);
	if (ptrDir2Del)
	{
		while ((dirlistdel2 = readdir(ptrDir2Del)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Del_View_2_Buffer[Del_V2_Index_Cnt]=dirlistdel2->d_name;
				g_print("Data %s\n", Del_View_2_Buffer[Del_V2_Index_Cnt]);				
				Del_V2_Index_Cnt++;
			}			
		}
		closedir(ptrDir2Del);
	}	
		
	for(i=0;i<Del_V2_Index_Cnt;i++)
	{
		if(strcmp(Del_View_2_Buffer[i],string) == 0)
		{				
			Del_V2_Index = i;	
			memset(Del_Path_2,0,10);
			strcat(Del_Path_2,Del_View_2_Buffer[Del_V2_Index]);
			printf("Del_Path_2 %s \n",Del_Path_2);
			if(Del_Path_2[0] == NULL)
			{
				printf("Sorry Path 2 is empty \n");
				return;
			}
			printf("Del_View_2_Buffer[0] %s \n",Del_Path_2);
			g_free( string );
			memset(Del_DBMS_Path_3,0,30);
			strcat(Del_DBMS_Path_3,Del_DBMS_Path_2);
			strcat(Del_DBMS_Path_3,"/");
			strcat(Del_DBMS_Path_3,Del_Path_2);
			printf("Calling DelViewList_2 with  Path %s \n",Del_DBMS_Path_3);
			DelViewList_3();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_Del_View_3( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( Del_View_3_List );
	
	if(DelConfig_Vbox3En)
		return;

	if(string == NULL)
		return;			

	gtk_combo_box_set_active_id(Del_View_3_List, string);

	if(Del_DisableCallBack3 == 1)
		return;
		
	Del_V3_Index_Cnt = 0;

	ptrDir3Del = opendir(Del_DBMS_Path_3);
	if (ptrDir3Del)
	{
		while ((dirlistdel3 = readdir(ptrDir3Del)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Del_View_3_Buffer[Del_V3_Index_Cnt]=dirlistdel3->d_name;
				g_print("CallBackFrom_Del_View_2 %s\n", Del_View_3_Buffer[Del_V3_Index_Cnt]);				
				Del_V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3Del);
	}	
			
	for(i=0;i<Del_V3_Index_Cnt;i++)
	{
		if(strcmp(Del_View_3_Buffer[i],string) == 0)
		{				
			Del_V3_Index = i;	

			memset(Del_Path_3,0,10);
			strcat(Del_Path_3,Del_View_3_Buffer[Del_V3_Index]);
			printf("Del_Path_3 %s \n",Del_Path_3);
			if(Del_Path_3[0] == NULL)
			{
				printf("Sorry Path 3 is empty \n");
				return;
			}
			
			printf("Del_Path = Del_View_3_Buffer[0] %s \n",Del_Path_3);
			g_free( string );
			memset(Del_DBMS_Path_4,0,30);
			strcat(Del_DBMS_Path_4,Del_DBMS_Path_3);
			strcat(Del_DBMS_Path_4,"/");
			strcat(Del_DBMS_Path_4,Del_Path_3);
			printf("New Del_Path %s \n",Del_DBMS_Path_4);	
			return;
		}
	}
		g_free( string );
}
	

static GtkWidget* CreateConfigDeleteScreen (void)
{	
	GError *error = NULL;	
	ConfDeleteBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (ConfDeleteBuilder, UI_FILE_4 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (ConfDeleteBuilder, NULL);
	
	ConfDeleteWindow = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, CONFIG_DELETE_WINDOW));
	if(!ConfDeleteWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",CONFIG_DELETE_WINDOW,UI_FILE_4 );
	}
	
	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);
	
	
	Button1 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "setting"));
	g_signal_connect (G_OBJECT (Button1), "clicked", G_CALLBACK (GoToSettingScreen), NULL);	
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "config"));
	//g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToBpScreen), NULL);	

	Button3 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "mode"));
	//g_signal_connect (G_OBJECT (Button3), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button4 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "help"));
	//g_signal_connect (G_OBJECT (Button4), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button5 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "back"));
	g_signal_connect (G_OBJECT (Button5), "clicked", G_CALLBACK (QuitConfigDeleteWindow), NULL);	

	DelBtn0 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "del0"));
	g_signal_connect (G_OBJECT (DelBtn0), "clicked", G_CALLBACK (DelConfig_Vbox0), NULL);	
	
	DelBtn1 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "del1"));
	g_signal_connect (G_OBJECT (DelBtn1), "clicked", G_CALLBACK (DelConfig_Vbox1), NULL);	

	DelBtn2 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "del2"));
	g_signal_connect (G_OBJECT (DelBtn2), "clicked", G_CALLBACK (DelConfig_Vbox2), NULL);	
	
	DelBtn3 = GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder, "del3"));
	g_signal_connect (G_OBJECT (DelBtn3), "clicked", G_CALLBACK (DelConfig_Vbox3), NULL);		

	if(Del_vbox0En == 0)
	{
		vbox0 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(ConfDeleteWindow),vbox0 );
		GtkFrame *gvp = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder,"view"));
		gtk_box_pack_start( GTK_BOX( vbox0 ), gvp, FALSE, FALSE, 0 );
		Del_View_0_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp ), Del_View_0_List );
		Del_vbox0En = 1;
	}

	if(Del_vbox1En == 0)
	{
		vbox1 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(ConfDeleteWindow),vbox1 );			
		GtkFrame *gvp1 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder,"view1"));
		gtk_box_pack_start( GTK_BOX( vbox1 ), gvp1, FALSE, FALSE, 0 );			
		Del_View_1_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp1 ), Del_View_1_List );
		Del_vbox1En = 1;
	}
	
	if(Del_vbox2En == 0)
	{
		vbox2 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(ConfDeleteWindow),vbox2 );			
		GtkFrame *gvp2 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder,"view2"));
		gtk_box_pack_start( GTK_BOX( vbox2 ), gvp2, FALSE, FALSE, 0 );			
		Del_View_2_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp2 ), Del_View_2_List );
		Del_vbox2En = 1;
	}

	if(Del_vbox3En == 0)
	{
		vbox3 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(ConfDeleteWindow),vbox3 );
		GtkFrame *gvp3 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfDeleteBuilder,"view3"));
		gtk_box_pack_start( GTK_BOX( vbox3), gvp3, FALSE, FALSE, 0 );
		Del_View_3_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp3 ), Del_View_3_List );
		Del_vbox3En = 1;
	}
	

	
	DelViewList_0();
	g_object_unref (ConfDeleteBuilder);	
	return ConfDeleteWindow;
}

void Del_ResetDisables(void)
{
	Del_DisableCallBack0 = 0;
	Del_DisableCallBack1 = 0;
	Del_DisableCallBack2 = 0;
}

void DelViewList_0(void)
{
	Del_vbox1En = 0;
	Del_vbox2En = 0;
	Del_vbox3En = 0;
	Del_V0_Index = 0;
	
	printf("***********************   DelViewList_0   **********************\n");
	/********************************************************************************************
																						Vbox 0 
	*********************************************************************************************/
	Del_DisableCallBack0 = 1;
	Del_DisableCallBack1 = 1;
	Del_DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_0_List));

	ptrDir0Del = opendir(Del_DBMS_Path_0);
	if (ptrDir0Del)
	{
		Del_V0_Index_Cnt = 0;
		while ((dirlistdel0 = readdir(ptrDir0Del)) != NULL)
		{
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Del_View_0_Buffer[Del_V0_Index_Cnt]=dirlistdel0->d_name;                         
				Del_V0_Index_Cnt++;
			}	
		}
	}
	
	if(Del_V0_Index_Cnt == 0)
	{
		printf("\nSorry Del_V0_Index_Cnt is %d\n",Del_V0_Index_Cnt);
		Del_ResetDisables();
		return;
	}
		
	ptrDir0Del = opendir(Del_DBMS_Path_0);
	ptrDir0Del = opendir(Del_DBMS_Path_0);
	if (ptrDir0Del)
	{
		Del_V0_Index_Cnt = 0;
		while ((dirlistdel0 = readdir(ptrDir0Del)) != NULL)
		{
			//printf("%s\n", dirlistdel0->d_name);
			if((strcmp(dirlistdel0->d_name , ".") != 0) && (strcmp(dirlistdel0->d_name,"..") != 0))
			{
				Del_View_0_Buffer[Del_V0_Index_Cnt]=dirlistdel0->d_name;
				printf("Vbox 0 Adding %s , %d \n", Del_View_0_Buffer[Del_V0_Index_Cnt],Del_V0_Index);	
				if(Del_V0_Index_Cnt == Del_V0_Index)
				{
					memset(Del_Path_0,0,10);
					strcat(Del_Path_0,Del_View_0_Buffer[Del_V0_Index_Cnt]);
					printf("Del_Path_0 %s \n",Del_Path_0);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Del_View_0_List), Del_View_0_Buffer[Del_V0_Index_Cnt]);
				Del_V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0Del);
	}
	
	if(Del_V0_Index_Cnt == 0)
	{
		printf("\nSorry Del_V0_Index_Cnt is %d\n",Del_V0_Index_Cnt);
		Del_ResetDisables();
		return;
	}
	
	if(Del_Path_0[0] == NULL)
	{
		printf("List Path 0 is empty \n");
		Del_ResetDisables();
		return;
	}
			
	memset(Del_DBMS_Path_1,0,30);
	strcat(Del_DBMS_Path_1,"./src/dbms/");
	strcat(Del_DBMS_Path_1,Del_Path_0);
	printf("New Path for VBox 1 %s \n",Del_DBMS_Path_1);
	gtk_combo_box_set_active((GtkComboBox *)(Del_View_0_List),Del_V0_Index);
	g_signal_connect( G_OBJECT( Del_View_0_List ), "changed", G_CALLBACK( CallBackFrom_Del_View_0), NULL );
	Del_V0_Index = 0;
	printf("******** DelViewList_0 Bye **********\n");
	DelViewList_1();
}

void DelViewList_1(void)
{
	int i = 0;		

	Del_V1_Index = 0;
	printf("***********************   DelViewList_1   **********************\n");
	Del_DisableCallBack0 = 0;
	Del_DisableCallBack1 = 1;
	Del_DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_1_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_3_List));
	
	ptrDir1Del = opendir(Del_DBMS_Path_1);
	if (ptrDir1Del)
	{
		Del_V1_Index_Cnt = 0;
		while ((dirlistdel1 = readdir(ptrDir1Del)) != NULL)
		{
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Del_View_1_Buffer[Del_V1_Index_Cnt]=dirlistdel1->d_name;                          
				Del_V1_Index_Cnt++;
			}	
		}
	}
	
	if(Del_V1_Index_Cnt == 0)
	{
		printf("\nSorry Del_V1_Index_Cnt is %d\n",Del_V1_Index_Cnt);
		Del_ResetDisables();
		return;
	}
	memset(Del_Path_1,0,10);
	ptrDir1Del = opendir(Del_DBMS_Path_1);
	if (ptrDir1Del)
	{
		Del_V1_Index_Cnt = 0;
		while ((dirlistdel1 = readdir(ptrDir1Del)) != NULL)
		{
			if((strcmp(dirlistdel1->d_name , ".") != 0) && (strcmp(dirlistdel1->d_name,"..") != 0))
			{
				Del_View_1_Buffer[Del_V1_Index_Cnt]=dirlistdel1->d_name;
				printf("Vox 1 Adding %s , %d \n", Del_View_1_Buffer[Del_V1_Index_Cnt],Del_V1_Index);				
				if(Del_V1_Index_Cnt == Del_V1_Index)
				{
					strcat(Del_Path_1,Del_View_1_Buffer[Del_V1_Index_Cnt]);
					printf("Del_Path_1 %s \n",Del_Path_1);
				}
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Del_View_1_List), Del_View_1_Buffer[Del_V1_Index_Cnt]);                               
				Del_V1_Index_Cnt++;
			}	
		}
		closedir(ptrDir1Del);
	}

	if(Del_V1_Index_Cnt == 0)
	{
		printf("\nSorry Del_V1_Index_Cnt is %d\n",Del_V1_Index_Cnt);
		Del_ResetDisables();
		return;
	}

	if(Del_Path_1[0] == NULL)
	{
		printf("List Path 1 is empty \n");
		Del_ResetDisables();
		return;
	}
			
	memset(Del_DBMS_Path_2,0,30);
	strcat(Del_DBMS_Path_2,Del_DBMS_Path_1);
	strcat(Del_DBMS_Path_2,"/");
	strcat(Del_DBMS_Path_2,Del_Path_1);
	printf("New Path for Box 2 %s \n",Del_DBMS_Path_2);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Del_View_1_List),Del_V1_Index);
	g_signal_connect( G_OBJECT( Del_View_1_List ), "changed", G_CALLBACK( CallBackFrom_Del_View_1 ), NULL );	
	Del_V1_Index = 0;
	printf("******** DelViewList_1 Bye **********\n");
	DelViewList_2();
}

void DelViewList_2(void)
{
	int i = 0;
	
	Del_V2_Index = 0;
	Del_DisableCallBack0 = 0;
	Del_DisableCallBack1 = 0;
	Del_DisableCallBack2 = 1;

	printf("***********************   DelViewList_2   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_3_List));
	
	ptrDir2Del = opendir(Del_DBMS_Path_2);
	if (ptrDir2Del)
	{
		Del_V2_Index_Cnt = 0;
		while ((dirlistdel2 = readdir(ptrDir2Del)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Del_View_2_Buffer[Del_V2_Index_Cnt]=dirlistdel2->d_name;
				printf("Vox 2 Adding %s , %d \n", Del_View_2_Buffer[Del_V2_Index_Cnt],Del_V2_Index);	                            
				Del_V2_Index_Cnt++;
			}	
		}
	}
	
	if(Del_V2_Index_Cnt == 0)
	{
		printf("\nSorry Del_V2_Index_Cnt is %d\n",Del_V2_Index_Cnt);
		Del_ResetDisables();
		return;
	}		

	ptrDir2Del = opendir(Del_DBMS_Path_2);
	if (ptrDir2Del)
	{
		Del_V2_Index_Cnt = 0;
		while ((dirlistdel2 = readdir(ptrDir2Del)) != NULL)
		{
			if((strcmp(dirlistdel2->d_name , ".") != 0) && (strcmp(dirlistdel2->d_name,"..") != 0))
			{
				Del_View_2_Buffer[Del_V2_Index_Cnt]=dirlistdel2->d_name;
				printf("Vox 2 Adding %s , %d \n", Del_View_2_Buffer[Del_V2_Index_Cnt],Del_V2_Index);				
				if(Del_V2_Index_Cnt == Del_V2_Index)
				{
					memset(Del_Path_2,0,10);
					strcat(Del_Path_2,Del_View_2_Buffer[Del_V2_Index_Cnt]);
					printf("Del_Path_2 %s \n",Del_Path_2);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Del_View_2_List), Del_View_2_Buffer[Del_V2_Index_Cnt]);                               
				Del_V2_Index_Cnt++;
			}	
		}
		closedir(ptrDir2Del);
	}

	if(Del_V2_Index_Cnt == 0)
	{
		printf("\nSorry Del_V2_Index_Cnt is %d\n",Del_V2_Index_Cnt);
		Del_ResetDisables();
		return;
	}	

	if(Del_Path_2[0] == NULL)
	{
		printf("List Path 2 is empty \n");
		Del_ResetDisables();
		return;
	}		
	memset(Del_DBMS_Path_3,0,30);
	strcat(Del_DBMS_Path_3,Del_DBMS_Path_2);
	strcat(Del_DBMS_Path_3,"/");
	strcat(Del_DBMS_Path_3,Del_Path_2);
	printf("New Path for Box 3 %s \n",Del_DBMS_Path_3);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Del_View_2_List),Del_V2_Index);
	g_signal_connect( G_OBJECT( Del_View_2_List ), "changed", G_CALLBACK( CallBackFrom_Del_View_2 ), NULL );	

	Del_V2_Index = 0;
	printf("******** DelViewList_2 Bye **********\n");
	DelViewList_3();	
}

void DelViewList_3(void)
{
	int i = 0;	
	
	Del_V3_Index = 0;
	Del_DisableCallBack0 = 0;
	Del_DisableCallBack1 = 0;
	Del_DisableCallBack2 = 1;
	Del_DisableCallBack3 = 1;
	
	printf("***********************   DelViewList_3   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(Del_View_3_List));
	ptrDir3Del = opendir(Del_DBMS_Path_3);
	printf("New Path for Box 3 %s \n",Del_DBMS_Path_3);
	if (ptrDir3Del)
	{
		Del_V3_Index_Cnt = 0;
		while ((dirlistdel3 = readdir(ptrDir3Del)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Del_View_3_Buffer[Del_V3_Index_Cnt]=dirlistdel3->d_name;                          
				Del_V3_Index_Cnt++;
			}	
		}
	}
	
	if(Del_V3_Index_Cnt == 0)
	{
		printf("\nSorry Del_V3_Index_Cnt is %d\n",Del_V3_Index_Cnt);
		Del_ResetDisables();
		return;
	}	

	ptrDir3Del = opendir(Del_DBMS_Path_3);
	if (ptrDir3Del)
	{
		Del_V3_Index_Cnt = 0;
		while ((dirlistdel3 = readdir(ptrDir3Del)) != NULL)
		{
			if((strcmp(dirlistdel3->d_name , ".") != 0) && (strcmp(dirlistdel3->d_name,"..") != 0))
			{
				Del_View_3_Buffer[Del_V3_Index_Cnt]=dirlistdel3->d_name;   
				printf("Vox 3 Adding %s , %d \n", Del_View_3_Buffer[Del_V3_Index_Cnt],Del_V3_Index);			
				if(Del_V3_Index_Cnt == 0)
				{
					memset(Del_Path_3,0,10);
					strcat(Del_Path_3,Del_View_3_Buffer[0]);
					printf("Del_Path_3 %s \n",Del_Path_3);
				}		
				gtk_combo_box_text_append_text((GtkComboBoxText *)(Del_View_3_List), Del_View_3_Buffer[Del_V3_Index_Cnt]);
				Del_V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3Del);
	}

	if(Del_V3_Index_Cnt == 0)
	{
		printf("\nSorry Del_V3_Index_Cnt is %d\n",Del_V3_Index_Cnt);
		Del_ResetDisables();
		return;
	}
	if(Del_Path_3[0] == NULL)
	{
		printf("List Path 3 is empty \n");
		Del_ResetDisables();
	}
	
	memset(Del_DBMS_Path_4,0,30);
	strcat(Del_DBMS_Path_4,Del_DBMS_Path_3);
	strcat(Del_DBMS_Path_4,"/");
	strcat(Del_DBMS_Path_4,Del_Path_3);
	printf("New Del_DBMS_Path_4 %s \n",Del_DBMS_Path_4);	
	
	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(Del_View_3_List),Del_V3_Index);
	g_signal_connect( G_OBJECT( Del_View_3_List ), "changed", G_CALLBACK( CallBackFrom_Del_View_3), NULL );	
	Del_DisableCallBack2 = 0;
	Del_DisableCallBack3 = 0;	


	Del_V3_Index = 0;
	printf("******** DelViewList_3 Bye **********\n");
}

void GoToConfigDeleteScreen(void)
{
	if(SetWindowEn == 1)
	{
		SetWindowEn = 0;
		g_object_unref (SetBuilder);
		gtk_widget_hide(SettingWindow);
		gtk_widget_hide(SettingWindow);
	}
	
	Del_vbox0En = 0;
	Del_vbox1En	= 0;
	Del_vbox2En	= 0;
	Del_vbox3En	= 0;
	
	Del_V0_Index = 0;
	Del_V1_Index = 0;
	Del_V2_Index = 0;
	Del_V3_Index = 0;

	DelConfig_Vbox0En = 0;
	DelConfig_Vbox1En = 0;
	DelConfig_Vbox2En = 0;
	DelConfig_Vbox3En = 0;

	Del_V0_Index_Cnt = 0;
	Del_V1_Index_Cnt = 0;
	Del_V2_Index_Cnt = 0;
	Del_V3_Index_Cnt = 0;

	ConfDeleteWindow = CreateConfigDeleteScreen();
	gtk_widget_show_all(ConfDeleteWindow);
	ConfDeleteWindowEn = 1;	
}

void QuitConfigDeleteWindow(void)
{
	ConfDeleteWindowEn = 0;
	g_object_unref (ConfDeleteBuilder);
	gtk_widget_hide(ConfDeleteWindow);
	GoToMainScreen();
}


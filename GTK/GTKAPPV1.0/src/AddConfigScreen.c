#include"include/main.h"

void ResetDisables(void);
void AddViewList_0(void);
void AddViewList_1(void);
void AddViewList_2(void);
void AddViewList_3(void);
void GoToConfigAddScreen(void);
void QuitConfigAddWindow(void);

extern void GoToDetailScreen(void);
extern void GoToPopUPScreen(void);
extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToMainScreen(void);
extern void GoToSettingScreen(void);

/*****************************************************************************************************************
                              Variable Declaration
******************************************************************************************************************/

extern int MainWindowEn,SetWindowEn,ConfWindowEn,ConfAddWindowEn;
extern GtkBuilder *ConfBuilder,*ConfAddBuilder, *SetBuilder, *BpBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*ConfAddWindow,*SettingWindow;

GtkWidget *entry0,*entry1,*entry2,*entry3;
GtkWidget *AddBtn0,*AddBtn1,*AddBtn2,*AddBtn3,*AddDetails;
GtkWidget *Button1,*Button2,*Button3,*Button4,*Button5;
GtkImage  *imageBG;	
GError *error = NULL;	

volatile int AddConfig_Vbox0En = 0;
volatile int AddConfig_Vbox1En = 0;
volatile int AddConfig_Vbox2En = 0;
volatile int AddConfig_Vbox3En = 0;

volatile int V0_Index_Cnt = 0;
volatile int V1_Index_Cnt = 0;
volatile int V2_Index_Cnt = 0;
volatile int V3_Index_Cnt = 0;

volatile char DBMS_Path_0[30] = "./src/dbms/";
volatile char DBMS_Path_1[30];
volatile char DBMS_Path_2[30];
volatile char DBMS_Path_3[30];
volatile char DBMS_Path_4[30];

volatile char *View_0_Buffer[100]; 
volatile char *View_1_Buffer[100]; 
volatile char *View_2_Buffer[100]; 
volatile char *View_3_Buffer[100]; 

volatile unsigned char Path_0[10];
volatile unsigned char Path_1[10];
volatile unsigned char Path_2[10];
volatile unsigned char Path_3[10];
volatile char DisableCallBack0 = 0;
volatile char DisableCallBack1 = 0;
volatile char DisableCallBack2 = 0;
volatile char DisableCallBack3 = 0;
volatile char vbox0En,vbox1En,vbox2En,vbox3En;
int V0_Index = 0,V1_Index = 0,V2_Index=0,V3_Index=0;


DIR  *ptrDir0,*ptrDir1,*ptrDir2,*ptrDir3;
GtkWidget *vbox0,*vbox1,*vbox2,*vbox3;
struct dirent *dirlist0,*dirlist1,*dirlist2,*dirlist3;
static GtkComboBoxText *View_0_List,*View_1_List,*View_2_List,*View_3_List;
/*****************************************************************************************************************
                             Main Code Starts Here 
******************************************************************************************************************/
char NewDirPath_0[30];
char NewDirPath_1[30];  
char NewDirPath_2[30];  
char NewDirPath_3[30];  

static void AddConfig_Vbox0(void)
{
	char *TextEntry;
	
	AddConfig_Vbox0En = 1;
	printf("AddConfig_Vbox0 called \n");	
	TextEntry = gtk_entry_get_text(entry0);	
	printf("gtk_entry_get_text(entry0) %s \n",TextEntry);
	
	if(TextEntry == 0)
		return;
	
	memset(NewDirPath_0,0,30);
	strcpy(NewDirPath_0,DBMS_Path_0);
	strcat(NewDirPath_0,TextEntry);
	printf("NewDirPath_0 Path %s \n",NewDirPath_0);
	g_object_unref (ConfAddBuilder);
	gtk_widget_hide(ConfAddWindow);
	GoToPopUPScreen();
}

static void AddConfig_Vbox1(void)
{	
	char *TextEntry;
	
	AddConfig_Vbox1En = 1;
 	printf("AddConfig_Vbox1 called \n");
	TextEntry = gtk_entry_get_text(entry1);	
	printf("gtk_entry_get_text(entry1) %s \n",TextEntry);

	if(TextEntry == 0)
		return;
		
	memset(NewDirPath_1,0,30);
	strcpy(NewDirPath_1,DBMS_Path_1);
	strcat(NewDirPath_1,"/");
	strcat(NewDirPath_1,TextEntry);
	printf("NewDirPath_1 Path %s \n",NewDirPath_1);
	g_object_unref (ConfAddBuilder);
	gtk_widget_hide(ConfAddWindow);
	GoToPopUPScreen();
}

static void AddConfig_Vbox2(void)
{
	char *TextEntry;
	
	AddConfig_Vbox2En = 1;
 	printf("AddConfig_Vbox2 called \n"); 
	TextEntry = gtk_entry_get_text(entry2);	
	printf("gtk_entry_get_text(entry2) %s \n",TextEntry);	

	if(TextEntry == 0)
		return;
		
	memset(NewDirPath_2,0,30);
	strcpy(NewDirPath_2,DBMS_Path_2);
	strcat(NewDirPath_2,"/");
	strcat(NewDirPath_2,TextEntry);
	printf("NewDirPath_2 Path %s \n",NewDirPath_2);	
	g_object_unref (ConfAddBuilder);
	gtk_widget_hide(ConfAddWindow);
	GoToPopUPScreen();
}

static void AddConfig_Vbox3(void)
{
	char *TextEntry;

	AddConfig_Vbox3En = 1;
 	printf("AddConfig_Vbox3 called \n"); 
	TextEntry = gtk_entry_get_text(entry3);		
	printf("gtk_entry_get_text(entry3) %s \n",TextEntry);

	if(TextEntry == 0)
		return;
			
	memset(NewDirPath_3,0,30);
	strcpy(NewDirPath_3,DBMS_Path_3);
	strcat(NewDirPath_3,"/");
	strcat(NewDirPath_3,TextEntry);
	printf("NewDirPath_3 Path %s \n",NewDirPath_3);
	g_object_unref (ConfAddBuilder);
	gtk_widget_hide(ConfAddWindow);
	GoToPopUPScreen();
}

static void CallBackFrom_View_0( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	char *string = gtk_combo_box_text_get_active_text( View_0_List );

	V1_Index = 0;
	V2_Index = 0;
	V3_Index = 0;
	
	if(DisableCallBack0)
	{
		printf("\n DisableCallBack0 \n");
		return;
	}
			
	if(AddConfig_Vbox0En)
		return;		

	gtk_combo_box_set_active_id(View_0_List, string);
	
	if(string == NULL)
		return;
		
	g_print( "CallBackFrom_View_0: >> %s <<\n", ( string ? string : "NULL" ) );
	
	V0_Index_Cnt = 0;
	DisableCallBack1 = 1;
	ptrDir0 = opendir(DBMS_Path_0);
	if (ptrDir0)
	{
		while ((dirlist0 = readdir(ptrDir0)) != NULL)
		{
			if((strcmp(dirlist0->d_name , ".") != 0) && (strcmp(dirlist0->d_name,"..") != 0))
			{
				View_0_Buffer[V0_Index_Cnt]=dirlist0->d_name;
				printf("Data %s\n", View_0_Buffer[V0_Index_Cnt]);				
				V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0);
	}
			
	for(i=0;i<V0_Index_Cnt;i++)
	{
		if(strcmp(View_0_Buffer[i],string) == 0)
		{
			V0_Index = i;	
			memset(Path_0,0,10);
			strcat(Path_0,View_0_Buffer[V0_Index]);
			printf("Path_0 %s \n",Path_0);
			if(Path_0[0] == NULL)
			{
				printf("Sorry Path 0 is empty \n");
				return;
			}
			g_free( string );
			memset(DBMS_Path_1,0,30);
			memset(DBMS_Path_2,0,30);
			memset(DBMS_Path_3,0,30);
			strcat(DBMS_Path_1,"./src/dbms/");
			strcat(DBMS_Path_1,Path_0);
			printf("Calling AddViewList_0 with Path %s \n",DBMS_Path_1);
			AddViewList_1();	
			return;
		}
	}	
	g_free( string );
}

static void CallBackFrom_View_1( GtkComboBox *combo, gpointer data )
{
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( View_1_List );

	if(DisableCallBack1 == 1)
	{
		printf("\n DisableCallBack1 \n");
		return;
	}
		
	if(AddConfig_Vbox1En)
		return;
	
	gtk_combo_box_set_active_id(View_1_List, string);
	
	if(string == NULL)
		return;	
		
	g_print("CallBackFrom_View_1: >> %s <<\n", ( string ? string : "NULL" ) );
	
	V2_Index = 0;
	V3_Index = 0;
	
	V1_Index_Cnt = 0;	
	ptrDir1 = opendir(DBMS_Path_1);
	if (ptrDir1)
	{
		while ((dirlist1 = readdir(ptrDir1)) != NULL)
		{
			printf("%s\n", dirlist1->d_name);
			if((strcmp(dirlist1->d_name , ".") != 0) && (strcmp(dirlist1->d_name,"..") != 0))
			{
				View_1_Buffer[V1_Index_Cnt]=dirlist1->d_name;
				g_print("Data %s\n", View_1_Buffer[V1_Index_Cnt]);				
				V1_Index_Cnt++;
			}			
		}
		closedir(ptrDir1);
	}
			
	for(i=0;i<V1_Index_Cnt;i++)
	{
		if(strcmp(View_1_Buffer[i],string) == 0)
		{				
			V1_Index = i;	
			memset(Path_1,0,10);
			strcat(Path_1,View_1_Buffer[V1_Index]);
			printf("Path_0 %s \n",Path_1);

			if(Path_1[0] == NULL)
			{
				printf("Sorry Path 1 is empty \n");
				return;
			}
			printf("View_1_Buffer[0] %s \n",Path_1);
			g_free( string );
			memset(DBMS_Path_2,0,30);
			memset(DBMS_Path_3,0,30);
			strcat(DBMS_Path_2,DBMS_Path_1);
			strcat(DBMS_Path_2,"/");
			strcat(DBMS_Path_2,Path_1);
			printf("Calling AddViewList_1 with Path%s \n",DBMS_Path_2);
			AddViewList_2();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_View_2( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( View_2_List );

	if(DisableCallBack2 == 1)
	{
		printf("\n DisableCallBack2 \n");
		return;
	}	
		
	if(AddConfig_Vbox2En)
		return;
		
	if(string == NULL)
		return;	

	gtk_combo_box_set_active_id(View_2_List, string);
	g_print("CallBackFrom_View_2: >> %s <<\n", ( string ? string : "NULL" ) );

	V3_Index = 0;
	V2_Index_Cnt = 0;

	ptrDir2 = opendir(DBMS_Path_2);
	if (ptrDir2)
	{
		while ((dirlist2 = readdir(ptrDir2)) != NULL)
		{
			if((strcmp(dirlist2->d_name , ".") != 0) && (strcmp(dirlist2->d_name,"..") != 0))
			{
				View_2_Buffer[V2_Index_Cnt]=dirlist2->d_name;
				g_print("Data %s\n", View_2_Buffer[V2_Index_Cnt]);				
				V2_Index_Cnt++;
			}			
		}
		closedir(ptrDir2);
	}	
		
	for(i=0;i<V2_Index_Cnt;i++)
	{
		if(strcmp(View_2_Buffer[i],string) == 0)
		{				
			V2_Index = i;	
			memset(Path_2,0,10);
			strcat(Path_2,View_2_Buffer[V2_Index]);
			printf("Path_2 %s \n",Path_2);
			if(Path_2[2] == NULL)
			{
				printf("Sorry Path 2 is empty \n");
				return;
			}
			printf("View_2_Buffer[0] %s \n",Path_2);
			g_free( string );
			memset(DBMS_Path_3,0,30);
			strcat(DBMS_Path_3,DBMS_Path_2);
			strcat(DBMS_Path_3,"/");
			strcat(DBMS_Path_3,Path_2);
			printf("Calling AddViewList_2 with  Path %s \n",DBMS_Path_3);
			AddViewList_3();				
			return;
		}
	}	
	g_free( string );	
}

static void CallBackFrom_View_3( GtkComboBox *combo, gpointer data )
{	
	int i = 0;
	gchar *string = gtk_combo_box_text_get_active_text( View_3_List );
	
	if(AddConfig_Vbox3En)
		return;

	if(string == NULL)
		return;			

	gtk_combo_box_set_active_id(View_3_List, string);

	if(DisableCallBack3 == 1)
		return;
		
	V3_Index_Cnt = 0;

	ptrDir3 = opendir(DBMS_Path_3);
	if (ptrDir3)
	{
		while ((dirlist3 = readdir(ptrDir3)) != NULL)
		{
			if((strcmp(dirlist3->d_name , ".") != 0) && (strcmp(dirlist3->d_name,"..") != 0))
			{
				View_3_Buffer[V3_Index_Cnt]=dirlist3->d_name;
				g_print("CallBackFrom_Del_View_3 %s\n", View_3_Buffer[V3_Index_Cnt]);				
				V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3);
	}	
	
	for(i=0;i<V3_Index_Cnt;i++)
	{
		if(strcmp(View_3_Buffer[i],string) == 0)
		{				
			V3_Index = i;	

			memset(Path_3,0,10);
			strcat(Path_3,View_3_Buffer[V3_Index]);
			printf("Path_3 %s \n",Path_3);
			if(Path_3[0] == NULL)
			{
				printf("Sorry Path 3 is empty \n");
				return;
			}
			
			printf("Del_Path = View_3_Buffer[0] %s \n",Path_3);
			g_free( string );
			memset(DBMS_Path_4,0,30);
			strcat(DBMS_Path_4,DBMS_Path_3);
			strcat(DBMS_Path_4,"/");
			strcat(DBMS_Path_4,Path_3);
			printf("New Del_Path %s \n",DBMS_Path_4);	
			
			memset(NewDirPath_3,0,30);
			strcpy(NewDirPath_3,DBMS_Path_4);
			printf("NewDirPath_3 %s \n",NewDirPath_3);	
			return;
		}
	}
}


static GtkWidget* CreateConfigAddScreen (void)
{	
	ConfAddBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (ConfAddBuilder, UI_FILE_3 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (ConfAddBuilder, NULL);
	
	ConfAddWindow = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, CONFIG_ADD_WINDOW));
	if(!ConfAddWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",CONFIG_WINDOW,UI_FILE_3 );
	}

	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	Button1 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "setting"));
	g_signal_connect (G_OBJECT (Button1), "clicked", G_CALLBACK (GoToSettingScreen), NULL);	
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "config"));
	//g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToBpScreen), NULL);	

	Button3 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "mode"));
	//g_signal_connect (G_OBJECT (Button3), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button4 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "help"));
	//g_signal_connect (G_OBJECT (Button4), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button5 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "back"));
	g_signal_connect (G_OBJECT (Button5), "clicked", G_CALLBACK (QuitConfigAddWindow), NULL);	

	AddBtn0 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "add0"));
	g_signal_connect (G_OBJECT (AddBtn0), "clicked", G_CALLBACK (AddConfig_Vbox0), NULL);	
	
	AddBtn1 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "add1"));
	g_signal_connect (G_OBJECT (AddBtn1), "clicked", G_CALLBACK (AddConfig_Vbox1), NULL);	

	AddBtn2 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "add2"));
	g_signal_connect (G_OBJECT (AddBtn2), "clicked", G_CALLBACK (AddConfig_Vbox2), NULL);	
	
	AddBtn3 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "add3"));
	g_signal_connect (G_OBJECT (AddBtn3), "clicked", G_CALLBACK (AddConfig_Vbox3), NULL);	
	
	AddDetails = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "details"));
	g_signal_connect (G_OBJECT (AddDetails), "clicked", G_CALLBACK (GoToDetailScreen), NULL);	

	if(vbox0En == 0)
	{
		vbox0 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(ConfAddWindow),vbox0 );
		GtkFrame *gvp = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder,"view"));
		gtk_box_pack_start( GTK_BOX( vbox0 ), gvp, FALSE, FALSE, 0 );
		View_0_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp ), View_0_List );
		vbox0En = 1;
	}

	if(vbox1En == 0)
	{
		vbox1 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(ConfAddWindow),vbox1 );			
		GtkFrame *gvp1 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder,"view1"));
		gtk_box_pack_start( GTK_BOX( vbox1 ), gvp1, FALSE, FALSE, 0 );			
		View_1_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp1 ), View_1_List );
		vbox1En = 1;
	}
	
	if(vbox2En == 0)
	{
		vbox2 = gtk_vbox_new( FALSE, 6 );		
		gtk_container_add( GTK_CONTAINER(ConfAddWindow),vbox2 );			
		GtkFrame *gvp2 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder,"view2"));
		gtk_box_pack_start( GTK_BOX( vbox2 ), gvp2, FALSE, FALSE, 0 );			
		View_2_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp2 ), View_2_List );
		vbox2En = 1;
	}

	if(vbox3En == 0)
	{
		vbox3 = gtk_vbox_new( FALSE, 6 );
		gtk_container_add( GTK_CONTAINER(ConfAddWindow),vbox3 );
		GtkFrame *gvp3 = (GtkFrame *)GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder,"view3"));
		gtk_box_pack_start( GTK_BOX( vbox3), gvp3, FALSE, FALSE, 0 );
		View_3_List = gtk_combo_box_text_new();
		gtk_container_add( GTK_CONTAINER( gvp3 ), View_3_List );
		vbox3En = 1;
	}
	
	entry0 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "entry0"));
	entry1 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "entry1"));
	entry2 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "entry2"));
	entry3 = GTK_WIDGET (gtk_builder_get_object (ConfAddBuilder, "entry3"));
	
	AddViewList_0();
	g_object_unref (ConfAddBuilder);	
	return ConfAddWindow;
}

void ResetDisables(void)
{
	DisableCallBack0 = 0;
	DisableCallBack1 = 0;
	DisableCallBack2 = 0;
}

void AddViewList_0(void)
{
	vbox1En = 0;
	vbox2En = 0;
	vbox3En = 0;
	printf("***********************   AddViewList_0   **********************\n");
	/********************************************************************************************
																						Vbox 0 
	*********************************************************************************************/
	DisableCallBack0 = 1;
	DisableCallBack1 = 1;
	DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_0_List));

	ptrDir0 = opendir(DBMS_Path_0);
	if (ptrDir0)
	{
		V0_Index_Cnt = 0;
		while ((dirlist0 = readdir(ptrDir0)) != NULL)
		{
			if((strcmp(dirlist0->d_name , ".") != 0) && (strcmp(dirlist0->d_name,"..") != 0))
			{
				View_0_Buffer[V0_Index_Cnt]=dirlist0->d_name;                         
				V0_Index_Cnt++;
			}	
		}
	}
	
	if(V0_Index_Cnt == 0)
	{
		printf("\nSorry V0_Index_Cnt is %d\n",V0_Index_Cnt);
		ResetDisables();
		return;
	}
		
	ptrDir0 = opendir(DBMS_Path_0);
	if (ptrDir0)
	{
		V0_Index_Cnt = 0;
		while ((dirlist0 = readdir(ptrDir0)) != NULL)
		{
			//printf("%s\n", dirlist0->d_name);
			if((strcmp(dirlist0->d_name , ".") != 0) && (strcmp(dirlist0->d_name,"..") != 0))
			{
				View_0_Buffer[V0_Index_Cnt]=dirlist0->d_name;
				printf("Vbox 0 Adding %s , %d \n", View_0_Buffer[V0_Index_Cnt],V0_Index);	
				if(V0_Index_Cnt == V0_Index)
				{
					memset(Path_0,0,10);
					strcat(Path_0,View_0_Buffer[V0_Index_Cnt]);
					printf("Path_0 %s \n",Path_0);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(View_0_List), View_0_Buffer[V0_Index_Cnt]);
				V0_Index_Cnt++;
			}			
		}
		closedir(ptrDir0);
	}
	
	if(V0_Index_Cnt == 0)
	{
		printf("\nSorry V0_Index_Cnt is %d\n",V0_Index_Cnt);
		ResetDisables();
		return;
	}
	
	if(Path_0[0] == NULL)
	{
		printf("List Path 0 is empty \n");
		ResetDisables();
		return;
	}
			
	memset(DBMS_Path_1,0,30);
	strcat(DBMS_Path_1,"./src/dbms/");
	strcat(DBMS_Path_1,Path_0);
	printf("New Path for VBox 1 %s \n",DBMS_Path_1);
	gtk_combo_box_set_active((GtkComboBox *)(View_0_List),V0_Index);
	g_signal_connect( G_OBJECT( View_0_List ), "changed", G_CALLBACK( CallBackFrom_View_0), NULL );
	AddViewList_1();
}

void AddViewList_1(void)
{
	int i = 0;		

	printf("***********************   AddViewList_1   **********************\n");
	DisableCallBack0 = 0;
	DisableCallBack1 = 1;
	DisableCallBack2 = 1;
	
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_1_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_3_List));
	
	ptrDir1 = opendir(DBMS_Path_1);
	if (ptrDir1)
	{
		V1_Index_Cnt = 0;
		while ((dirlist1 = readdir(ptrDir1)) != NULL)
		{
			if((strcmp(dirlist1->d_name , ".") != 0) && (strcmp(dirlist1->d_name,"..") != 0))
			{
				View_1_Buffer[V1_Index_Cnt]=dirlist1->d_name;                          
				V1_Index_Cnt++;
			}	
		}
	}
	
	if(V1_Index_Cnt == 0)
	{
		printf("\nSorry V1_Index_Cnt is %d\n",V1_Index_Cnt);
		ResetDisables();
		return;
	}
	memset(Path_1,0,10);
	ptrDir1 = opendir(DBMS_Path_1);
	if (ptrDir1)
	{
		V1_Index_Cnt = 0;
		while ((dirlist1 = readdir(ptrDir1)) != NULL)
		{
			if((strcmp(dirlist1->d_name , ".") != 0) && (strcmp(dirlist1->d_name,"..") != 0))
			{
				View_1_Buffer[V1_Index_Cnt]=dirlist1->d_name;
				printf("Vox 1 Adding %s , %d \n", View_1_Buffer[V1_Index_Cnt],V1_Index);				
				if(V1_Index_Cnt == V1_Index)
				{
					strcat(Path_1,View_1_Buffer[V1_Index_Cnt]);
					printf("Path_1 %s \n",Path_1);
				}
				gtk_combo_box_text_append_text((GtkComboBoxText *)(View_1_List), View_1_Buffer[V1_Index_Cnt]);                               
				V1_Index_Cnt++;
			}	
		}
		closedir(ptrDir1);
	}

	if(V1_Index_Cnt == 0)
	{
		printf("\nSorry V1_Index_Cnt is %d\n",V1_Index_Cnt);
		ResetDisables();
		return;
	}

	if(Path_1[0] == NULL)
	{
		printf("List Path 1 is empty \n");
		ResetDisables();
		return;
	}
			
	memset(DBMS_Path_2,0,30);
	strcat(DBMS_Path_2,DBMS_Path_1);
	strcat(DBMS_Path_2,"/");
	strcat(DBMS_Path_2,Path_1);
	printf("New Path for Box 2 %s \n",DBMS_Path_2);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(View_1_List),V1_Index);
	g_signal_connect( G_OBJECT( View_1_List ), "changed", G_CALLBACK( CallBackFrom_View_1 ), NULL );	
	AddViewList_2();
}

void AddViewList_2(void)
{
	int i = 0;
	
	DisableCallBack0 = 0;
	DisableCallBack1 = 0;
	DisableCallBack2 = 1;

	printf("***********************   AddViewList_2   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_2_List));
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_3_List));
	
	ptrDir2 = opendir(DBMS_Path_2);
	if (ptrDir2)
	{
		V2_Index_Cnt = 0;
		while ((dirlist2 = readdir(ptrDir2)) != NULL)
		{
			if((strcmp(dirlist2->d_name , ".") != 0) && (strcmp(dirlist2->d_name,"..") != 0))
			{
				View_2_Buffer[V2_Index_Cnt]=dirlist2->d_name;
				printf("Vox 2 Adding %s , %d \n", View_2_Buffer[V2_Index_Cnt],V2_Index);	                            
				V2_Index_Cnt++;
			}	
		}
	}
	
	if(V2_Index_Cnt == 0)
	{
		printf("\nSorry V2_Index_Cnt is %d\n",V2_Index_Cnt);
		ResetDisables();
		return;
	}		

	ptrDir2 = opendir(DBMS_Path_2);
	if (ptrDir2)
	{
		V2_Index_Cnt = 0;
		while ((dirlist2 = readdir(ptrDir2)) != NULL)
		{
			if((strcmp(dirlist2->d_name , ".") != 0) && (strcmp(dirlist2->d_name,"..") != 0))
			{
				View_2_Buffer[V2_Index_Cnt]=dirlist2->d_name;
				printf("Vox 2 Adding %s , %d \n", View_2_Buffer[V2_Index_Cnt],V2_Index);				
				if(V2_Index_Cnt == V2_Index)
				{
					memset(Path_2,0,10);
					strcat(Path_2,View_2_Buffer[V2_Index_Cnt]);
					printf("Path_2 %s \n",Path_2);
				}			
				gtk_combo_box_text_append_text((GtkComboBoxText *)(View_2_List), View_2_Buffer[V2_Index_Cnt]);                               
				V2_Index_Cnt++;
			}	
		}
		closedir(ptrDir2);
	}

	if(V2_Index_Cnt == 0)
	{
		printf("\nSorry V2_Index_Cnt is %d\n",V2_Index_Cnt);
		ResetDisables();
		return;
	}	

	if(Path_2[0] == NULL)
	{
		printf("List Path 2 is empty \n");
		ResetDisables();
		return;
	}		
	memset(DBMS_Path_3,0,30);
	strcat(DBMS_Path_3,DBMS_Path_2);
	strcat(DBMS_Path_3,"/");
	strcat(DBMS_Path_3,Path_2);
	printf("New Path for Box 3 %s \n",DBMS_Path_3);

	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(View_2_List),V2_Index);
	g_signal_connect( G_OBJECT( View_2_List ), "changed", G_CALLBACK( CallBackFrom_View_2 ), NULL );	

	AddViewList_3();	
}

void AddViewList_3(void)
{
	int i = 0;	
	
	DisableCallBack0 = 0;
	DisableCallBack1 = 0;
	DisableCallBack2 = 1;
	DisableCallBack3 = 1;
	
	printf("***********************   AddViewList_3   **********************\n");
	gtk_combo_box_text_remove_all( (GtkComboBoxText *)(View_3_List));
	ptrDir3 = opendir(DBMS_Path_3);
	printf("New Path for Box 3 %s \n",DBMS_Path_3);
	if (ptrDir3)
	{
		V3_Index_Cnt = 0;
		while ((dirlist3 = readdir(ptrDir3)) != NULL)
		{
			if((strcmp(dirlist3->d_name , ".") != 0) && (strcmp(dirlist3->d_name,"..") != 0))
			{
				View_3_Buffer[V3_Index_Cnt]=dirlist3->d_name;                          
				V3_Index_Cnt++;
			}	
		}
	}
	
	if(V3_Index_Cnt == 0)
	{
		printf("\nSorry V3_Index_Cnt is %d\n",V3_Index_Cnt);
		ResetDisables();
		return;
	}	

	ptrDir3 = opendir(DBMS_Path_3);
	if (ptrDir3)
	{
		V3_Index_Cnt = 0;
		V3_Index = 0;
		while ((dirlist3 = readdir(ptrDir3)) != NULL)
		{
			View_3_Buffer[V3_Index_Cnt]=dirlist3->d_name;
			if ( (strcmp(View_3_Buffer[V3_Index_Cnt] , ".") != 0) && (strcmp(View_3_Buffer[V3_Index_Cnt],"..") != 0) )
			{
				printf("Vox 3 Adding %s , %d \n", View_3_Buffer[V3_Index_Cnt],V3_Index);			
				if(V3_Index_Cnt == V3_Index)
				{
					memset(Path_3,0,10);
					strcat(Path_3,View_3_Buffer[V3_Index_Cnt]);
					printf("Path_3 %s \n",Path_3);
					memset(NewDirPath_3,0,30);
					strcpy(NewDirPath_3,DBMS_Path_3);
					strcat(NewDirPath_3,"/");
					strcat(NewDirPath_3,Path_3);
				}		
				gtk_combo_box_text_append_text((GtkComboBoxText *)(View_3_List), View_3_Buffer[V3_Index_Cnt]);
				V3_Index_Cnt++;
			}			
		}
		closedir(ptrDir3);
	}

	if(V3_Index_Cnt == 0)
	{
		printf("\nSorry V3_Index_Cnt is %d\n",V3_Index_Cnt);
		ResetDisables();
		return;
	}
	if(Path_3[0] == NULL)
	{
		printf("List Path 3 is empty \n");
		ResetDisables();
	}
		
	// Set default height
	gtk_combo_box_set_active((GtkComboBox *)(View_3_List),V3_Index);
	g_signal_connect( G_OBJECT( View_3_List ), "changed", G_CALLBACK( CallBackFrom_View_3), NULL );	
	DisableCallBack2 = 0;
	DisableCallBack3 = 0;
}

void GoToConfigAddScreen(void)
{
	if(SetWindowEn == 1)
	{
		SetWindowEn = 0;
		g_object_unref (SetBuilder);
		gtk_widget_hide(SettingWindow);
		gtk_widget_hide(SettingWindow);
	}
	else if(ConfAddWindowEn == 1)
	{
		ConfAddWindowEn = 0;
		g_object_unref (ConfAddBuilder);
		gtk_widget_hide(ConfAddWindow);
		gtk_widget_hide(ConfAddWindow);
	}
	
	vbox0En = 0;
	vbox1En	= 0;
	vbox2En	= 0;
	vbox3En	= 0;
	
	V0_Index = 0;
	V1_Index = 0;
	V2_Index = 0;
	V3_Index = 0;

	AddConfig_Vbox0En = 0;
	AddConfig_Vbox1En = 0;
	AddConfig_Vbox2En = 0;
	AddConfig_Vbox3En = 0;

	V0_Index_Cnt = 0;
	V1_Index_Cnt = 0;
	V2_Index_Cnt = 0;
	V3_Index_Cnt = 0;

	ConfAddWindow = CreateConfigAddScreen();
	gtk_widget_show_all(ConfAddWindow);
	ConfAddWindowEn = 1;	
}

void QuitConfigAddWindow(void)
{
	ConfAddWindowEn = 0;
	g_object_unref (ConfAddBuilder);
	gtk_widget_hide(ConfAddWindow);
	GoToMainScreen();
}


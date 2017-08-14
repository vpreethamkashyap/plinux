#include"include/main.h"

void GoToPopUPScreen(void);
void QuitPopWindow(void);

extern void Add0(void);
extern void Add1(void);
extern void Add2(void);
extern void Add3(void);
extern void GoToConfigScreen(void);
extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToMainScreen(void);
extern void GoToConfigAddScreen(void);

GtkWidget *label;

extern int AddConfig_Vbox0En;
extern int AddConfig_Vbox1En;
extern int AddConfig_Vbox2En;
extern int AddConfig_Vbox3En;
extern GtkBuilder *ConfBuilder, *PopBuilder, *PopBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*PopWindow;

extern char DBMS_Path_0[30];
extern char DBMS_Path_1[30];
extern char DBMS_Path_2[30];
extern char DBMS_Path_3[30];

extern char NewDirPath_0[30];
extern char NewDirPath_1[30];  
extern char NewDirPath_2[30];  
extern char NewDirPath_3[30]; 

/*****************************************************************************************************************
                         Main Code Starts Here 
******************************************************************************************************************/
void Add0(void)
{
	DIR  *ptrDir0,*ptrDir1,*ptrDir2,*ptrDir3;
	
	printf("Add0 DBMS_Path_0 %s \n",DBMS_Path_0);
	printf("NewDirPath_0 Path %s \n",NewDirPath_0);	
	ptrDir0 = opendir(DBMS_Path_0);
	mkdir(NewDirPath_0, 0777);
	closedir(ptrDir0);
}

void Add1(void)
{
	DIR  *ptrDir0,*ptrDir1,*ptrDir2,*ptrDir3;
	printf("Add1 DBMS_Path_0 %s \n",DBMS_Path_1);
	printf("NewDirPath_1 Path %s \n",NewDirPath_1);	
	ptrDir1 = opendir(DBMS_Path_1);
	mkdir(NewDirPath_1, 0777);
	closedir(ptrDir1);	
}

void Add2(void)
{
	DIR  *ptrDir0,*ptrDir1,*ptrDir2,*ptrDir3;
	printf("Add2 DBMS_Path_0 %s \n",DBMS_Path_2);
	printf("NewDirPath_2 Path %s \n",NewDirPath_2);		
	ptrDir2 = opendir(DBMS_Path_2);
	mkdir(NewDirPath_2, 0777);
	closedir(ptrDir2);		
}
void Add3(void)
{
	FILE *fp1,*fp2,*fp3;
	char FilePath[50];
	
	DIR  *ptrDir0,*ptrDir1,*ptrDir2,*ptrDir3,*ptrDir4;
	printf("Add3 DBMS_Path_3 %s \n",DBMS_Path_3);
	printf("NewDirPath_3 Path %s \n",NewDirPath_3);
	ptrDir3 = opendir(DBMS_Path_3);
	mkdir(NewDirPath_3, 0777);
	closedir(ptrDir3);
	
	memset(FilePath,0,50);
	strcat(FilePath,NewDirPath_3);
	strcat(FilePath,"/name.txt");		
	printf("Path 1 %s \n",FilePath);
	fp1 = fopen (FilePath, "w");
	if(fp1<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		printf(" System is able to create name.txt file \n");
	}
	close(fp1);
	
	memset(FilePath,0,50);
	strcat(FilePath,NewDirPath_3);
	strcat(FilePath,"/man.txt");		
	printf("Path 1 %s \n",FilePath);
	fp1 = fopen (FilePath, "w");
	if(fp1<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		printf(" System is able to create man.txt file \n");
	}
	close(fp2);
	
	memset(FilePath,0,50);
	strcat(FilePath,NewDirPath_3);
	strcat(FilePath,"/geo.txt");		
	printf("Path 1 %s \n",FilePath);
	fp1 = fopen (FilePath, "w");
	if(fp1<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		printf(" System is able to create geo.txt file \n");
	}
	close(fp3);
}

void GoToYesScreen(void)
{
	if(AddConfig_Vbox0En)
	{
		Add0();
	}
	if(AddConfig_Vbox1En)
	{
		Add1();
	}
	if(AddConfig_Vbox2En)
	{
		Add2();
	}
	if(AddConfig_Vbox3En)
	{
		Add3();
	}	
	g_object_unref (PopBuilder);
	gtk_widget_hide(PopWindow);
	GoToConfigAddScreen();
}
void GoToNoScreen(void)
{
	g_object_unref (PopBuilder);
	gtk_widget_hide(PopWindow);
	GoToConfigAddScreen();
}

static GtkWidget* CreatePopupScreen (void)
{
	
	GtkWidget *Button1,*Button2;
	GtkImage  *imageBG;

	GError* error = NULL;
	PopBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (PopBuilder, UI_FILE_5 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (PopBuilder, NULL);
	
	PopWindow = GTK_WIDGET (gtk_builder_get_object (PopBuilder, POPUP_WINDOW));
	if(!PopWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",POPUP_WINDOW,UI_FILE_2 );
	}
	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(popImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (PopBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	Button1 = GTK_WIDGET (gtk_builder_get_object (PopBuilder, "yes"));
	g_signal_connect (G_OBJECT (Button1), "clicked", G_CALLBACK (GoToYesScreen), NULL);
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (PopBuilder, "no"));
	g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToNoScreen), NULL);	

	g_object_unref (PopBuilder);	
	return PopWindow;
}

void GoToPopUPScreen(void)
{
	PopWindow = CreatePopupScreen();
	gtk_widget_show (PopWindow);
}




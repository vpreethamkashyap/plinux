#include"include/main.h"

void GoToPopUPDelScreen(void);

void Del0(void);
void Del1(void);
void Del2(void);
void Del3(void);

GtkWidget *Button1,*Button2;
GtkImage  *imageBG;


extern volatile int DelConfig_Vbox0En;
extern volatile int DelConfig_Vbox1En;
extern volatile int DelConfig_Vbox2En;
extern volatile int DelConfig_Vbox3En;
extern GtkBuilder *ConfBuilder, *DelPopBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*DelPopWindow;

extern volatile char Del_DBMS_Path_0[50];
extern volatile char Del_DBMS_Path_1[50];
extern volatile char Del_DBMS_Path_2[50];
extern volatile char Del_DBMS_Path_3[50];
extern volatile char Del_DBMS_Path_4[50];

extern volatile char Del_NewDirPath_0[50];
extern volatile char Del_NewDirPath_1[50];  
extern volatile char Del_NewDirPath_2[50];  
extern volatile char Del_NewDirPath_3[50]; 


/*****************************************************************************************************************
                         Main Code Starts Here 
******************************************************************************************************************/
void Del0(void)
{
	char path[50];
	
	printf("Going delete from box 0\n");
	printf("Del_NewDirPath_0 Path %s \n",Del_NewDirPath_0);	
	memset(path,0,50);
	strcat(path,"./del.sh ");
	strcat(path,Del_NewDirPath_0);
	system(path);
	printf("Delted \n");	
}

void Del1(void)
{
	char path[50];
	
	printf("Going delete from box 1\n");
	printf("Del_NewDirPath_1 Path %s \n",Del_NewDirPath_1);	
	memset(path,0,50);
	strcat(path,"./del.sh ");
	strcat(path,Del_NewDirPath_1);
	system(path);
	printf("Delted \n");
}

void Del2(void)
{
	char path[50];
	
	printf("Going delete from box 2\n");
	printf("Del_NewDirPath_2 Path %s \n",Del_NewDirPath_2);	
	memset(path,0,50);
	strcat(path,"./del.sh ");
	strcat(path,Del_NewDirPath_2);
	system(path);
	printf("Delted \n");
}
void Del3(void)
{
	char path[50];
	
	printf("Going delete from box 3\n");
	printf("Del_NewDirPath_3 Path %s \n",Del_NewDirPath_3);	
	memset(path,0,50);
	strcat(path,"./del.sh ");
	strcat(path,Del_NewDirPath_3);
	system(path);
	printf("Delted \n");
}

void GoToDelYesScreen(void)
{
	if(DelConfig_Vbox0En)
	{
		DelConfig_Vbox0En = 0;
		Del0();
	}
	else if(DelConfig_Vbox1En)
	{
		DelConfig_Vbox1En = 0;
		Del1();
	}
	else if(DelConfig_Vbox2En)
	{
		DelConfig_Vbox2En = 0;
		Del2();
	}
	else if(DelConfig_Vbox3En)
	{
		DelConfig_Vbox3En = 0;
		Del3();
	}	

	g_object_unref (DelPopBuilder);
	gtk_widget_hide(DelPopWindow);
	GoToConfigDeleteScreen();
}
void GoToDelNoScreen(void)
{
	g_object_unref (DelPopBuilder);
	gtk_widget_hide(DelPopWindow);
	GoToConfigDeleteScreen();
}

static GtkWidget* CreateDelPopupScreen (void)
{	
	GError* error = NULL;
	DelPopBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (DelPopBuilder, UI_FILE_6 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (DelPopBuilder, NULL);
	
	DelPopWindow = GTK_WIDGET (gtk_builder_get_object (DelPopBuilder, DEL_POPUP_WINDOW));
	if(!DelPopWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",DEL_POPUP_WINDOW,UI_FILE_6 );
	}
	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(popImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (DelPopBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	Button1 = GTK_WIDGET (gtk_builder_get_object (DelPopBuilder, "yes"));
	g_signal_connect (G_OBJECT (Button1), "clicked", G_CALLBACK (GoToDelYesScreen), NULL);
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (DelPopBuilder, "no"));
	g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToDelNoScreen), NULL);	

	g_object_unref (DelPopBuilder);	
	return DelPopWindow;
}

void GoToPopUPDelScreen(void)
{
	DelPopWindow = CreateDelPopupScreen();
	gtk_widget_show (DelPopWindow);
}




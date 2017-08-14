#include"include/main.h"

/*****************************************************************************************************************
                                       Variable Declaration
******************************************************************************************************************/


GtkWidget *entry0,*entry1,*entry2,*entry3,*entry4,*entry5;
GtkWidget *AddBtn0,*AddBtn1,*AddBtn2,*AddBtn3,*AddBtn4,*AddBtn5;
GtkWidget *Button1,*Button2,*Button3,*Button4,*Button5;
GtkImage  *imageBG;	
char FilePath[50];
extern char NewDirPath_0[30];
extern char NewDirPath_1[30];  
extern char NewDirPath_2[30];  
extern char NewDirPath_3[30]; 

void AddDetail_InFile0(void);
void AddDetail_InFile1(void);
void AddDetail_InFile2(void);
void QuitAddDetailWindow(void);
extern void GoToMainScreen(void);
extern GtkBuilder *ConfBuilder,*ConfAddBuilder,*ConfDeleteBuilder, *SetBuilder, *PopBuilder,*BpBuilder,*DelPopBuilder,*AddDetailBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*ConfAddWindow,*ConfDeleteWindow,*SettingWindow,*PopWindow,*DelPopWindow,*AddDetailWindow;
/*****************************************************************************************************************
                                       Main Code Starts Here 
******************************************************************************************************************/

void AddDetail_InFile0(void)
{
	FILE *fp1,*fp2,*fp3;
	char *Buffer;
	char Buf0[10];

	Buffer = gtk_entry_get_text(entry0);	
	strcpy(Buf0,Buffer);
	
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
		fwrite(&Buf0,sizeof(Buf0),1,fp1);
		printf("Name %s\n",Buf0);
	}
	fclose(fp1);	
}

void AddDetail_InFile1(void)
{
	FILE *fp1;
	char *Buffer;
	char Buf0[10];

	Buffer = gtk_entry_get_text(entry1);	
	strcpy(Buf0,Buffer);
	
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
		fwrite(&Buf0,sizeof(Buf0),1,fp1);
		printf("man %s\n",Buf0);
	}
	fclose(fp1);
}

void AddDetail_InFile2(void)
{
	FILE *fp1;
	char *Buffer;
	char Buf0[10];

	Buffer = gtk_entry_get_text(entry2);	
	strcpy(Buf0,Buffer);
	
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
		fwrite(&Buf0,sizeof(Buf0),1,fp1);			
		printf("Geo %s\n",Buf0);
	}
	fclose(fp1);
}

void ReadEntry(void)
{
	FILE *fp1,*fp2,*fp3;
	unsigned char Buf0[15],Buf1[15],Buf2[15];
	
	memset(FilePath,0,50);
	printf("NewDirPath_3 %s \n",NewDirPath_3);
	strcpy(FilePath,NewDirPath_3);
	strcat(FilePath,"/name.txt");		
	printf("Path 1 %s \n",FilePath);
	
	fp1 = fopen (FilePath, "r");
	
	if(fp1<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf0,10,1,fp1);
		printf("Name %s\n",Buf0);
		gtk_entry_set_text(entry0,Buf0);
	}
	fclose(fp1);	
			
	memset(FilePath,0,50);
	strcat(FilePath,NewDirPath_3);
	strcat(FilePath,"/man.txt");		
	printf("Path 1 %s \n",FilePath);
	fp2 = fopen (FilePath, "r");
	if(fp2<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf1,10,1,fp2);
		printf("Manufacture %s\n",Buf1);
		gtk_entry_set_text(entry1,Buf1);
	}
	fclose(fp2);	
		
	memset(FilePath,0,50);
	strcat(FilePath,NewDirPath_3);
	strcat(FilePath,"/geo.txt");		
	printf("Path 1 %s \n",FilePath);
	fp3 = fopen (FilePath, "r");
	if(fp3<0)
	{
		printf(" System is not able to create file \n");
	}
	else
	{
		fread(&Buf2,10,1,fp3);			
		printf("Geo Location %s\n",Buf2);
		gtk_entry_set_text(entry2,Buf2);
	}		
	fclose(fp3);
}

static GtkWidget* CreateAddDetailsScreen (void)
{
	GError *error = NULL;	

	AddDetailBuilder = gtk_builder_new ();	
	if (!gtk_builder_add_from_file (AddDetailBuilder, UI_FILE_7 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (AddDetailBuilder, NULL);
	
	AddDetailWindow = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, CONFIG_ADD_DETAIL_WINDOW));
	if(!AddDetailWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",CONFIG_WINDOW,UI_FILE_7 );
	}

	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);
	
	Button5 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "back"));
	g_signal_connect (G_OBJECT (Button5), "clicked", G_CALLBACK (QuitAddDetailWindow), NULL);	

	AddBtn0 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "add0"));
	g_signal_connect (G_OBJECT (AddBtn0), "clicked", G_CALLBACK (AddDetail_InFile0), NULL);	
	
	AddBtn1 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "add1"));
	g_signal_connect (G_OBJECT (AddBtn1), "clicked", G_CALLBACK (AddDetail_InFile1), NULL);	

	AddBtn2 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "add2"));
	g_signal_connect (G_OBJECT (AddBtn2), "clicked", G_CALLBACK (AddDetail_InFile2), NULL);	
	
	entry0 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "entry0"));
	entry1 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "entry1"));
	entry2 = GTK_WIDGET (gtk_builder_get_object (AddDetailBuilder, "entry2"));
	ReadEntry();
	return AddDetailWindow;
}

void GoToDetailScreen(void)
{
	gtk_widget_hide(ConfAddWindow);
	AddDetailWindow = CreateAddDetailsScreen();
	gtk_widget_show (AddDetailWindow);
}

void QuitAddDetailWindow(void)
{
	g_object_unref (AddDetailBuilder);
	gtk_widget_hide(AddDetailWindow);
	GoToMainScreen();
}









#if 0
void StartBmiTest( GtkWidget *widget, gpointer data ){
	FILE *fp;
	printf("ip is ready \n");
	fp = fopen (IN_TEXT_FILE, "w");
	if(fp<0){
		printf(" System is not able to create file \n");
	}
	else{
		printf("ip is ready \n");
		ClearOutPutFile();
		WriteEntryFile();
		strcpy(InText.InBuf,"WeTest");
		fwrite(&InText,sizeof(InText),1,fp);
		printf(" File has been Updated \n");
		fclose(fp);			
	}
    TimerInit();
	return;
} 

void ClearOutPutFile(void){
	FILE *fp;
	fp = fopen (OT_ENTERY_FILE, "w");
	fclose(fp);
	fp = fopen (OT_TEXT_FILE, "w");
	fclose(fp);	
}
void WriteEntryFile(void){
	FILE *fp;
	char *HightBuffer;

	HightBuffer = gtk_entry_get_text(entry1);	
	strcpy(Din.Weight,"123");
	strcpy(Din.Hight,HightBuffer);
	Din.Comma = ',';

	fp = fopen (IN_ENTERY_FILE, "w");
	if(fp<0){
		printf(" System is not able to open file \n");
	}
	else{
		fwrite(&Din,sizeof(Din),1,fp);
		fclose(fp);
		printf(" System has updated the Hight Buf file %s \n",Din.Hight);
		BMITestEn=1;
	}
}


void GetBmiOutput(void){

	FILE *fp;
	char Buf[2];
   
	if(BMITestEn==1){
		fp = fopen (OT_TEXT_FILE, "r+");
		if(fp<0){
			printf(" System is not able to create file \n");
		}
		else{
			fread(&Buf,1,1,fp);
			fclose(fp);	
			if(Buf[0] == '1'){
				printf(" String info %d \n",Buf[0]);
				printf("System Got Data Updated \n");
				fp = fopen (OT_ENTERY_FILE, "r");
				fread(&Bmi,sizeof(Bmi),1,fp);
				fclose(fp);
				printf("Bmi Value is %s\n",Bmi.Weight);
				printf("Bmi Value is %s\n",Bmi.BmiValue);
				gtk_entry_set_text(entry2,&Bmi.Weight);
				gtk_entry_set_text(entry3,&Bmi.BmiValue);
				BMITestEn=0;
				ClearOutPutFile();
			}			
		}
	}
}

#endif


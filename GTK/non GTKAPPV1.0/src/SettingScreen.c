#include"include/main.h"

void GoToSettingScreen(void);
void QuitSettingWindow(void);
extern void GoToConfigScreen(void);
extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToMainScreen(void);

/*****************************************************************************************************************
                                                        Variable Declaration
 * http://stackoverflow.com/questions/8352027/gtk-timer-how-to-make-a-timer-within-a-frame
******************************************************************************************************************/


GtkWidget *label;

extern int MainWindowEn,SetWindowEn,ConfWindowEn;
extern GtkBuilder *ConfBuilder, *SetBuilder, *BpBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*SettingWindow;


/*****************************************************************************************************************
                                                                Main Code Starts Here 
******************************************************************************************************************/

static GtkWidget* CreateSettingScreen (void)
{
	
	GtkWidget *Button1,*Button2,*Button3,*Button4;
	GtkImage  *imageBG;

	GError* error = NULL;
	SetBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (SetBuilder, UI_FILE_1 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (SetBuilder, NULL);
	
	SettingWindow = GTK_WIDGET (gtk_builder_get_object (SetBuilder, SETTING_WINDOW));
	if(!SettingWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",SETTING_WINDOW,UI_FILE_1 );
	}
	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (SetBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	Button1 = GTK_WIDGET (gtk_builder_get_object (SetBuilder, "setting"));
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (SetBuilder, "config"));
	g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToConfigScreen), NULL);	

	Button3 = GTK_WIDGET (gtk_builder_get_object (SetBuilder, "mode"));
	//g_signal_connect (G_OBJECT (Button3), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button3 = GTK_WIDGET (gtk_builder_get_object (SetBuilder, "help"));
	//g_signal_connect (G_OBJECT (Button4), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button4 = GTK_WIDGET (gtk_builder_get_object (SetBuilder, "back"));
	g_signal_connect (G_OBJECT (Button4), "clicked", G_CALLBACK (QuitSettingWindow), NULL);	
	
	g_object_unref (SetBuilder);	
	return SettingWindow;
}

void GoToSettingScreen(void)
{
	if(SetWindowEn == 1)
	{
		SetWindowEn = 0;
		g_object_unref (SetBuilder);
		gtk_widget_hide(SettingWindow);
		gtk_widget_hide(SettingWindow);
	}
	else if(ConfWindowEn == 1)
	{
		ConfWindowEn = 0;
		g_object_unref (ConfBuilder);
		gtk_widget_hide(ConfWindow);
		gtk_widget_hide(ConfWindow);
	}
	
	SetWindowEn = 1;
	gtk_widget_hide(MainWindow);
	SettingWindow = CreateSettingScreen();
	gtk_widget_show (SettingWindow);
}

void QuitSettingWindow(void)
{
	SetWindowEn = 0;
	g_object_unref (SetBuilder);
	gtk_widget_hide(SettingWindow);
	GoToMainScreen();
}



#include"include/main.h"
#include <string.h>
#include <stdlib.h>

void GoToConfigScreen(void);
void QuitConfigWindow(void);

extern void GoToModeScreen(void);
extern void GoToHelpScreen(void);
extern void GoToMainScreen(void);
extern void GoToSettingScreen(void);
extern void GoToConfigAddScreen(void);
extern void GoToConfigDeleteScreen(void);

/*****************************************************************************************************************
                              Variable Declaration
******************************************************************************************************************/

extern int MainWindowEn,SetWindowEn,ConfWindowEn;
extern GtkBuilder *ConfBuilder, *SetBuilder, *BpBuilder;
extern GtkWidget *MainWindow,*Bliwindow,*ConfWindow,*SettingWindow;

char ht_str[75][6];
static GtkComboBoxText *height_list;
/*****************************************************************************************************************
                             Main Code Starts Here 
******************************************************************************************************************/
static void cb_changed( GtkComboBox *combo, gpointer     data )
{
	int i = 0;
	
	gchar *string = gtk_combo_box_text_get_active_text( height_list );
	gtk_combo_box_set_active_id(height_list, string);
	g_print( "Selected (simple): >> %s <<\n", ( string ? string : "NULL" ) );
	g_free( string );
}

static GtkWidget* CreateConfigScreen (void)
{	
	GtkWidget *Button1,*Button2,*Button3,*Button4,*Button5,*Button6,*Button7;
	GtkImage  *imageBG;
	GtkWidget *vbox;
	
	GError *error = NULL;	
	ConfBuilder = gtk_builder_new ();
	
	if (!gtk_builder_add_from_file (ConfBuilder, UI_FILE_2 , &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}
	gtk_builder_connect_signals (ConfBuilder, NULL);
	
	ConfWindow = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, CONFIG_WINDOW));
	if(!ConfWindow)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",CONFIG_WINDOW,UI_FILE_2 );
	}
	
	GdkPixbufAnimation * pixbufBGanm = gdk_pixbuf_animation_new_from_file(BkGndImage, error);
	imageBG = (GtkImage *) GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "image1"));
	gtk_image_set_from_animation(GTK_IMAGE(imageBG), pixbufBGanm);

	Button1 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "setting"));
	g_signal_connect (G_OBJECT (Button1), "clicked", G_CALLBACK (GoToSettingScreen), NULL);	
	
	Button2 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "config"));
	//g_signal_connect (G_OBJECT (Button2), "clicked", G_CALLBACK (GoToBpScreen), NULL);	

	Button3 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "mode"));
	//g_signal_connect (G_OBJECT (Button3), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button4 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "help"));
	//g_signal_connect (G_OBJECT (Button4), "clicked", G_CALLBACK (GoToBliScreen), NULL);	
	
	Button5 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "back"));
	g_signal_connect (G_OBJECT (Button5), "clicked", G_CALLBACK (QuitConfigWindow), NULL);	
	
	Button6 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "add"));
	g_signal_connect (G_OBJECT (Button6), "clicked", G_CALLBACK (GoToConfigAddScreen), NULL);	
	
	Button7 = GTK_WIDGET (gtk_builder_get_object (ConfBuilder, "delete"));
	g_signal_connect (G_OBJECT (Button7), "clicked", G_CALLBACK (GoToConfigDeleteScreen), NULL);	

	g_object_unref (ConfBuilder);	
	return ConfWindow;
}



void GoToConfigScreen(void)
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
	
	ConfWindowEn = 1;
	
	ConfWindow = CreateConfigScreen();
	gtk_widget_show_all(ConfWindow);
	//gtk_widget_show (ConfWindow);
}

void QuitConfigWindow(void)
{
	ConfWindowEn = 0;
	g_object_unref (ConfBuilder);
	gtk_widget_hide(ConfWindow);
	GoToMainScreen();
}



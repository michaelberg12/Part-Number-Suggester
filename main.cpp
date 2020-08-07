#include <cairo.h>
#include <gtk/gtk.h>
#include "UI_Handleing.h"
#include "File_interfacer.h"
#include "FileData.h"
#include "BasicId.h"

#include <iostream>

#include <Windows.h>
#include <string>


int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	File_Interfacer gen();

	ConfigWindow _location_config(true);
	ConfigWindow _type_config(false);


	GtkWidget* _dir_config_window = _location_config.window();
	GtkWidget* _file_config_window = _type_config.window();

	MainWindow _file_list(_dir_config_window, _file_config_window);
	GtkWidget* _main_window = _file_list.window();

	srand(time(0));

	gtk_widget_show_all(_main_window);

	gtk_main();
    return 0;
}

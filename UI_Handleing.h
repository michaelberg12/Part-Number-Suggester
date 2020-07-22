#pragma once
#include <gtk/gtk.h>
#include <cairo.h>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Part.h"

class UI_Handleing
{
public:
	UI_Handleing(int argc, char* argv[]);
private:

	static GtkWidget* _part_window;
	static GtkWidget* _main_window;

	void _window_creation();
	void _new_part_window();
	void _new_main_window();

	void _part_legend(GtkWidget* legend_box);
	void _new_part_creation_menu(GtkWidget* grid);
	void _new_main_menu(GtkWidget* grid);

	static void _part_number_confirm(GtkButton* button, gpointer user_data);
};

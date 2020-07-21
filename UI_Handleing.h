#pragma once
#include <gtk/gtk.h>
#include <cairo.h>

#define _USE_MATH_DEFINES
#include <cmath>

class UI_Handleing
{
public:
	UI_Handleing(int argc, char* argv[]);
private:

	static GtkWidget* _part_window;

	void _window_creation();
	void _new_part_window();
	void _option_menu_creation(GtkWidget* grid);

	static void _part_number_confirm(GtkButton* button, gpointer user_data);
};

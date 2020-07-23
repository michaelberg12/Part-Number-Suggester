#pragma once
#include <gtk/gtk.h>
#include <cairo.h>
#include <iostream>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Part.h"

class UI_Handleing
{
public:
	UI_Handleing(int argc, char* argv[]);
private:
	static GList* list;
	static GtkTreeStore* store;
	static std::vector<Part> selected_part_list;
	static bool _selection_disable_flag;

	static GtkTreeSelection* select;

	static GtkWidget* _part_window;
	static GtkWidget* _main_window;

	void _window_creation();
	void _new_main_window();

	static void _new_part_creation_menu(GtkWidget* grid);
	void _new_main_menu(GtkWidget* grid);

	static void _part_number_confirm(GtkButton* button, gpointer user_data);
	static void _selection_changed(GtkTreeSelection* selection, gpointer data);
	static void _generate_new_part_number(GtkButton* button, gpointer user_data);

	static void _new_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _delete_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _config_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _new_part_window();
};

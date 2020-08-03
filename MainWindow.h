#pragma once
#pragma once
#include <gtk/gtk.h>
#include <cairo.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h> 
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Part.h"
#include "File_interfacer.h"
#include "ConfigWindow.h"

class MainWindow
{
public:
	MainWindow();
private:
	GList* _list;
	GtkTreeStore* _store_parts;
	GtkTreeSelection* _select;
	std::vector<Part> _selected_part_list;

	bool _selection_disable_flag;
	GtkWidget* _main_window;

	GtkWidget* _part_name_input;
	GtkWidget* _part_desc_input;

	Part _new_part = Part("", "", "", "");

	void _window_creation();
	void _new_main_window();

	void _new_main_menu(GtkWidget* grid);
	static std::vector<Part> _parse_files(std::vector<WIN32_FIND_DATA> files_data);

	static void _selection_changed_main(GtkTreeSelection* selection, gpointer user_data);
	static void _new_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _delete_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _config_menu_loc(GtkMenuItem* menuitem, gpointer user_data);
	static void _config_menu_type(GtkMenuItem* menuitem, gpointer user_data);
	static void cell_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data);
	static bool _verify_file_name(std::string file_name, gpointer user_data);
	static void _add_files(std::vector<Part> part_list, gpointer user_data);
};


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

class UI_Handleing
{
public:
	UI_Handleing(int argc, char* argv[]);
private:

	static GList* _list;

	static GtkTreeStore* _store_parts;

	static std::vector<Part> _selected_part_list;
	static bool _selection_disable_flag;

	static GtkTreeSelection* _select;

	static GtkWidget* _part_window;
	static GtkWidget* _main_window;
	static GtkWidget* _file_config_window;
	static GtkWidget* _dir_config_window;

	//remove these as soon as possible
	//use the buffer to remove them
	static GtkWidget* _part_name_input;
	static GtkWidget* _part_desc_input;

	static Part _new_part;

	void _window_creation();
	void _new_main_window();

	static void _new_part_creation_menu(GtkWidget* grid);
	void _new_main_menu(GtkWidget* grid);

	static void _part_number_confirm(GtkButton* button, gpointer user_data);
	static void _selection_changed_main(GtkTreeSelection* selection, gpointer data);
	static void _generate_new_part_number(GtkButton* button, gpointer user_data);

	static std::vector<Part> _parse_files(std::vector<WIN32_FIND_DATA> files_data);
	static void _new_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _delete_menu_item(GtkMenuItem* menuitem, gpointer user_data);
	static void _config_menu_loc(GtkMenuItem* menuitem, gpointer user_data);
	static void _config_menu_type(GtkMenuItem* menuitem, gpointer user_data);
	static void cell_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data);
	static bool _verify_file_name(std::string file_name);
	static void _add_files(std::vector<Part> part_list);

	static void _new_part_window();
};

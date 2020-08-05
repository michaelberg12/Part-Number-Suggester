#pragma once

#include <gtk/gtk.h>
#include <cairo.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h> 
#include <windows.h>      // For common windows data types and function headers

#define _USE_MATH_DEFINES
#include <cmath>
#include "FileData.h"
#include "File_interfacer.h"
#include "Enums.h"

class ConfigWindow
{
public:
	ConfigWindow(bool file_location);
	GtkWidget* window();
private:

	bool _file_location;
	bool _selection_disable_flag;

	std::vector<GtkTreeRowReference*> _row_refs;

	GtkWidget* _config_window;
	GtkWidget* config_list;

	GList* _list;
	GtkTreeStore* _store;
	GtkTreeSelection* _select;
	GtkTreeViewColumn* _column;

	void _new_config_window();

	static void cell_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data);
	static void _selection_changed_config(GtkTreeSelection* selection, gpointer data);
	static void _add_clicked(GtkButton* button, gpointer user_data);
	static void _add_clicked_path(GtkButton* button, gpointer user_data);
	static void _remove_clicked(GtkButton* button, gpointer user_data);
	static void _close_window(GtkButton* button, gpointer user_data);
	static void _update_save_del(GtkTreeModel* tree_model, GtkTreePath* path, gpointer user_data);
	static void _update_save(GtkTreeModel* tree_model, GtkTreePath* path, GtkTreeIter* iter, gpointer user_data);
	static gboolean _delete_window(GtkWidget* widget, GdkEvent* event, gpointer data);
	static gboolean _to_string_vector(GtkTreeModel* model, GtkTreePath* path, GtkTreeIter* iter, gpointer data);
};


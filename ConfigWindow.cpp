#include "ConfigWindow.h"

GtkWidget* ConfigWindow::_config_window;
GtkWidget* ConfigWindow::config_list;

GtkTreeSelection* ConfigWindow::_select;

GList* ConfigWindow::_list;
GtkTreeStore* ConfigWindow::_store;

bool ConfigWindow::_selection_disable_flag = false;

std::vector<GtkTreeRowReference*> _row_refs;

ConfigWindow::ConfigWindow(std::string name)
{
	_config_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	_new_config_window();
}

GtkWidget* ConfigWindow::window()
{
	return _config_window;
}

void ConfigWindow::_new_config_window()
{
	GtkWidget* main_window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(_config_window), main_window_box);

	GtkWidget* add_row = gtk_button_new_with_label("+");
	GtkWidget* delete_row = gtk_button_new_with_label("-");
	GtkWidget* add_del_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_end(GTK_BOX(add_del_box), add_row, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(add_del_box), delete_row, FALSE, FALSE, 0);

	
	g_signal_connect(G_OBJECT(delete_row), "clicked", G_CALLBACK(_remove_clicked), NULL);

	GtkWidget* scrollable_list = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(main_window_box), scrollable_list, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_window_box), add_del_box, FALSE, TRUE, 0);

	config_list = gtk_tree_view_new();
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(config_list), GTK_TREE_VIEW_GRID_LINES_BOTH);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(config_list), FALSE);
	_select = gtk_tree_view_get_selection(GTK_TREE_VIEW(config_list));
	gtk_tree_selection_set_mode(_select, GTK_SELECTION_MULTIPLE);
	g_signal_connect(G_OBJECT(_select), "changed", G_CALLBACK(_selection_changed_config), NULL);
	gtk_container_add(GTK_CONTAINER(scrollable_list), config_list);

	g_signal_connect(_config_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GtkCellRenderer* rend_edit = gtk_cell_renderer_text_new();
	g_object_set(rend_edit, "editable", TRUE, NULL);

	g_signal_connect(G_OBJECT(rend_edit), "edited", G_CALLBACK(cell_edited_callback), NULL);

	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes("Name", rend_edit, "text", NAME_CON, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(config_list), column);

	g_signal_connect(G_OBJECT(add_row), "clicked", G_CALLBACK(_add_clicked_path), column);


	_store = gtk_tree_store_new(N_COLUMNS_CON, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(config_list), GTK_TREE_MODEL(_store));
	g_object_unref(_store);

	GtkTreeIter iter;

	//============================= part number ui elements ===================================
	for (int a1 = 0; a1 < 40; a1++) {
		std::string part_number;
		for (int a2 = 0; a2 < 20; a2++) {
			part_number.append(std::to_string(rand() % 8 + 1));
		}
		part_number.insert(2, std::string(1, (char)(rand() % 26 + 65)));

		gtk_tree_store_append(_store, &iter, NULL);
		gtk_tree_store_set(_store, &iter, NAME, part_number.c_str(), -1);
	}
	//=========================================================================================

	gtk_window_set_position(GTK_WINDOW(_config_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_config_window), 400, 400);
	gtk_window_set_resizable(GTK_WINDOW(_config_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_config_window), "Config");
}


void ConfigWindow::cell_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(_store), &iter_rawModel, path_string);
	gtk_tree_store_set(_store, &iter_rawModel, NAME_CON, new_text, -1);
}

void ConfigWindow::_selection_changed_config(GtkTreeSelection* selection, gpointer data)
{
	if (!_selection_disable_flag) {
		GtkTreeIter iter;
		_row_refs.clear();
		g_list_free_full(_list, (GDestroyNotify)gtk_tree_path_free);
		_list = gtk_tree_selection_get_selected_rows(selection, NULL);
		printf("Selected: %d Elements\n", g_list_length(_list));
		for (GList* a1 = _list; a1 != NULL; a1 = a1->next)
		{
			GtkTreePath* indv_row = (GtkTreePath*)(a1->data);
			gtk_tree_model_get_iter(GTK_TREE_MODEL(_store), &iter, indv_row);
			gchar* part_name;
			gtk_tree_model_get(GTK_TREE_MODEL(_store), &iter, NAME_CON, &part_name, -1);
			g_print("%s\n", part_name);
			_row_refs.push_back(gtk_tree_row_reference_new(GTK_TREE_MODEL(_store), indv_row));
		}
	}
}

void ConfigWindow::_add_clicked(GtkButton* button, gpointer user_data)
{
	GtkTreeViewColumn* column = (GtkTreeViewColumn*)user_data;
	GtkTreeIter iter;
	gtk_tree_store_append(_store, &iter, NULL);
	gtk_tree_store_set(_store, &iter, NAME, "", -1);

	gtk_tree_view_set_cursor_on_cell(GTK_TREE_VIEW(config_list), gtk_tree_model_get_path(GTK_TREE_MODEL(_store), &iter), column, NULL, TRUE);
}

void ConfigWindow::_add_clicked_path(GtkButton* button, gpointer user_data)
{
	GtkTreeViewColumn* column = (GtkTreeViewColumn*)user_data;
	GtkTreeIter iter;
	gtk_tree_store_append(_store, &iter, NULL);

	GtkFileChooserNative* native = gtk_file_chooser_native_new("Open File", GTK_WINDOW(_config_window), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "_Open", "_Cancel");

	int res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char* filename;
		GtkFileChooser* chooser = GTK_FILE_CHOOSER(native);
		filename = gtk_file_chooser_get_filename(chooser);
		g_print("%s\n", filename);
		gtk_tree_store_set(_store, &iter, NAME, filename, -1);
		gtk_tree_view_set_cursor_on_cell(GTK_TREE_VIEW(config_list), gtk_tree_model_get_path(GTK_TREE_MODEL(_store), &iter), column, NULL, FALSE);
		g_free(filename);
	}

	g_object_unref(native);
}

void ConfigWindow::_remove_clicked(GtkButton* button, gpointer user_data)
{
	_selection_disable_flag = true;
	g_print("Delete signal triggered\n\n");
	for (auto indv_rows : _row_refs) {
		GtkTreeIter iter;
		GtkTreePath* indv_row = gtk_tree_row_reference_get_path(indv_rows);
		gtk_tree_model_get_iter(GTK_TREE_MODEL(_store), &iter, indv_row);
		gtk_tree_store_remove(_store, &iter);
	}
	_selection_disable_flag = false;
	gtk_tree_selection_set_mode(_select, GTK_SELECTION_NONE);
	gtk_tree_selection_set_mode(_select, GTK_SELECTION_MULTIPLE);
}



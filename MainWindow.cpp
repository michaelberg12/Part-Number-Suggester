#include "MainWindow.h"
#include "UI_Handleing.h"

MainWindow::MainWindow(GtkWidget* file_type, GtkWidget* file_loc)
{
	_type_config_window = file_type;
	_loc_config_window = file_loc;

	_window_creation();
	_new_main_window();
	_new_confirm_window();
}

GtkWidget* MainWindow::window()
{
	return _main_window;
}

void MainWindow::_window_creation()
{
	_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	_confirm_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void MainWindow::_new_main_window()
{
	GtkWidget* main_window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(_main_window), main_window_box);

	GtkWidget* scrollable_list = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget* menu_bar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(main_window_box), menu_bar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_window_box), scrollable_list, TRUE, TRUE, 0);

	GtkWidget* new_part = gtk_menu_item_new_with_label("New");
	GtkWidget* delete_part = gtk_menu_item_new_with_label("Delete");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), new_part);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), delete_part);

	GtkWidget* configure_menu = gtk_menu_new();
	GtkWidget* configure_menu_label = gtk_menu_item_new_with_label("Config");
	GtkWidget* config_loc = gtk_menu_item_new_with_label("File Locations");
	GtkWidget* config_types = gtk_menu_item_new_with_label("File Types");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(configure_menu_label), configure_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(configure_menu), config_types);
	gtk_menu_shell_append(GTK_MENU_SHELL(configure_menu), config_loc);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), configure_menu_label);

	g_signal_connect(G_OBJECT(new_part), "activate", G_CALLBACK(_new_menu_item), _store_parts);
	g_signal_connect(G_OBJECT(delete_part), "activate", G_CALLBACK(_delete_clicked), this);
	g_signal_connect(G_OBJECT(config_loc), "activate", G_CALLBACK(_config_menu_loc), _loc_config_window);
	g_signal_connect(G_OBJECT(config_types), "activate", G_CALLBACK(_config_menu_type), _type_config_window);

	GtkWidget* part_list = gtk_tree_view_new();
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(part_list), GTK_TREE_VIEW_GRID_LINES_BOTH);
	_select = gtk_tree_view_get_selection(GTK_TREE_VIEW(part_list));
	gtk_tree_selection_set_mode(_select, GTK_SELECTION_MULTIPLE);
	g_signal_connect(G_OBJECT(_select), "changed", G_CALLBACK(_selection_changed_main), this);
	gtk_container_add(GTK_CONTAINER(scrollable_list), part_list);

	g_signal_connect(_main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_transient_for(GTK_WINDOW(_type_config_window), GTK_WINDOW(_main_window));
	gtk_window_set_transient_for(GTK_WINDOW(_loc_config_window), GTK_WINDOW(_main_window));

	_new_main_menu(part_list);

	gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_main_window), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(_main_window), TRUE);
	gtk_window_set_title(GTK_WINDOW(_main_window), "Part Number Manager");
}

void MainWindow::_new_confirm_window() {
	GtkWidget* main_window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(_confirm_window), main_window_box);

	GtkWidget* confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* confirm_delete = gtk_button_new_with_label("Delete");
	GtkWidget* cancel_delete = gtk_button_new_with_label("Cancel");
	gtk_box_pack_start(GTK_BOX(confirm_box), cancel_delete, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(confirm_box), confirm_delete, TRUE, FALSE, 20);
	gtk_box_pack_end(GTK_BOX(main_window_box), confirm_box, FALSE, FALSE, 10);
	g_signal_connect(G_OBJECT(cancel_delete), "clicked", G_CALLBACK(_delete_cancel), _confirm_window);
	g_signal_connect(G_OBJECT(confirm_delete), "clicked", G_CALLBACK(_delete_menu_item), this);

	g_signal_connect(_confirm_window, "destroy", G_CALLBACK(_delete_cancel), _confirm_window);

	GtkWidget* part_number_label = gtk_label_new("Confirm Delete?");
	gtk_box_pack_start(GTK_BOX(main_window_box), part_number_label, TRUE, TRUE, 10);

	gtk_window_set_position(GTK_WINDOW(_confirm_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_confirm_window), 200, 100);
	gtk_window_set_resizable(GTK_WINDOW(_confirm_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_confirm_window), "Confirm");
}

void MainWindow::_new_main_menu(GtkWidget* list)
{
	GtkCellRenderer* rend__name = gtk_cell_renderer_text_new();
	g_object_set(rend__name, "editable", TRUE, NULL);
	GtkCellRenderer* rend_rev = gtk_cell_renderer_text_new();
	g_object_set(rend_rev, "editable", TRUE, NULL);
	GtkCellRenderer* rend_desc = gtk_cell_renderer_text_new();
	g_object_set(rend_desc, "editable", TRUE, NULL);
	GtkCellRenderer* rend_id = gtk_cell_renderer_text_new();
	g_object_set(rend_id, "editable", FALSE, NULL);//not needed

	g_signal_connect(G_OBJECT(rend__name), "edited", G_CALLBACK(_name_edited_callback), this);
	g_signal_connect(G_OBJECT(rend_rev), "edited", G_CALLBACK(_rev_edited_callback), this);
	g_signal_connect(G_OBJECT(rend_desc), "edited", G_CALLBACK(_desc_edited_callback), this);

	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes("Name", rend__name, "text", Main::NAME, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("ID", rend_id, "text", Main::ID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Revision", rend_rev, "text", Main::REV, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Description", rend_desc, "text", Main::DESC, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	_store_parts = gtk_tree_store_new((gint)Main::N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(_store_parts));
	g_object_unref(_store_parts);

	File_Interfacer file;
	for (auto location : file.load_file_loc()) {
		std::vector<WIN32_FIND_DATA> files_data;
		location.append("\\*");
		//g_print("%s\n", (LPCWSTR)location.c_str());
		std::wstring wide_s = std::wstring(location.begin(), location.end());
		files_data = file.find_files(wide_s.c_str(), 0);
		_add_files(_parse_files(files_data));
	}

}

void MainWindow::_selection_changed_main(GtkTreeSelection* selection, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	if (!class_ref->_selection_disable_flag) {
		GtkTreeIter iter;
		class_ref->_selected_part_list.clear();
		g_list_free_full(class_ref->_list, (GDestroyNotify)gtk_tree_path_free);
		class_ref->_list = gtk_tree_selection_get_selected_rows(selection, NULL);
		for (GList* a1 = class_ref->_list; a1 != NULL; a1 = a1->next)
		{
			GtkTreePath* indv_row = (GtkTreePath*)(a1->data);
			gtk_tree_model_get_iter(GTK_TREE_MODEL(class_ref->_store_parts), &iter, indv_row);
			class_ref->_row_refs.push_back(gtk_tree_row_reference_new(GTK_TREE_MODEL(class_ref->_store_parts), indv_row));
		}
	}
}

std::vector<FileData> MainWindow::_parse_files(std::vector<WIN32_FIND_DATA> files_data)
{
	File_Interfacer file;
	std::vector<FileData> return_value;
	for (auto file_data : files_data) {
		BasicId file_parser(std::wstring(file_data.cFileName));
		for (auto file_exstension : file.load_file_type()) {
			if (file_parser.ext() == file_exstension) {
				if (file_parser.valid()) {
					return_value.push_back(FileData(file_parser.raw(), file_parser.to_str(), file_parser.rev_str(), ""));
				}
				else {
					return_value.push_back(FileData(file_parser.raw(), "", file_parser.rev_str(), ""));
				}
				break;
			}
		}
	}
	return return_value;
}

void MainWindow::_new_menu_item(GtkMenuItem* menuitem, gpointer user_data)
{
	BasicId id;
	GtkTreeIter iter;
	GtkTreeStore* store_parts = (GtkTreeStore*)user_data;

	std::string part_number = id.new_id("");
	GtkWidget* part_number_label = (GtkWidget*)(user_data);
	bool repeat_flag = true;
	while (repeat_flag) {
		part_number = id.new_id("");
		bool valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store_parts), &iter);
		repeat_flag = false;
		while (valid) {
			gchar* str_data;
			gtk_tree_model_get(GTK_TREE_MODEL(store_parts), &iter, Main::ID, &str_data, -1);
			if (part_number == std::string(str_data)) {
				repeat_flag = true;
				break;
			}
			g_free(str_data);
			valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store_parts), &iter);
		}
	}
	NewPartWindow part_window(part_number, store_parts);
	gtk_widget_show_all(part_window.window());
}

void MainWindow::_delete_menu_item(GtkMenuItem* button, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	gtk_widget_hide(class_ref->_confirm_window);
	class_ref->_selection_disable_flag = true;
	for (auto indv_rows : class_ref->_row_refs) {
		GtkTreeIter iter;
		GtkTreePath* indv_row = gtk_tree_row_reference_get_path(indv_rows);
		gtk_tree_model_get_iter(GTK_TREE_MODEL(class_ref->_store_parts), &iter, indv_row);
		gtk_tree_store_remove(class_ref->_store_parts, &iter);
	}
	class_ref->_selection_disable_flag = false;
	gtk_tree_selection_set_mode(class_ref->_select, GTK_SELECTION_NONE);
	gtk_tree_selection_set_mode(class_ref->_select, GTK_SELECTION_MULTIPLE);
}

void MainWindow::_config_menu_loc(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* display_window = (GtkWidget*)user_data;
	gtk_widget_show_all(display_window);
}

void MainWindow::_config_menu_type(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* display_window = (GtkWidget*)user_data;
	gtk_widget_show_all(display_window);
}

void MainWindow::_name_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter, Main::NAME, new_text, -1);
}

void MainWindow::_rev_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter_rawModel, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter_rawModel, Main::REV, new_text, -1);
}

void MainWindow::_desc_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter_rawModel, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter_rawModel, Main::DESC, new_text, -1);
}

void MainWindow::_delete_clicked(GtkMenuItem* button, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	gtk_widget_show_all(class_ref->_confirm_window);
}

void MainWindow::_delete_cancel(GtkButton* button, gpointer user_data)
{
	GtkWidget* window = (GtkWidget*)user_data;
	gtk_widget_hide(window);
}

void MainWindow::_add_files(std::vector<FileData> part_list)
{
	std::vector<std::string> unique_id;
	for (int a1 = 0; a1 < part_list.size(); a1++) {
		printf("%s %s %s\n", part_list[a1].name().c_str(), part_list[a1].id().c_str(), part_list[a1].rev().c_str());
		if (part_list[a1].rev() == "" && part_list[a1].id() != "") {
			unique_id.push_back(part_list[a1].id());
		}
	}
	std::sort(unique_id.begin(), unique_id.end());
	unique_id.erase(std::unique(unique_id.begin(), unique_id.end()), unique_id.end());

	GtkTreeIter iter, child;

	for (auto id_add : unique_id) {
		//determin if id has multiple files
		int count = 0;
		for (auto file_add : part_list) {
			//iterate through part list and count
			if (file_add.id() == id_add) { count++; }
			if (count > 1) { break; }
		}
		if (count > 1) {
			//multiple files
			FileData id_header("", id_add, "", "Grouping of all files with the " + id_add + " id");
			id_header.part_list_append(_store_parts, &iter);
			for (auto file_child_add : part_list) {
				if (file_child_add.id() == id_add) {
					file_child_add.part_list_append(_store_parts, &iter, &child);
				}
			}
		}
	}
	for (auto file_add : part_list) {
		if (file_add.id() == "") {
			file_add.part_list_append(_store_parts, &iter);
		}
	}
}


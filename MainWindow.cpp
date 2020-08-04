#include "MainWindow.h"

#include "UI_Handleing.h"

MainWindow::MainWindow(GtkWidget* file_type, GtkWidget* file_loc)
{
	_type_config_window = file_type;
	_loc_config_window = file_loc;
	_window_creation();
	_new_main_window();
}

GtkWidget* MainWindow::window()
{
	return _main_window;
}

void MainWindow::_window_creation()
{
	_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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

	g_signal_connect(G_OBJECT(new_part), "activate", G_CALLBACK(_new_menu_item), _part_window);
	g_signal_connect(G_OBJECT(delete_part), "activate", G_CALLBACK(_delete_menu_item), this);
	g_signal_connect(G_OBJECT(config_loc), "activate", G_CALLBACK(_config_menu_loc), _loc_config_window);
	g_signal_connect(G_OBJECT(config_types), "activate", G_CALLBACK(_config_menu_type), _type_config_window);

	GtkWidget* part_list = gtk_tree_view_new();
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(part_list), GTK_TREE_VIEW_GRID_LINES_BOTH);
	_select = gtk_tree_view_get_selection(GTK_TREE_VIEW(part_list));
	gtk_tree_selection_set_mode(_select, GTK_SELECTION_MULTIPLE);
	g_signal_connect(G_OBJECT(_select), "changed", G_CALLBACK(_selection_changed_main), this);
	gtk_container_add(GTK_CONTAINER(scrollable_list), part_list);

	g_signal_connect(_main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	_new_main_menu(part_list);

	gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_main_window), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(_main_window), TRUE);
	gtk_window_set_title(GTK_WINDOW(_main_window), "Part Number Manager");
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

	g_signal_connect(G_OBJECT(rend__name), "edited", G_CALLBACK(name_edited_callback), (gint*)Main::NAME);
	g_signal_connect(G_OBJECT(rend_rev), "edited", G_CALLBACK(name_edited_callback), (gint*)Main::REV);
	g_signal_connect(G_OBJECT(rend_desc), "edited", G_CALLBACK(name_edited_callback), (gint*)Main::DESC);

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
			gchar* part_name, * part_id, * part_rev, * part_desc;
			gtk_tree_model_get(GTK_TREE_MODEL(class_ref->_store_parts), &iter, Main::NAME, &part_name, Main::ID, &part_id, Main::REV, &part_rev, Main::DESC, &part_desc, -1);
			class_ref->_selected_part_list.push_back(Part(part_name, part_id, part_rev, part_desc, gtk_tree_row_reference_new(GTK_TREE_MODEL(class_ref->_store_parts), indv_row)));
		}
	}
}

std::vector<Part> MainWindow::_parse_files(std::vector<WIN32_FIND_DATA> files_data)
{
	File_Interfacer file;
	std::vector<Part> return_value;
	for (auto file_data : files_data) {
		std::wstring file_name = std::wstring(file_data.cFileName);
		for (auto a1 = file_name.crbegin(); a1 != file_name.crend(); a1++) {
			std::wstring file_name_modified, file_exstention;
			if (*a1 == L'.') {
				file_exstention.assign(file_name.crbegin(), a1);
				std::reverse(file_exstention.begin(), file_exstention.end());
				std::wcout << file_exstention << L" ";

				std::vector<std::string> types = file.load_file_type();
				for (auto type : types) {
					std::wstring type_conv = std::wstring(type.begin(), type.end());
					if (type_conv == file_exstention) {
						file_name_modified.assign(a1 + 1, file_name.crend());
						std::reverse(file_name_modified.begin(), file_name_modified.end());
						std::wcout << file_name_modified << L" ";
						std::string file_id = std::string(file_name_modified.begin(), file_name_modified.end());

						if (_verify_file_name(file_id)) {
							//file conforms to standards
							if (file_id.size() == 7) {
								//contains revision
								std::string rev = std::string(1, file_id.back());
								file_id.pop_back();
								return_value.push_back(Part(file_id, file_id, rev, ""));
							}
							else if (file_id.size() == 6) {
								//conforms
								if (file_exstention == L"SLDDRW") {
									return_value.push_back(Part(file_id, file_id, "DWG", ""));
								}
								else {
									return_value.push_back(Part(file_id, file_id, "MC", ""));
								}
							}
						}
						else {
							return_value.push_back(Part(file_id, "N/A", "", ""));
							//non conforming files
						}
						std::wcout << type_conv << L"==" << file_name_modified << L" ";
					}
					else {
						std::wcout << type_conv << L"!=" << file_name_modified << L" ";
					}
				}
				std::wcout << std::endl;
				break;
			}
		}
	}

	return return_value;
}

void MainWindow::_new_menu_item(GtkMenuItem* menuitem, gpointer user_data)
{
	GtkWidget* display_window = (GtkWidget*)user_data;
	gtk_widget_show_all(display_window);
}

void MainWindow::_delete_menu_item(GtkMenuItem* menuitem, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	class_ref->_selection_disable_flag = true;
	for (auto indv_part : class_ref->_selected_part_list) {
		GtkTreeIter iter;
		gchar* part_name, * part_id, * part_rev, * part_desc;

		GtkTreePath* indv_row = gtk_tree_row_reference_get_path(indv_part.row_ref());
		gtk_tree_model_get_iter(GTK_TREE_MODEL(class_ref->_store_parts), &iter, indv_row);

		gtk_tree_model_get(GTK_TREE_MODEL(class_ref->_store_parts), &iter, Main::NAME, &part_name, Main::ID, &part_id, Main::REV, &part_rev, Main::DESC, &part_desc, -1);
		g_print("Deleting: %s %s %s %s, %d\n", part_name, part_id, part_rev, part_desc, class_ref->_selected_part_list.size());

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

void MainWindow::name_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter_rawModel, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter_rawModel, Main::NAME, new_text, -1);
}

void MainWindow::rev_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter_rawModel, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter_rawModel, Main::REV, new_text, -1);
}

void MainWindow::desc_edited_callback(GtkCellRendererText* cell, gchar* path_string, gchar* new_text, gpointer user_data)
{
	MainWindow* class_ref = (MainWindow*)user_data;
	GtkTreeIter iter_rawModel;
	gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(class_ref->_store_parts), &iter_rawModel, path_string);
	gtk_tree_store_set(class_ref->_store_parts, &iter_rawModel, Main::DESC, new_text, -1);
}

bool MainWindow::_verify_file_name(std::string file_name)
{
	//id format must be 
	//11A111
	printf("%s : %d ", file_name.c_str(), file_name.size());
	if (file_name.size() != 6 && file_name.size() != 7) { return false; }
	for (int a1 = 0; a1 < file_name.size(); a1++) {
		int code = (int)file_name[a1];
		printf("%d %d ", a1, code);
		if (a1 == 2) {
			//must be A->Z
			if (65 < code && code > 90) { return false; }
		}
		else if (a1 == 6) {
			//must be A->Z
			if (65 < code && code > 90) { return false; }
		}
		else {
			//must be 0->9
			if (48 < code && code > 57) { return false; }
		}

	}
	return true;
}

void MainWindow::_add_files(std::vector<Part> part_list)
{
	std::vector<Part> master_list;
	for (int a1 = 0; a1 < part_list.size(); a1++) {
		if (part_list[a1].rev() == "MC") {
			master_list.push_back(part_list[a1]);
		}
	}
	GtkTreeIter iter, child;

	for (auto file_add : part_list) {
		if (file_add.rev() == "MC") {
			file_add.part_list_append(_store_parts, &iter);
			for (auto file_child_add : part_list) {
				if (file_child_add.rev() != "MC" && file_child_add.id() == file_add.id()) {
					file_child_add.part_list_append(_store_parts, &iter, &child);
				}
			}
		}
	}
}


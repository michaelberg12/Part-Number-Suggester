#include "UI_Handleing.h"

GtkWidget* UI_Handleing::_part_window;
GtkWidget* UI_Handleing::_main_window;

UI_Handleing::UI_Handleing(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	_window_creation();
	_new_main_window();

	gtk_widget_show_all(_main_window);

	gtk_main();
}

void UI_Handleing::_window_creation()
{
	//_part_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void UI_Handleing::_new_main_window()
{
	GtkWidget* main_window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(_main_window), main_window_box);

	GtkWidget* scrollable_list = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget* menu_bar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(main_window_box), menu_bar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_window_box), scrollable_list, TRUE, TRUE, 0);

	GtkWidget* new_part = gtk_menu_item_new_with_label("New");
	GtkWidget* delete_part = gtk_menu_item_new_with_label("Delete");
	GtkWidget* configure_files = gtk_menu_item_new_with_label("Config");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), new_part);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), delete_part);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), configure_files);


	GtkWidget* part_list = gtk_tree_view_new();
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(part_list), GTK_TREE_VIEW_GRID_LINES_BOTH);
	gtk_container_add(GTK_CONTAINER(scrollable_list), part_list);

	g_signal_connect(_main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	_new_main_menu(part_list);

	gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_main_window), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(_main_window), TRUE);
	gtk_window_set_title(GTK_WINDOW(_main_window), "Part Number Manager");
}

void UI_Handleing::_new_part_window()
{
	GtkWidget* vert_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(_part_window), vert_main_box);

	g_signal_connect(_part_window, "destroy", G_CALLBACK(_part_number_confirm), NULL);
	_new_part_creation_menu(vert_main_box);

	gtk_window_set_position(GTK_WINDOW(_part_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_part_window), 300, 250);
	gtk_window_set_resizable(GTK_WINDOW(_part_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_part_window), "Part Number Manager");
}

void UI_Handleing::_new_part_creation_menu(GtkWidget* vertical_box)
{
	//============================= part number ui elements ===================================
	GtkWidget* part_number_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* part_number_label = gtk_label_new("");
	GtkWidget* part_number_frame = gtk_frame_new("Part Number");
	gtk_label_set_markup(GTK_LABEL(part_number_label), "<span size=\"50000\">11A111</span>");
	gtk_container_add(GTK_CONTAINER(part_number_frame), part_number_label);
	gtk_frame_set_label_align(GTK_FRAME(part_number_frame), 0.1, 0.5);
	//gtk_box_pack_start(GTK_BOX(show_lidar_pos), label_show_lidar_pos, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(part_number_box), part_number_frame, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(vertical_box), part_number_box, TRUE, FALSE, 10);
	//=========================================================================================

	GtkWidget* confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* number_confirm = gtk_button_new_with_label("Use This Number");
	GtkWidget* generate_new = gtk_button_new_with_label("Generate New");
	gtk_box_pack_start(GTK_BOX(confirm_box), generate_new, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(confirm_box), number_confirm, TRUE, FALSE, 20);
	gtk_box_pack_end(GTK_BOX(vertical_box), confirm_box, FALSE, FALSE, 10);

	g_signal_connect(G_OBJECT(number_confirm), "clicked", G_CALLBACK(_part_number_confirm), NULL);
}

void UI_Handleing::_new_main_menu(GtkWidget* list)
{
	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", NAME, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Revision", renderer, "text", REV, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", DESC, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	GtkTreeStore* store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	g_object_unref(store);

	GtkTreeIter iter;

	//============================= part number ui elements ===================================
	for (int a1 = 0; a1 < 40; a1++) {
		std::string part_number;
		for (int a2 = 0; a2 < 5; a2++) {
			part_number.append(std::to_string(rand() % 8 + 1));
		}
		part_number.insert(2, std::string(1, (char)(rand() % 26 + 65)));

		Part default_part("Builder", part_number,  std::string(1, (char)(rand() % 26 + 65)), "Sample Text");

		default_part.part_list_append(store, &iter);
	}
	//=========================================================================================

}

void UI_Handleing::_part_number_confirm(GtkButton* button, gpointer user_data)
{
	gtk_main_quit();
}
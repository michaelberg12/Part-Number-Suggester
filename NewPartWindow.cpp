#include "NewPartWindow.h"

NewPartWindow::NewPartWindow(std::string new_id, GtkTreeStore* file_store)
{
	this->_file_store = file_store;
	this->_new_id = new_id;
	_window_creation();
	_new_part_window();
}

GtkWidget* NewPartWindow::window()
{
	return _part_window;
}

void NewPartWindow::_window_creation()
{
	_part_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void NewPartWindow::_new_part_window()
{
	GtkWidget* vert_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(_part_window), vert_main_box);
	_new_part_creation_menu(vert_main_box);

	gtk_window_set_position(GTK_WINDOW(_part_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_part_window), 300, 400);
	gtk_window_set_resizable(GTK_WINDOW(_part_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_part_window), "Part Number Manager");
}

void NewPartWindow::_new_part_creation_menu(GtkWidget* vertical_box)
{
	std::string part_number = _new_id;
	part_number.insert(0, "<span size=\"50000\">");
	part_number.append("</span>");
	//============================= part number ui elements ===================================
	GtkWidget* part_number_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* part_number_label = gtk_label_new("");
	GtkWidget* part_number_frame = gtk_frame_new("Part Number");
	gtk_label_set_markup(GTK_LABEL(part_number_label), part_number.c_str());
	gtk_container_add(GTK_CONTAINER(part_number_frame), part_number_label);
	gtk_frame_set_label_align(GTK_FRAME(part_number_frame), 0.1, 0.5);
	//gtk_box_pack_start(GTK_BOX(show_lidar_pos), label_show_lidar_pos, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(part_number_box), part_number_frame, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(vertical_box), part_number_box, TRUE, FALSE, 10);
	//=========================================================================================

	GtkWidget* part_name_frame = gtk_frame_new("Part Name");
	GtkWidget* _part_name_input = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(part_name_frame), _part_name_input);
	gtk_frame_set_label_align(GTK_FRAME(part_name_frame), 0.1, 0.5);

	GtkWidget* part_desc_frame = gtk_frame_new("Part Description");
	GtkWidget* _part_desc_input = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(part_desc_frame), _part_desc_input);
	gtk_frame_set_label_align(GTK_FRAME(part_name_frame), 0.1, 0.5);

	gtk_box_pack_start(GTK_BOX(vertical_box), part_name_frame, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(vertical_box), part_desc_frame, FALSE, FALSE, 10);

	GtkWidget* confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* number_confirm = gtk_button_new_with_label("Use This Number");
	GtkWidget* cancel_part = gtk_button_new_with_label("Cancel");
	gtk_box_pack_start(GTK_BOX(confirm_box), cancel_part, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(confirm_box), number_confirm, TRUE, FALSE, 20);

	gtk_box_pack_end(GTK_BOX(vertical_box), confirm_box, FALSE, FALSE, 10);

	g_signal_connect(_part_window, "destroy", G_CALLBACK(_close_window), this->_part_window);
	g_signal_connect(G_OBJECT(number_confirm), "clicked", G_CALLBACK(_part_number_confirm), this);
	g_signal_connect(G_OBJECT(cancel_part), "clicked", G_CALLBACK(_close_window), this->_part_window);
}

void NewPartWindow::_part_number_confirm(GtkButton* button, gpointer user_data)
{
	//add new part
	NewPartWindow* class_ref = (NewPartWindow*)user_data;
	
	gtk_widget_hide(GTK_WIDGET(class_ref->_part_window));
}

void NewPartWindow::_close_window(GtkButton* button, gpointer user_data)
{
	//don't add new part
	GtkWidget* window = (GtkWidget*)user_data;
	gtk_widget_hide(window);
}
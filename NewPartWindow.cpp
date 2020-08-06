#include "NewPartWindow.h"

NewPartWindow::NewPartWindow(std::string new_id)
{
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

	g_signal_connect(_part_window, "destroy", G_CALLBACK(_part_number_confirm), NULL);
	_new_part_creation_menu(vert_main_box);

	gtk_window_set_position(GTK_WINDOW(_part_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_part_window), 300, 400);
	gtk_window_set_resizable(GTK_WINDOW(_part_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_part_window), "Part Number Manager");

	gtk_window_set_destroy_with_parent(GTK_WINDOW(_part_window), TRUE);
}

void NewPartWindow::_new_part_creation_menu(GtkWidget* vertical_box)
{
	std::string part_number, temp_holder;
	for (int a2 = 0; a2 < 5; a2++) {
		part_number.append(std::to_string(rand() % 8 + 1));
	}
	part_number.insert(2, std::string(1, (char)(rand() % 26 + 65)));
	temp_holder = part_number;
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
	_part_name_input = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(part_name_frame), _part_name_input);
	gtk_frame_set_label_align(GTK_FRAME(part_name_frame), 0.1, 0.5);

	GtkWidget* part_desc_frame = gtk_frame_new("Part Description");
	_part_desc_input = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(part_desc_frame), _part_desc_input);
	gtk_frame_set_label_align(GTK_FRAME(part_name_frame), 0.1, 0.5);

	gtk_box_pack_start(GTK_BOX(vertical_box), part_name_frame, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(vertical_box), part_desc_frame, FALSE, FALSE, 10);

	_new_part = Part(gtk_entry_get_text(GTK_ENTRY(_part_name_input)), temp_holder, "A", gtk_entry_get_text(GTK_ENTRY(_part_name_input)));

	GtkWidget* confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* number_confirm = gtk_button_new_with_label("Use This Number");
	GtkWidget* generate_new = gtk_button_new_with_label("Generate New");
	gtk_box_pack_start(GTK_BOX(confirm_box), generate_new, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(confirm_box), number_confirm, TRUE, FALSE, 20);

	gtk_box_pack_end(GTK_BOX(vertical_box), confirm_box, FALSE, FALSE, 10);

	g_signal_connect(G_OBJECT(number_confirm), "clicked", G_CALLBACK(_part_number_confirm), part_number_label);
	g_signal_connect(G_OBJECT(generate_new), "clicked", G_CALLBACK(_generate_new_part_number), part_number_label);
}
#include "UI_Handleing.h"

GtkWidget* UI_Handleing::_part_window;

UI_Handleing::UI_Handleing(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	_window_creation();
	_new_part_window();

	gtk_widget_show_all(_part_window);

	gtk_main();
}

void UI_Handleing::_window_creation()
{
	_part_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void UI_Handleing::_new_part_window()
{
	GtkWidget* vert_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(_part_window), vert_main_box);

	g_signal_connect(_part_window, "destroy", G_CALLBACK(_part_number_confirm), NULL);
	_option_menu_creation(vert_main_box);

	gtk_window_set_position(GTK_WINDOW(_part_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_part_window), 300, 250);
	gtk_window_set_resizable(GTK_WINDOW(_part_window), FALSE);
	gtk_window_set_title(GTK_WINDOW(_part_window), "Part Number Manager");
}

void UI_Handleing::_option_menu_creation(GtkWidget* vertical_box)
{
	//=============================lidar setting ui elements===================================
	GtkWidget* show_lidar_pos = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* label_show_lidar_pos = gtk_label_new("");
	GtkWidget* part_number_frame = gtk_frame_new("Part Number");
	gtk_label_set_markup(GTK_LABEL(label_show_lidar_pos), "<span size=\"50000\">11A111</span>");
	gtk_container_add(GTK_CONTAINER(part_number_frame), label_show_lidar_pos);
	gtk_frame_set_label_align(GTK_FRAME(part_number_frame), 0.1, 0.5);
	//gtk_box_pack_start(GTK_BOX(show_lidar_pos), label_show_lidar_pos, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(show_lidar_pos), part_number_frame, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(vertical_box), show_lidar_pos, TRUE, FALSE, 10);
	//=========================================================================================

	GtkWidget* confirm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget* number_confirm = gtk_button_new_with_label("Use This Number");
	GtkWidget* generate_new = gtk_button_new_with_label("Generate New");
	gtk_box_pack_start(GTK_BOX(confirm_box), generate_new, TRUE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(confirm_box), number_confirm, TRUE, FALSE, 20);
	gtk_box_pack_end(GTK_BOX(vertical_box), confirm_box, FALSE, FALSE, 10);

	g_signal_connect(G_OBJECT(number_confirm), "clicked", G_CALLBACK(_part_number_confirm), NULL);
}


void UI_Handleing::_part_number_confirm(GtkButton* button, gpointer user_data)
{
	gtk_main_quit();
}
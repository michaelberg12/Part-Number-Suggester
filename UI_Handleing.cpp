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
	GtkWidget* scrollable_list = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget* part_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(_main_window), scrollable_list);
	gtk_container_add(GTK_CONTAINER(scrollable_list), part_list);

	g_signal_connect(_main_window, "destroy", G_CALLBACK(_part_number_confirm), NULL);
	_new_main_menu(part_list);

	gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(_main_window), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(_main_window), FALSE);
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

void UI_Handleing::_new_main_menu(GtkWidget* part_list)
{
	//============================= part number ui elements ===================================
	for (int a1 = 0; a1 < 40; a1++) {
		GtkWidget* part_number_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		GtkWidget* part_number_label = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(part_number_label), std::string("<span size=\"10000\">" + std::string("Builder") + "</span>").c_str());
		GtkWidget* part_name_label = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(part_name_label), "<span size=\"10000\">11A111</span>");
		GtkWidget* part_rev_label = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(part_rev_label), "<span size=\"10000\">A</span>");
		GtkWidget* part_description_label = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(part_description_label), "<span size=\"10000\">Sample Text</span>");
		gtk_box_pack_start(GTK_BOX(part_number_box), part_name_label, TRUE, FALSE, 10);
		gtk_box_pack_start(GTK_BOX(part_number_box), part_number_label, TRUE, FALSE, 10);
		gtk_box_pack_start(GTK_BOX(part_number_box), part_rev_label, TRUE, FALSE, 10);
		gtk_box_pack_start(GTK_BOX(part_number_box), part_description_label, TRUE, FALSE, 10);
		gtk_container_add(GTK_CONTAINER(part_list), part_number_box);
	}
	//=========================================================================================

}


void UI_Handleing::_part_number_confirm(GtkButton* button, gpointer user_data)
{
	gtk_main_quit();
}
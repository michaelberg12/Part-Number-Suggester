#pragma once

#include <vector>
#include <gtk/gtk.h>
#include <string>

#include "BasicId.h"

class NewPartWindow
{
public:
	NewPartWindow(std::string new_id);
	GtkWidget* window();
private:
	std::string _new_id;

	GtkWidget* _part_window;

	void _window_creation();

	void _new_part_window();
	void _new_part_creation_menu(GtkWidget* vertical_box);

	static void _part_number_confirm(GtkButton* button, gpointer user_data);
	static void close_window(GtkButton* button, gpointer user_data);
};


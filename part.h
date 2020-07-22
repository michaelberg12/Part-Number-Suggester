#pragma once
#include <string>
#include <cairo.h>
#include <gtk/gtk.h>
enum {
	NAME,
	ID,
	REV,
	DESC,
	N_COLUMNS
};

class Part
{
public:
	Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc);

	void part_list_append(GtkTreeStore* store, GtkTreeIter *iter);

private:

	std::string _part_name;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;
};


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
	//for adding parts
	Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc);
	//for tracking selected parts
	Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc, GtkTreeRowReference* row_reference);

	void part_list_append(GtkTreeStore* store, GtkTreeIter *iter);

	GtkTreeRowReference* row_ref();
private:
	std::string _part_name;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;

	GtkTreeRowReference* _row_reference;
};


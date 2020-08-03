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



	std::string name();
	std::string id();
	std::string rev();
	std::string desc();

	std::string save_string();

	void part_list_append(GtkTreeStore* store, GtkTreeIter *iter);
	void part_list_append(GtkTreeStore* store, GtkTreeIter* iter, GtkTreeIter* child_iter);

	GtkTreeRowReference* row_ref();
private:
	std::string _part_name;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;

	GtkTreeRowReference* _row_reference;
};


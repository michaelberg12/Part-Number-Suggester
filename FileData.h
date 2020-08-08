#pragma once
#include <string>
#include <cairo.h>
#include <gtk/gtk.h>
#include <Windows.h>

#include "Enums.h"

class FileData
{
public:
	//for adding parts
	FileData(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc);
	//for tracking selected parts



	std::string name();
	std::string id();
	std::string rev();
	std::string desc();
	std::string loc();
	std::string edited();

	std::string save_string();

	void part_list_append(GtkTreeStore* store, GtkTreeIter *iter);
	void part_list_append(GtkTreeStore* store, GtkTreeIter* iter, GtkTreeIter* child_iter);

	bool operator==(const FileData& o_f);
	bool operator!=(const FileData& o_f);
private:
	std::string _part_name;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;
	std::wstring _file_loc;
	WIN32_FIND_DATA _file_data;
};


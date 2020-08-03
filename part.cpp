#include "Part.h"

Part::Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc)
{
	_part_name = part_name;
	_part_id = part_id;
	_part_rev = part_rev;
	_part_desc = part_desc;
}

Part::Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc, GtkTreeRowReference* row_reference)
{
	_part_name = part_name;
	_part_id = part_id;
	_part_rev = part_rev;
	_part_desc = part_desc;
	_row_reference = row_reference;
}

std::string Part::name()
{
	return _part_name;
}

std::string Part::id()
{
	return _part_id;
}

std::string Part::rev()
{
	return _part_rev;
}

std::string Part::desc()
{
	return _part_desc;
}

std::string Part::save_string()
{
	return (_part_name + " " + _part_id + " " + _part_rev + " " + _part_desc);
}

void Part::part_list_append(GtkTreeStore* store, GtkTreeIter *iter)
{
	gtk_tree_store_append(store, iter, NULL);
	gtk_tree_store_set(store, iter, NAME, this->_part_name.c_str(), ID, this->_part_id.c_str(), REV, this->_part_rev.c_str(), DESC, this->_part_desc.c_str(), -1);
}

void Part::part_list_append(GtkTreeStore* store, GtkTreeIter* iter, GtkTreeIter* child_iter)
{
	gtk_tree_store_append(store, child_iter, iter);
	gtk_tree_store_set(store, child_iter, NAME, this->_part_name.c_str(), ID, this->_part_id.c_str(), REV, this->_part_rev.c_str(), DESC, this->_part_desc.c_str(), -1);
}

GtkTreeRowReference* Part::row_ref()
{
	return _row_reference;
}


#include "Part.h"

Part::Part(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc)
{
	_part_name = part_name;
	_part_id = part_id;
	_part_rev = part_rev;
	_part_desc = part_desc;


}

void Part::part_list_append(GtkTreeStore* store, GtkTreeIter *iter)
{
	gtk_tree_store_append(store, iter, NULL);
	gtk_tree_store_set(store, iter, NAME, this->_part_name.c_str(), ID, this->_part_id.c_str(), REV, this->_part_rev.c_str(), DESC, this->_part_desc.c_str(), -1);
}

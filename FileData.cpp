#include "FileData.h"

FileData::FileData(std::string part_name, std::string part_id, std::string part_rev, std::string part_desc)
{
	_part_name = part_name;
	_part_id = part_id;
	_part_rev = part_rev;
	_part_desc = part_desc;
}

FileData::FileData(WIN32_FIND_DATA file_data, std::wstring parent_path) {
	this->_part_desc = "";
	this->_file_data = file_data;
	this->_file_loc = parent_path + this->_file_data.cFileName;
	BasicId id(this->_file_data.cFileName);
	this->_part_name = id.raw();
	this->_file_ext = id.ext();
	if (id.valid()) {
		this->_part_id = id.to_str();
		this->_part_rev = id.rev_str();
	}
	else {
		this->_part_id = "";
		this->_part_rev = "";
	}
}

FileData::FileData(WIN32_FIND_DATA file_data, std::wstring parent_path, std::string part_name, std::string part_rev, std::string part_desc)
{
	this->_part_desc = part_desc;
	this->_file_data = file_data;
	this->_file_loc = parent_path + this->_file_data.cFileName;
	BasicId id(this->_file_data.cFileName);
	this->_part_name = part_name;
	this->_file_ext = id.ext();
	this->_part_rev = part_rev;
	if (id.valid()) {
		this->_part_id = id.to_str();
	}
	else {
		this->_part_id = "";
	}
}

std::string FileData::name()
{
	return _part_name;
}

std::string FileData::id()
{
	return _part_id;
}

std::string FileData::rev()
{
	return _part_rev;
}

std::string FileData::desc()
{
	return _part_desc;
}

std::string FileData::loc()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(this->_file_loc);
}

std::string FileData::ext()
{
	return this->_file_ext;
}

std::string FileData::edited()
{
	SYSTEMTIME SystemTime;
	FileTimeToSystemTime(&_file_data.ftLastWriteTime, &SystemTime);
	if (std::to_string(SystemTime.wYear) == "1601") {
		return ""; //this solution may want to be updated but since computers weren't invented yet I'd say this is safe to assume
	}
	std::string date(std::to_string(SystemTime.wMonth) + "/" + std::to_string(SystemTime.wDay) + "/" + std::to_string(SystemTime.wYear));
	std::string time(std::to_string(SystemTime.wHour) + ":" + std::to_string(SystemTime.wMinute));
	return time + " " + date;
}

std::string FileData::save_string()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string file_location = converter.to_bytes(this->_file_loc);
	return (file_location + "," + this->_part_name + ","+ this->_part_rev + "," + this->_part_desc);
}

void FileData::part_list_append(GtkTreeStore* store, GtkTreeIter *iter)
{
	gtk_tree_store_append(store, iter, NULL);
	gtk_tree_store_set(store, iter, Main::NAME, this->_part_name.c_str(), Main::ID, this->_part_id.c_str(), Main::REV, this->_part_rev.c_str(), Main::DESC, this->_part_desc.c_str(), Main::LAST_EDITED, this->edited().c_str(), Main::LOC, this->loc().c_str(), -1);
}

void FileData::part_list_append(GtkTreeStore* store, GtkTreeIter* iter, GtkTreeIter* child_iter)
{
	gtk_tree_store_append(store, child_iter, iter);
	gtk_tree_store_set(store, child_iter, Main::NAME, this->_part_name.c_str(), Main::ID, this->_part_id.c_str(), Main::REV, this->_part_rev.c_str(), Main::DESC, this->_part_desc.c_str(), Main::LAST_EDITED, this->edited().c_str(), Main::LOC, this->loc().c_str(), -1);
}

bool FileData::operator==(const FileData& o_f)
{
	//this is in case the user edited any of the other atributes
	return (this->_file_loc == o_f._file_loc);
}

bool FileData::operator!=(const FileData& o_f)
{
	return !(*this == o_f);
}


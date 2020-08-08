#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

//because I am lazy
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "FileData.h"

class File_Interfacer
{
public:
	File_Interfacer();

	std::vector<WIN32_FIND_DATA> find_files(LPCWSTR file_location, int level);

	void save_main(std::vector<FileData> part_list);
	void save_file_loc(std::vector<std::string> part_list);
	void save_file_type(std::vector<std::string> part_list);

	std::vector<FileData> load_main();
	std::vector<std::string> load_file_loc();
	std::vector<std::string> load_file_type();
private:

	void _save(std::string file_loc, std::vector<std::string> line_list);
	std::vector<std::string> _load(std::string file_loc);
};


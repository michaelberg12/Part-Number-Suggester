#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

class File_Interfacer
{
public:
	File_Interfacer();

	std::vector<WIN32_FIND_DATA> find_files(LPCWSTR file_location, int level);

private:

};


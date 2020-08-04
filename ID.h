#pragma once
#include <string>

__interface ID
{
public:
	//to display
	std::string to_str();
	std::wstring to_wstr();

	//to extract rev data
	std::string rev_str();
	std::wstring rev_wstr();

	//check validity
	bool valid(std::wstring);
	bool valid(std::string);

	//the size of the id structure
	int size();
};


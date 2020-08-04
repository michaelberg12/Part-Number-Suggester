#pragma once

#include <string>

#include "ID.h"

class BasicId : public ID
{
public:
	BasicId(std::wstring file_name);

	//to display (parsed)
	std::string to_str();
	std::wstring to_wstr();

	//information about the id
	std::string type();
	std::string rev_str();
	std::string raw();

	//generate a new id
	std::string new_id(std::string rev);

	//check validity
	bool valid(std::wstring);
	bool valid(std::string);

	//the size of the id structure
	int size();
private:

};


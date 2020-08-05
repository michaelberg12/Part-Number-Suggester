#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include "ID.h"

/*
	===================================ID STRUCTURE============================================
	Example 37G103AA
			01234567

	37 - The 0 and 1 space are numbers from 0 -> 9 and is random      (R)
	G - The 2 space is any letter from A -> Z (capital) and is random (R)
	103 - The 3, 4, and 5 space are numbers from 0 -> 9 and is random (R)
	AA - The 6 and 7 space are from A->Z and are not random

		The letters are incrimented in a base 26 fasion
		The letters are all capital
		The letters indicates the revision
		There may be no revision letters and that indicates the master copy

	(R) - Required
	===========================================================================================
*/

class BasicId : public ID
{
public:
	BasicId();
	BasicId(std::wstring file_name);
	BasicId(std::string file_name);

	//to display (parsed)
	std::string to_str();
	std::wstring to_wstr();

	//information about the id
	std::string type();
	std::string rev_str();
	std::string raw();

	//generate a new id
	std::string new_id(std::string rev);

	//check validity and does not parse the string
	bool valid();
	bool valid(std::string);
	bool valid(std::wstring);

	//the size of the id structure
	int size();

	void operator=(const BasicId& b_id);
	bool operator==(const BasicId& b_id);
private:
	std::string _wstr_to_str(std::wstring w_string);
	std::wstring _str_to_wstr(std::string n_string);

	void _parse();

	std::string _file_name;
	std::string _id;
	std::string _rev;
};


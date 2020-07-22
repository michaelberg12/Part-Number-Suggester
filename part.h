#pragma once
#include <string>

class Part
{
public:
	Part(std::string part_number, std::string part_id, std::string part_rev, std::string part_desc);

	char* number();
	char* id();
	char* rev();
	char* desc();
private:
	std::string _part_number;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;
};


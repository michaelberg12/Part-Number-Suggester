#pragma once
#include <string>

class Part
{
public:
	Part(std::string part_number, std::string part_id, std::string part_rev, std::string part_desc);

	void set_size(int size);

	const char* number();
	const char* id();
	const char* rev();
	const char* desc();

private:

	int _size;
	std::string _part_number;
	std::string _part_id;
	std::string _part_rev;
	std::string _part_desc;

};


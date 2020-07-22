#include "part.h"

Part::Part(std::string part_number, std::string part_id, std::string part_rev, std::string part_desc)
{
	_part_number = part_number;
	_part_id = part_id;
	_part_rev = part_rev;
	_part_desc = part_desc;
	_size = 10000;
}

void Part::set_size(int size)
{
	_size = size;
}

const char* Part::number()
{
	return std::string("<span size=\"" + std::to_string(_size)+ "\">" + _part_number + "</span>").c_str();
}

const char* Part::id()
{
	return std::string("<span size=\"" + std::to_string(_size) + "\">" + _part_id + "</span>").c_str();
}

const char* Part::rev()
{
	return std::string("<span size=\"" + std::to_string(_size) + "\">" + _part_rev + "</span>").c_str();
}

const char* Part::desc()
{
	return std::string("<span size=\"" + std::to_string(_size) + "\">" + _part_desc + "</span>").c_str();
}

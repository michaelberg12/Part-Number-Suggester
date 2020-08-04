#include "BasicId.h"

BasicId::BasicId()
{
}

BasicId::BasicId(std::wstring file_name)
{
	id.assign(file_name.begin(), file_name.end());
}

std::string BasicId::to_str()
{
	return std::string();
}

std::wstring BasicId::to_wstr()
{
	return std::wstring();
}

std::string BasicId::type()
{
	return std::string();
}

std::string BasicId::rev_str()
{
	return std::string();
}

std::string BasicId::raw()
{
	return std::string();
}

std::string BasicId::new_id(std::string rev)
{
	return std::string();
}

bool BasicId::valid(std::wstring)
{
	return false;
}

bool BasicId::valid(std::string)
{
	return false;
}

bool BasicId::valid()
{
	return false;
}

int BasicId::size()
{
	return 0;
}

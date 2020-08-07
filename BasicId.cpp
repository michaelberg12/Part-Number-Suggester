#include "BasicId.h"

BasicId::BasicId()
{
	this->_file_name = "";
	this->_file_name_parsed = "";
	this->_exstension = "";
	this->_id = "";
	this->_rev = "";
}

BasicId::BasicId(std::wstring file_name)
{
	this->_file_name = this->_wstr_to_str(file_name);
	this->_parse();
}

BasicId::BasicId(std::string file_name)
{
	this->_file_name = file_name;
	this->_parse();
}

std::string BasicId::to_str()
{
	return this->_id;
}

std::wstring BasicId::to_wstr()
{
	return this->_str_to_wstr(this->_id);
}

std::string BasicId::type()
{
	return std::string("BasicID");
}

std::string BasicId::rev_str()
{
	return this->_rev;
}

std::string BasicId::raw()
{
	return this->_file_name;
}

std::string BasicId::raw_par()
{
	return this->_file_name_parsed;
}

std::string BasicId::ext()
{
	return this->_exstension;
}

std::string BasicId::new_id(std::string rev)
{
	srand(time(0));
	std::string return_id;
	for (int a2 = 0; a2 < 5; a2++) {
		return_id.append(std::to_string(rand() % 8 + 1));
	}
	return_id.insert(2, std::string(1, (char)(rand() % 26 + 65)));
	std::string pre_rev = return_id;
	return_id.append(rev);
	//ensure that the revision is complient
	if (this->valid(return_id)) {
		return return_id;
	}
	return pre_rev;
}

bool BasicId::valid(std::wstring w_id)
{
	return valid(_wstr_to_str(w_id));
}

bool BasicId::valid(std::string id)
{
	if (id.size() < 6 || id.size() > 8) { return false; }
	for (int a1 = 0; a1 < id.size(); a1++) {
		int code = (int)id[a1];
		if (a1 == 2 || a1 == 6 || a1 == 7) {
			//must be A->Z
			if (65 > code || code > 90) { return false; }
		}
		else {
			//must be 0->9
			if (48 > code || code > 57) { return false; }
		}

	}
	return true;
}

bool BasicId::valid()
{
	return this->valid(this->_id);
}

int BasicId::size()
{
	return (this->_id.size() + this->_rev.size());
}

void BasicId::operator=(const BasicId& b_id)
{
	this->_file_name = b_id._file_name;
	this->_file_name_parsed = b_id._file_name_parsed;
	this->_exstension = b_id._exstension;
	this->_id = b_id._id;
	this->_rev = b_id._rev;
}

bool BasicId::operator==(const BasicId& b_id)
{
	return (this->_id == b_id._id && this->_rev == b_id._rev);
}

bool BasicId::operator!=(const BasicId& b_id)
{
	return !(*this == b_id);
}

std::string BasicId::_wstr_to_str(std::wstring w_string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(w_string);
}

std::wstring BasicId::_str_to_wstr(std::string n_string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(n_string);
}

void BasicId::_parse()
{
	bool exstension_flag = false;
	for (auto a1 = _file_name.rbegin(); a1 != _file_name.rend(); a1++) {
		if (*a1 == '.') {
			exstension_flag = true;
			std::string file_id, file_exstention;
			//assign the file exstension string from the last . to the end
			file_exstention.assign(_file_name.rbegin(), a1);
			std::reverse(file_exstention.begin(), file_exstention.end());

			this->_exstension = file_exstention;
			//assign the file name
			file_id.assign(a1 + 1, _file_name.rend());
			std::reverse(file_id.begin(), file_id.end());

			//the file name without the exstension
			this->_file_name_parsed = file_id;
			//check to see if this is a basic ID
			if (this->valid(file_id)) {
				this->_id.assign(_file_name.begin(), _file_name.begin() + 6);
				//file conforms to standards
				if (file_id.size() <= 7) {
					//conforms and contains revision
					this->_rev.assign(file_id.begin() + 6, file_id.end());
				}
				else if (file_id.size() == 6) {
					//conforms
					this->_rev = "";
				}
			}
			else {
				//non conforming files
				this->_rev = "";
				this->_id = "";
			}
			break;
		}
	}
	if (!exstension_flag && this->valid(this->_file_name)) {
		this->_file_name_parsed = this->_file_name;
		this->_exstension = "";
		//id conforms to standards with no file exstension
		this->_id.assign(_file_name.begin(), _file_name.begin() + 6);
		if (_file_name.size() <= 8) {
			//conforms and contains revision
			this->_rev.assign(_file_name.begin() + 6, _file_name.end());
		}
		else if (_file_name.size() == 6) {
			//conforms
			this->_rev = "";
		}
	}
	else if (!exstension_flag) {
		//id does not conforms to standards with no file exstension
		this->_exstension = "";
		this->_file_name_parsed = this->_file_name;
		this->_rev = "";
		this->_id = "";
	}
}

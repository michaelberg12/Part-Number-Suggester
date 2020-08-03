#include "file_interfacer.h"

File_Interfacer::File_Interfacer()
{
    

}

std::vector<WIN32_FIND_DATA> File_Interfacer::find_files(LPCWSTR file_location, int level)
{
    std::vector<WIN32_FIND_DATA> return_value;
    WIN32_FIND_DATA file;
    HANDLE search_handle = FindFirstFile(file_location, &file);
    if (search_handle)
    {
        do
        {
            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                std::wstring file_name = std::wstring(file.cFileName);
                if (file_name != L"." && file_name != L"..") {
                    for (int a1 = 0; a1 < level; a1++) { printf("   "); }
                    std::wstring file_path = std::wstring(file_location);
                    file_path.pop_back();
                    std::wcout << "D: " << file.cFileName;
                    std::wcout << " S: " << (file_path + file_name + L"\\*") << std::endl;
                    std::vector<WIN32_FIND_DATA> found_files = find_files((file_path + file_name + L"\\*").c_str(), level + 1);
                    return_value.insert(return_value.end(), found_files.begin(), found_files.end());
                }
            }
            else if (file.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
                return_value.push_back(file);
                for (int a1 = 0; a1 < level; a1++) { printf("   "); }
                std::wcout << file.cFileName << std::endl;
            }

        } while (FindNextFile(search_handle, &file));
        FindClose(search_handle);
    }
    return return_value;
}

void File_Interfacer::save_main(std::vector<Part> part_list)
{
    std::vector<std::string> input;
    for (auto part : part_list) {
        input.push_back(part.save_string());
    }
    this->_save("PartSave", input);
}

void File_Interfacer::save_file_loc(std::vector<std::string> file_loc)
{
    this->_save("LocSave", file_loc);
}

void File_Interfacer::save_file_type(std::vector<std::string> file_type)
{
    this->_save("TypeSave", file_type);
}

std::vector<Part> File_Interfacer::load_main()
{
    std::vector<Part> return_value;
    std::vector<std::string> loaded_lines = this->_load("PartSave");
    for (auto line : loaded_lines) {
        std::vector<std::string> buffer;
        boost::split(buffer, line, boost::is_any_of(" "));
        if (buffer.size() >= 4){
            return_value.push_back(Part(buffer[0], buffer[1], buffer[2], buffer[3]));
        }
    }
    return return_value;
}

std::vector<std::string> File_Interfacer::load_file_loc()
{
    return _load("LocSave");
}

std::vector<std::string> File_Interfacer::load_file_type()
{
    return _load("TypeSave");
}

void File_Interfacer::_save(std::string file_loc, std::vector<std::string> line_list)
{
    std::ofstream save_file;
    save_file.open(file_loc, std::ios::trunc);
    if (save_file.is_open()) {
        for (auto line : line_list) {
            save_file << line << std::endl;
        }
        save_file.close();
    }
}

std::vector<std::string> File_Interfacer::_load(std::string file_loc)
{
    std::vector<std::string> return_vector;
    std::ifstream saved_file;
    saved_file.open(file_loc);
    if (saved_file.is_open()) {
        std::string buffer;
        while (std::getline(saved_file, buffer)) {
            return_vector.push_back(buffer);
        }
    }
    return return_vector;
}

#include "file_interfacer.h"

File_Interfacer::File_Interfacer()
{
    

}

std::vector<WIN32_FIND_DATA> File_Interfacer::find_files(LPCWSTR file_location, int level)
{
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
                    find_files((file_path + file_name + L"\\*").c_str(), level + 1);
                }
            }
            else if (file.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
                for (int a1 = 0; a1 < level; a1++) { printf("   "); }
                std::wcout << file.cFileName << std::endl;
            }

        } while (FindNextFile(search_handle, &file));
        FindClose(search_handle);
    }
    return std::vector<WIN32_FIND_DATA>();
}

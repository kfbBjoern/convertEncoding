#include "handleFiles.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "windows.h"

namespace fs = std::filesystem;

void  addFiles(std::vector< std::string >& files, std::string parameter)
{
    if (!std::filesystem::exists(parameter)) {
        std::cerr << "\t files does not exist :" << parameter << "\n";
        return;
    }

    if (fs::is_regular_file(parameter)) {
        files.emplace_back(parameter);
        return;
    }

    if (fs::is_directory(parameter)) {
        for(auto& p: fs::recursive_directory_iterator(parameter))
        {
            // demo_status(*it, it->symlink_status()); // use cached status from directory entry
            if (fs::is_regular_file(p)) {
                files.emplace_back(p.path());
            }
        }
        return;
    }

    return;
}

bool hasFileBOM(std::fstream& file)
{
    std::string bom;
    std::getline(file, bom);
    file.seekg(0);
    if ('\xEF' == bom[0] && '\xBB' == bom[1] && '\xBF' == bom[2])
    {
        return true;
    }
    else 
    {
        return false;
    }

}

void readFile(std::fstream& stream, std::string& content)
{
    stream.imbue(std::locale("C"));
    stream.seekg(0, std::ios::end);   
    content.reserve(stream.tellg());
    stream.seekg(0, std::ios::beg);

    content.assign((std::istreambuf_iterator<char>(stream)),
                std::istreambuf_iterator<char>());                
    return;
}

void convertString(std::string& content, std::string& utf8Content)
{
    std::string codepage_str;
    int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, content.c_str(),content.length(), nullptr, 0);

    std::wstring utf16_str(size, '\0');
    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, content.c_str(), content.length(), &utf16_str[0], size);

    int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),utf16_str.length(), nullptr, 0, nullptr, nullptr);
    utf8Content.resize(utf8_size);
    WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), &utf8Content[0], utf8_size, nullptr, nullptr);
}

bool convertFile(std::string& path)
{
    std::fstream stream(path.c_str());
    if (!stream.good() || stream.bad()) {
        return false;
    }

    if (hasFileBOM(stream))
    {
        return true;
    }
    std::string content;
    readFile(stream, content);
    std::string utf8Content;
    convertString(content, utf8Content);
    std::cout << "DEBUG:\n" << utf8Content << "DEBUG\n";
    return false;
}
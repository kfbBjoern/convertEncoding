#include "handleFiles.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <string_view>

#ifdef WIN32
#include "windows.h"
#endif

namespace fs = std::filesystem;

void  addFiles(std::vector< std::string >& files, std::string parameter, std::list<std::string> excludes)
{
    if (!std::filesystem::exists(parameter)) {
        std::cerr << "\t files does not exist :" << parameter << "\n";
        return;
    }

    if (fs::is_regular_file(parameter)) {
        if ( checkSingleFile(parameter, excludes)) {
            files.emplace_back(parameter);
        }
        return;
    }

    if (fs::is_directory(parameter)) {

        for(auto& p: fs::recursive_directory_iterator(parameter))
        {
            // demo_status(*it, it->symlink_status()); // use cached status from directory entry
            if (fs::is_regular_file(p)) {
                std::string file_name {p.path().string()};
                if ( checkSingleFile(file_name , excludes)) {
                    files.emplace_back(file_name);
                }
            }
        }
        return;
    }

    return;
}


bool checkSingleFile(std::string parameter, std::list<std::string> excludes)
{
    for (std::string& appendix : excludes) {
        fs::path file {parameter};
        if(file.extension() == appendix) {
            return false;
        }
    }
    return true;
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

bool readFile(std::fstream& stream, std::string& content)
{
    stream.imbue(std::locale("C"));
    stream.seekg(0, std::ios::end);   
    std::size_t length = stream.tellg();
    content.reserve(length);
    stream.seekg(0, std::ios::beg);

    content.assign((std::istreambuf_iterator<char>(stream)),
                std::istreambuf_iterator<char>());                
    return false;
}

void convertString(std::string& content, std::string& utf8Content)
{
#ifdef WIN32
    std::string codepage_str;
    int contentLength = static_cast <int> (content.length());
    int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, content.c_str(), contentLength, nullptr, 0);

    std::wstring utf16_str(size, '\0');
    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, content.c_str(), contentLength, &utf16_str[0], size);
    int utf16_strLength = static_cast <int> (utf16_str.length());

    int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_strLength, nullptr, 0, nullptr, nullptr);
    utf8Content.resize(utf8_size);
    WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_strLength, &utf8Content[0], utf8_size, nullptr, nullptr);
#else
    utf8Content = content;
#endif
}

void writeFile(std::fstream& stream, std::string& content)
{
  stream.imbue(std::locale("de_DE.utf8"));
  stream.seekg(0, std::ios::beg);

  stream << '\xEF' << '\xBB' << '\xBF'
          << content;
  return;
}

void convertFile(std::string& path)
{
    std::fstream stream(path.c_str());
    if (!stream.good() || stream.bad()) {
        throw std::runtime_error("Bad file");
    }

    if (hasFileBOM(stream))
    {
        return;
    }
    std::string content;
    if (readFile(stream, content)) {
        std::string utf8Content;
        convertString(content, utf8Content);
        writeFile(stream, utf8Content);
    }
}
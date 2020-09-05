#include "handleFiles.hpp"
#include <filesystem>
#include <iostream>


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
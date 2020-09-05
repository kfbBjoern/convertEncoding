#include <iostream>
#include <vector>
#include "handleOptions.hpp"
#include "handleFiles.hpp"

int main (int argc, char** argv)
{
    std::vector< std::string > filesToConvert;

    for (int i {1}; i < argc; ++i ) {
        if (!isStringOption(std::string(argv[i]))) {
            addFiles(filesToConvert, std::string(argv[i]));
        }
    }

    int counter {0};
    for (auto&& path : filesToConvert) {
        std::cout << ++counter <<".\t:" << path;
        if ( convertFile(path) ) 
        {
            std::cout << "....ok\n";
        }
        else {
            std::cout << "....ERROR\n";
        };
    }
    return 0;
}
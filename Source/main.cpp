#include <iostream>
#include <vector>
#include "handleOptions.hpp"
#include "handleFiles.hpp"
#include "version.hpp"


void print_usage()
{
    std::cout << PROJECT_NAME << " version " <<  VERSION <<"\n\n";
    std::cout << PROJECT_NAME << " [path] \n";
    std::cout << "=======================================================\n";
    std::cout << "path\tpath or file name to convert all files recursive \n ";
}

int main (int argc, char** argv)
{
    if (argc == 1) {
        print_usage();
    }

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
#include <iostream>
#include <vector>
#include "handleFiles.hpp"
#include "Options.hpp"
#include "version.hpp"
#include <map>
#include <variant>

void print_usage()
{
    std::cout << PROJECT_NAME << " version " <<  VERSION <<"\n\n";
    std::cout << PROJECT_NAME << " [path] --usage \n";
    std::cout << "=======================================================\n";
    std::cout << "path\tpath or file name to convert all files recursive \n ";
    std::cout << "--usage -u to print this \n ";
}


void managingErrors(int error)
{    std::cout << "\n" << "during the conversion " ;
    if (error > 0) {
        std::cout << error << "errors ocurred.";
    }
    else {
        std::cout << "no error ocurred.\n";
    }
}

int main (int argc, char** argv)
{
    int error = 0;
    Options my_options(argc, argv);

    if ((argc == 1) || (my_options.exists(std::string("usage")))) {
        print_usage();
    }

    std::vector< std::string > filesToConvert;

    for (auto& path : my_options.getUnhandledOptions() ) {
        addFiles(filesToConvert, path);
    }

    int counter {0};
    for (auto&& path : filesToConvert) {
        std::cout << "\n" << ++counter <<".\t:" << path;
        try {
            convertFile(path); 
        }
        catch(std::exception const& e)
        {
            std::cout << "Error: " << e.what();
            ++error;
        } 
    }
    managingErrors(error);
    return error;
}
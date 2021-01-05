#include <algorithm> 
#include <iostream>
#include <locale>
#include <vector>
#include "handleFiles.hpp"
#include "Options.hpp"
#include "version.hpp"
#include <map>
#include <string>
#include <variant>


void print_usage()
{
    std::cout << PROJECT_NAME << " version " <<  VERSION <<"\n\n";
    std::cout << PROJECT_NAME << " [path] --usage \n";
    std::cout << "=======================================================\n";
    std::cout << "path\tpath or file name to convert all files recursive \n ";
    std::cout << "--usage -u to print this \n ";
    std::cout << "-exclude list of file appendencies to exclude from converting i.e \"xls, pdf, xslm\" \n";
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

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void makeAppendix(std::string &s) {
    ltrim(s);
    rtrim(s);
    if ( s[0] != '.') {
        s = std::string(".") +s;
    }
}

std::list< std::string > splitString(std::string input) 
{
    std::list< std::string > output;
    while (!input.empty()) {
        std::size_t end = input.find(",", 0);
        if ((end != std::string::npos)) {
            std::string word {input.substr(0,end)};
            makeAppendix(word);
            input.erase(0, end+1);
            //std::cout << input << "|" <<  word << "|\n";
            output.emplace_back(word);
        }
        else {
            makeAppendix(input);
            output.emplace_back(input);
            //std::cout << "|" <<  input << "|\n";
            input.clear();
        }
    }
    return output;
}

int main (int argc, char** argv)
{
    int error = 0;
    Options my_options(argc, argv);

    if ((argc == 1) || (my_options.exists(std::string("usage")))) {
        print_usage();
    }

    std::vector< std::string > filesToConvert;
    std::string extens { my_options.getExtensionFor("exclude") };
    std::list< std::string > excludes { splitString(extens) };

    for (auto& path : my_options.getUnhandledOptions() ) {
        addFiles(filesToConvert, path, excludes);
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
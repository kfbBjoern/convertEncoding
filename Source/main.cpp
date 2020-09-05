#include <iostream>
#include <vector>
#include "handleOptions.hpp"

int main (int argc, char** argv)
{
    std::vector< std::string > paths;

    for (int i {1}; i < argc; ++i ) {
        if (!isStringOption(std::string(argv[i]))) {
            paths.emplace_back(argv[i]);
        }
    }

    int counter {0};
    for (auto&& path : paths) {
        std::cout << ++counter <<".\t:" << path << "\n";
    }
    return 0;
}
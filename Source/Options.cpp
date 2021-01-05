#include "Options.hpp"

#include <iostream>
#include <cstring>
 
Options::Options(int argc, char** argv)
{
    for (int i=1; i < argc ; ++i)
    {
        char *opt = argv[i];
        //std::cout << i << ". :" << opt;

        if ( opt[0] == '-') {
            //std::cout << " Option";
            if (opt[1] == '-') {
                std::list<OptionsInput>::const_iterator possible = equalsLongOption(opt);
                if (possible != PossibleOptions.cend()){
                    //std::cout << " long";
                    std::string extension("");
                    if (possible->RequiresExtension) {
                        extension = std::string(argv[++i]);
                    }
                    AllOptions.insert(std::pair< std::string, std::variant<int, std::string> >(possible->LongName, extension));
                }
                else {
                    std::cerr << "\n\t\tWrong long  Option:" << opt << "\n";
                }
            }
            else {
                std::list<OptionsInput>::const_iterator possible = equalsShortOption(opt);
                if (possible != PossibleOptions.cend()){
                    std::string extension("");
                    if (possible->RequiresExtension) {
                        extension = std::string(argv[++i]);
                    }
                    AllOptions.insert(std::pair< std::string, std::variant<int, std::string> >(possible->LongName, extension));
                }
                else {
                    std::cerr << "\n\t\tWrong short  Option:" << opt << "\n";
                }
            }
        }
        else {
            UnhandledOptions.emplace_back(opt);
            // std::cout << "No Option";
        }
        // std::cout << "\n";
    }
}

std::list<OptionsInput>::const_iterator Options::equalsLongOption(const char* opt) const
{
    std::string searched { opt};
    std::list<OptionsInput>::const_iterator OptionIterator;
    for (OptionIterator = PossibleOptions.cbegin(); OptionIterator != PossibleOptions.cend(); ++OptionIterator) {
        if (searched.find(OptionIterator->LongName)!=std::string::npos) {
            return OptionIterator;
        }
    }
    return PossibleOptions.cend();
}

std::list<OptionsInput>::const_iterator Options::equalsShortOption(const char* opt) const
{
    if (strlen(opt) == 2) {
        std::list<OptionsInput>::const_iterator OptionIterator;
        for (OptionIterator = PossibleOptions.cbegin(); OptionIterator != PossibleOptions.cend(); ++OptionIterator) {
            if ( OptionIterator->ShortName == opt[1]) {
                return OptionIterator;
            }
        }
    }
    return PossibleOptions.cend();
}

bool Options::exists(const std::string input) const
{
    std::map<std::string, std::variant<int, std::string> >::const_iterator found = AllOptions.find(input);
    if ( found != AllOptions.end()) {
        return true;
    }
    return false;
}

std::string Options::getExtensionFor(std::string long_name)
{
    std::string extension {""};
    if (exists(std::string(long_name))) {
        std::map<std::string, std::variant<int, std::string> >::const_iterator found = AllOptions.find(long_name);
        if (found != AllOptions.cend()) {
            if (std::holds_alternative<std::string>(found->second) ) {
                extension = std::get<std::string>(found->second);
            }
        }
    }
    return extension;
}

#include "handleOptions.hpp"

bool isStringOption(std::string parameter)
{
    if (parameter[0] == '-') 
    {
        return true;
    }
    else 
    {
        return false;
    }
}
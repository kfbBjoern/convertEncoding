#ifndef HANDLE_FILES
#define HANDLE_FILES

#include <list>
#include <string>
#include <vector>


void  addFiles(std::vector< std::string >& files, std::string parameter, std::list<std::string> excludes);

void convertFile(std::string& path);

bool checkSingleFile(std::string parameter, std::list<std::string> excludes);

#endif // HANDLE_FILES
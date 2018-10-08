#ifndef FILE_H
#define FILE_H

#include <string>

class File {
public:
    static int GetContent(const std::string& name, std::string& result);
};

#endif
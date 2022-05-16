
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

class StringUtils{
public:
    static std::vector<std::string> split (std::string s, std::string delimiter);
};

#endif
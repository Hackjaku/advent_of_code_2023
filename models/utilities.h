#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Utilities {
public:
    std::vector<std::string> ParseInput(std::string);
    bool Replace(std::string &, const std::string &, const std::string &);
};

#endif // UTILITIES_H
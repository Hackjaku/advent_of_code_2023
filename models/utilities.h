#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Utilities {
public:
    std::vector<std::string> ParseInput(std::string);
    bool ReplaceFirst(std::string &, const std::string &, const std::string &);
    void ReplaceAll(std::string &str, const std::string& from, const std::string& to);
};

#endif // UTILITIES_H
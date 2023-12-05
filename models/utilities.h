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
    int ReplaceAll(std::string &str, const std::string& from, const std::string& to);
    std::vector<std::string> Split(std::string, std::string);
};

#endif // UTILITIES_H
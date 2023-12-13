#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/integer/common_factor.hpp>

class Utilities {
public:
    static std::vector<std::string> ParseInput(std::string);
    static bool ReplaceFirst(std::string &, const std::string &, const std::string &);
    static int ReplaceAll(std::string &str, const std::string& from, const std::string& to);
    static std::vector<std::string> Split(std::string, std::string);
    static long LeastCommonMultiple(std::vector<long>);
    static bool AreMatchingRows(const std::vector<std::string> &, int, int);
    static bool AreMatchingColumns(const std::vector<std::string> &, int, int);
    static int AreDifferentRows(const std::vector<std::string> &, int, int);
    static int AreDifferentColumns(const std::vector<std::string> &, int, int);
};

#endif // UTILITIES_H
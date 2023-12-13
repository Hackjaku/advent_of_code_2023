#include "utilities.h"

std::vector<std::string> Utilities::ParseInput(std::string path) {
    std::vector<std::string> lines;
    std::string line;
    std::fstream data(path, std::ios::in);

    while (std::getline(data, line)) {
        lines.push_back(line);
    }

    return lines;
}

bool Utilities::ReplaceFirst(std::string &str, const std::string &from, const std::string &to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos) return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int Utilities::ReplaceAll(std::string &str, const std::string& from, const std::string& to) {
    int count = 0;
    while (ReplaceFirst(str, from, to)) {
        ++count;
    }
    return count;
}

std::vector<std::string> Utilities::Split(std::string str, std::string delimiter) {
    std::vector<std::string> parts;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        parts.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    parts.push_back(str);
    return parts;
}

long Utilities::LeastCommonMultiple(std::vector<long> numbers) {
    long result = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) {
        result = boost::integer::lcm(result, numbers[i]);
    }
    return result;
}

bool Utilities::AreMatchingColumns(const std::vector<std::string> &pattern, int col1, int col2) {
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i][col1] != pattern[i][col2]) {
            return false;
        }
    }
    return true;
}

bool Utilities::AreMatchingRows(const std::vector<std::string> &pattern, int row1, int row2) {
    return pattern[row1] == pattern[row2];
}

int Utilities::AreDifferentColumns(const std::vector<std::string> &pattern, int col1, int col2) {
    int count = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i][col1] != pattern[i][col2]) {
            ++count;
        }
    }
    return count;
}

int Utilities::AreDifferentRows(const std::vector<std::string> &pattern, int row1, int row2) {
    int count = 0;
    for (int i = 0; i < pattern[row1].size(); ++i) {
        if (pattern[row1][i] != pattern[row2][i]) {
            ++count;
        }
    }
    return count;
}
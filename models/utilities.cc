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

bool Utilities::Replace(std::string &str, const std::string &from, const std::string &to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos) return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
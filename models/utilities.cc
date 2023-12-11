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
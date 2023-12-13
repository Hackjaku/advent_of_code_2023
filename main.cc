#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "models/utilities.h"

bool IsMirrorColumn(const std::vector<std::string> &pattern, int mirror_column, int test_column) {
    short distance = std::abs(mirror_column - test_column);

    if (test_column < 0 || test_column + ((distance * 2) - 1) >= pattern[0].size()) {
        return true;
    } else {
        return IsMirrorColumn(pattern, mirror_column, test_column - 1) &&
            Utilities::AreMatchingColumns(pattern, test_column, test_column + ((distance * 2) - 1));
    }
}

bool IsMirrorRow(const std::vector<std::string> &pattern, int mirror_row, int test_row) {
    short distance = std::abs(mirror_row - test_row);

    if (test_row < 0 || test_row + ((distance * 2) - 1) >= pattern.size()) {
        return true;
    } else {
        return IsMirrorRow(pattern, mirror_row, test_row - 1) &&
            Utilities::AreMatchingRows(pattern, test_row, test_row + ((distance * 2) - 1));
    }
}

int FindMirrorRow(const std::vector<std::string> &pattern) {
    for (int i = 1; i < pattern.size(); ++i) {
        if (IsMirrorRow(pattern, i, i - 1)) {
            return i;
        }
    }
    return -1;
}

int FindMirrorColumn(const std::vector<std::string> &pattern) {
    for (int i = 1; i < pattern[0].size(); ++i) {
        if (IsMirrorColumn(pattern, i, i - 1)) {
            return i;
        }
    }
    return -1;
}

int main() {
    std::vector<std::string> lines = Utilities::ParseInput("../inputs/13.txt");

    int sum = 0;

    for (int i = 0; i < lines.size(); ++i) {

        std::vector<std::string> pattern;

        // while lines[i] is not empty
        while (lines[i].size() > 0) {
            pattern.push_back(lines[i]);
            ++i;
        }

        // do stuff...

        int mirror = FindMirrorColumn(pattern);
        if (mirror != -1) {
            sum += mirror;
        } else {
            mirror = FindMirrorRow(pattern);
            if (mirror != -1) {
                sum += 100 * mirror;
            } else {
                std::cout << "No mirror found" << std::endl;
            }
        }

        // ? end
        pattern.clear();
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
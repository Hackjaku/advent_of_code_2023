#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

#include "models/utilities.h"

bool IsFixableMirroredColumn(const std::vector<std::string> &pattern, int mirror_column, int test_column, bool &fixed) {
    short distance = std::abs(mirror_column - test_column);

    if (test_column < 0 || test_column + ((distance * 2) - 1) >= pattern[0].size()) {
        return true;
    } else {
        int differences = Utilities::AreDifferentColumns(pattern, test_column, test_column + ((distance * 2) - 1));
        if (differences == 1) {
            fixed = true;
            return IsFixableMirroredColumn(pattern, mirror_column, test_column - 1, fixed);
        } else if (differences == 0) {
            return IsFixableMirroredColumn(pattern, mirror_column, test_column - 1, fixed);
        } else {
            return false;
        }
    }

}

bool IsMirrorColumn(const std::vector<std::string> &pattern, int mirror_column, int test_column) {
    short distance = std::abs(mirror_column - test_column);

    if (test_column < 0 || test_column + ((distance * 2) - 1) >= pattern[0].size()) {
        return true;
    } else {
        return IsMirrorColumn(pattern, mirror_column, test_column - 1) &&
            Utilities::AreMatchingColumns(pattern, test_column, test_column + ((distance * 2) - 1));
    }
}

bool IsFixableMirroredRow(const std::vector<std::string> &pattern, int mirror_row, int test_row, bool &fixed) {
    short distance = std::abs(mirror_row - test_row);

    if (test_row < 0 || test_row + ((distance * 2) - 1) >= pattern.size()) {
        return true;
    } else {
        int differences = Utilities::AreDifferentRows(pattern, test_row, test_row + ((distance * 2) - 1));
        if (differences == 1) {
            fixed = true;
            return IsFixableMirroredRow(pattern, mirror_row, test_row - 1, fixed);
        } else if (differences == 0) {
            return IsFixableMirroredRow(pattern, mirror_row, test_row - 1, fixed);
        } else {
            return false;
        }
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

int FindFixableMirrorRow(const std::vector<std::string> &pattern) {
    for (int i = 1; i < pattern.size(); ++i) {
        bool fixed = false;
        if (IsFixableMirroredRow(pattern, i, i - 1, fixed)) {
            if (fixed) {
                return i;
            }
        }
    }
    return -1;
}

int FindFixableMirrorColumn(const std::vector<std::string> &pattern) {
    for (int i = 1; i < pattern[0].size(); ++i) {
        bool fixed = false;
        if (IsFixableMirroredColumn(pattern, i, i - 1, fixed)) {
            if (fixed) {
                return i;
            }
        }
    }
    return -1;
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();


    std::vector<std::string> lines = Utilities::ParseInput("../inputs/13.txt");

    int sum = 0;
    int sum2 = 0;

    for (int i = 0; i < lines.size(); ++i) {

        std::vector<std::string> pattern;

        // while lines[i] is not empty
        while (lines[i].size() > 0) {
            pattern.push_back(lines[i]);
            ++i;
        }

        // do stuff...

        // ! ---- PART 1 ----
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
        // ! ---- PART 1 END ----



        // ! ---- PART 2 ----

        int fixable_mirror = FindFixableMirrorRow(pattern);
        if (fixable_mirror != -1) {
            sum2 += 100 * fixable_mirror;
        } else {
            fixable_mirror = FindFixableMirrorColumn(pattern);
            if (fixable_mirror != -1) {
                sum2 += fixable_mirror;
            } else {
                std::cout << "No fixable mirror found" << std::endl;
            }
        }
        // ! ---- PART 2 END ----

        pattern.clear();
    }

    std::cout << "Part 1: " << sum << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "models/utilities.h"

int main() {
    std::vector<std::string> lines = Utilities::ParseInput("../inputs/13.txt");

    for (int i = 0; i < lines.size(); ++i) {

        std::vector<std::string> pattern;

        // while lines[i] is not empty
        while (lines[i].size() > 0) {
            pattern.push_back(lines[i]);
            ++i;
        }

        // do stuff...

        int mirror_column = FindMirrorColumn(pattern);
        std::cout << "Mirror column: " << mirror_column << std::endl;

        // ? end
        pattern.clear();
    }

    return 0;
}
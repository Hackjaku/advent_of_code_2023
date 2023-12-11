#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

#include "./models/utilities.h"


int main() {

    auto start = std::chrono::high_resolution_clock::now();

    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/10.txt");

    // find the S in map
    std::pair<int, int> start_point; // row, column

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'S') {
                start_point = std::make_pair(i, j);
            }
        }
    }

    std::cout << "Start point: " << start_point.first << ", " << start_point.second << std::endl;


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}
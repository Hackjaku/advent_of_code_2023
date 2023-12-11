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
    std::vector<std::string> lines = utils.ParseInput("../inputs/09.txt");

    std::vector<std::vector<int>> histories;
    // each line is in the form: 10 13 16 21 30 ...
    for (auto line : lines) {
        std::vector<std::string> numbers;
        boost::split(numbers, line, boost::is_any_of(" "));
        std::vector<int> history;
        for (auto number : numbers) {
            history.push_back(std::stoi(number));
        }
        histories.push_back(history);
    }

    std::vector<std::vector<int>> differences;
    std::vector<int> difference;

    std::vector<int> sums;
    std::vector<int> sums_part2;

    for (auto history : histories) {
        // clear differences
        differences.clear();
        differences.push_back(history);

        // clear difference
        difference.clear();

        // if difference is empty or any value in difference is not zero
        while (difference.empty() || std::any_of(difference.begin(), difference.end(), [](int i) { return i != 0; })) {
            difference.clear();
            for (int i = 0; i < differences[differences.size() - 1].size() - 1; i++) {
                difference.push_back(differences[differences.size() - 1][i + 1] - differences[differences.size() - 1][i]);
            }
            differences.push_back(difference);
        }


        // if difference values are all zero
        int sum = 0;
        // sum every latest value in differences
        for (auto difference : differences) {
            sum += difference[difference.size() - 1];
        }
        sums.push_back(sum);


        int extrpolated_value = 0;
        for (int i = differences.size() - 1; i >= 0; i--) {
            extrpolated_value = differences[i][0] - extrpolated_value;
        }

        sums_part2.push_back(extrpolated_value);

        // clear differences
        differences.clear();
    }

    long total = 0;
    for (auto sum : sums) {
        total += sum;
    }

    long total_part2 = 0;
    for (auto sum : sums_part2) {
        total_part2 += sum;
    }

    std::cout << "Total: " << total << std::endl;
    std::cout << "Total part 2: " << total_part2 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

#include "models/utilities.h"

void MoveUp(std::vector<std::string> &map, const int &row) {
    // move the round boulders up one place
    if (row == 0) {
        throw std::invalid_argument("Cannot move up the top row");
    }

    for (int i = 0; i < map[row].size(); ++i) {
        if (map[row][i] == 'O' && map[row - 1][i] == '.') {
            map[row][i] = '.';
            map[row - 1][i] = 'O';
        }
    }
}

void MoveDown(std::vector<std::string> &map, const int &row) {
    // move the round boulders down one place
    if (row == map.size() - 1) {
        throw std::invalid_argument("Cannot move down the bottom row");
    }

    for (int i = 0; i < map[row].size(); ++i) {
        if (map[row][i] == 'O' && map[row + 1][i] == '.') {
            map[row][i] = '.';
            map[row + 1][i] = 'O';
        }
    }
}

void MoveLeft(std::vector<std::string> &map, const int &col) {
    // move the round boulders left one place
    if (col == 0) {
        throw std::invalid_argument("Cannot move left the leftmost column");
    }

    for (int i = 0; i < map.size(); ++i) {
        if (map[i][col] == 'O' && map[i][col - 1] == '.') {
            map[i][col] = '.';
            map[i][col - 1] = 'O';
        }
    }
}

void MoveRight(std::vector<std::string> &map, const int &col) {
    // move the round boulders right one place
    if (col == map[0].size() - 1) {
        throw std::invalid_argument("Cannot move right the rightmost column");
    }

    for (int i = 0; i < map.size(); ++i) {
        if (map[i][col] == 'O' && map[i][col + 1] == '.') {
            map[i][col] = '.';
            map[i][col + 1] = 'O';
        }
    }
}

void TiltEast(std::vector<std::string> &map) {
    for (int i = map[0].size() - 2; i >= 0; --i) {
        for (int j = i; j <= map[i].size() - 2; ++j) {
            MoveRight(map, j);
        }
    }
}

void TiltWest(std::vector<std::string> &map) {
    for (int i = 1; i < map[0].size(); ++i) {
        for (int j = i; j > 0; --j) {
            MoveLeft(map, j);
        }
    }
}

void TiltSouth(std::vector<std::string> &map) {
    for (int i = map.size() - 2; i >= 0; --i) {
        for (int j = i; j <= map[i].size() - 2; ++j) {
            MoveDown(map, j);
        }
    }
}

void TiltNorth(std::vector<std::string> &map) {
    for (int i = 1; i < map.size(); ++i) {
        for (int j = i; j > 0; --j) {
            MoveUp(map, j);
        }
    }
}

int CalculateNorthWeight(const std::vector<std::string> &map) {
    int weight = 0;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 'O') {
                // distance from south
                weight += std::abs((int)i - (int)(map.size()));
            }
        }
    }

    return weight;
}

void PrintMap(const std::vector<std::string> &map) {
    for (int i = 0; i < map.size(); ++i) {
        std::cout << map[i] << std::endl;
    }
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> lines = Utilities::ParseInput("../inputs/14.txt");

    for (int i = 0; i < 3; ++i) {
        TiltNorth(lines);
        TiltWest(lines);
        TiltSouth(lines);
        TiltEast(lines);

        PrintMap(lines);

        std::cout << std::endl;
    }


    std::cout << std::endl << "Part 1: " << CalculateNorthWeight(lines) << std::endl << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}
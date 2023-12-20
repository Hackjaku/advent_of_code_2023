#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

#include "models/utilities.h"


struct ActiveMirror {
    int x, y;
    int direction;

    bool operator == (const ActiveMirror &other) const {
        return (x == other.x && y == other.y && direction == other.direction);
    }
};


void MoveBeamUp(std::vector<std::string> &grid, int x, int y, std::queue<ActiveMirror> &activeMirrors, std::vector<ActiveMirror> &visitedMirrors) {
    if (y < 0) {
        return;
    }

    while ((grid[y][x] == '.' || grid[y][x] == '#')) {
        grid[y][x] = '#';
        --y;
        if (y < 0) {
            return;
        }
    }

    switch (grid[y][x]) {
        case '/': {
            ActiveMirror mirror = {x, y, 0};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '\\': {
            ActiveMirror mirror = {x, y, 2};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '-': {
            ActiveMirror m1 = {x, y, 0};
            ActiveMirror m2 = {x, y, 2};

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m1) == visitedMirrors.end()) {
                visitedMirrors.push_back(m1);
                activeMirrors.push(m1);
            }

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m2) == visitedMirrors.end()) {
                visitedMirrors.push_back(m2);
                activeMirrors.push(m2);
            }
            break;
        }

        case '|': {
            ActiveMirror mirror = {x, y, 3};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
    }
}

void MoveBeamDown(std::vector<std::string> &grid, int x, int y, std::queue<ActiveMirror> &activeMirrors, std::vector<ActiveMirror> &visitedMirrors) {
    if (y >= grid.size()) {
        return;
    }

    while ((grid[y][x] == '.' || grid[y][x] == '#')) {
        grid[y][x] = '#';
        ++y;
        if (y >= grid.size()) {
            return;
        }
    }

    switch (grid[y][x]) {
        case '/': {
            ActiveMirror mirror = {x, y, 2};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '\\': {
            ActiveMirror mirror = {x, y, 0};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '-': {
            ActiveMirror m1 = {x, y, 0};
            ActiveMirror m2 = {x, y, 2};

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m1) == visitedMirrors.end()) {
                visitedMirrors.push_back(m1);
                activeMirrors.push(m1);
            }

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m2) == visitedMirrors.end()) {
                visitedMirrors.push_back(m2);
                activeMirrors.push(m2);
            }
            break;
        }
        case '|': {
            ActiveMirror mirror = {x, y, 1};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
    }
}

void MoveBeamLeft(std::vector<std::string> &grid, int x, int y, std::queue<ActiveMirror> &activeMirrors, std::vector<ActiveMirror> &visitedMirrors) {

    if (x < 0) {
        return;
    }

    while ((grid[y][x] == '.' || grid[y][x] == '#')) {
        grid[y][x] = '#';
        --x;
        if (x < 0) {
            return;
        }
    }

    switch (grid[y][x]) {
        case '/': {
            ActiveMirror mirror = {x, y, 1};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '\\': {
            ActiveMirror mirror = {x, y, 3};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '-': {
            ActiveMirror mirror = {x, y, 2};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '|': {
            ActiveMirror m1 = {x, y, 1};
            ActiveMirror m2 = {x, y, 3};

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m1) == visitedMirrors.end()) {
                visitedMirrors.push_back(m1);
                activeMirrors.push(m1);
            }

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m2) == visitedMirrors.end()) {
                visitedMirrors.push_back(m2);
                activeMirrors.push(m2);
            }
            break;
        }
    }
}

void MoveBeamRight(std::vector<std::string> &grid, int x, int y, std::queue<ActiveMirror> &activeMirrors, std::vector<ActiveMirror> &visitedMirrors) {

    if (x >= grid[y].size()) {
        return;
    }

    while ((grid[y][x] == '.' || grid[y][x] == '#')) {
        grid[y][x] = '#';
        ++x;
        if (x >= grid[y].size()) {
            return;
        }
    }

    switch (grid[y][x]) {
        case '/': {
            ActiveMirror mirror = {x, y, 3};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '\\': {
            ActiveMirror mirror = {x, y, 1};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) != visitedMirrors.end()) {
                // already visited this mirror with this direction
                return;
            }
            visitedMirrors.push_back(mirror);
            activeMirrors.push(mirror);
            break;
        }
        case '-': {
            ActiveMirror mirror = {x, y, 0};
            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), mirror) == visitedMirrors.end()) {
                visitedMirrors.push_back(mirror);
                activeMirrors.push(mirror);
            }
            break;
        }
        case '|': {
            ActiveMirror m1 = {x, y, 1};
            ActiveMirror m2 = {x, y, 3};

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m1) == visitedMirrors.end()) {
                visitedMirrors.push_back(m1);
                activeMirrors.push(m1);
            }

            if (std::find(visitedMirrors.begin(), visitedMirrors.end(), m2) == visitedMirrors.end()) {
                visitedMirrors.push_back(m2);
                activeMirrors.push(m2);
            }
            break;
        }
    }
}

void PrintGrid(const std::vector<std::string> &grid) {
    for (const std::string &line : grid) {
        std::cout << line << std::endl;
    }
}

void CleanGridFromMirrors(std::vector<std::string> &grid, const std::vector<ActiveMirror> &visitedMirrors) {
    for (const ActiveMirror &mirror : visitedMirrors) {
        grid[mirror.y][mirror.x] = '#';
    }

    // remove all mirrors (leave only # for beams and . for empty space)
    for (std::string &line : grid) {
        for (char &c : line) {
            if (c == '/' || c == '\\' || c == '-' || c == '|') {
                c = '.';
            }
        }
    }
}

int CountBeams(const std::vector<std::string> &grid) {
    int count = 0;
    for (const std::string &line : grid) {
        for (char c : line) {
            if (c == '#') {
                ++count;
            }
        }
    }
    return count;
}



int main() {

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> lines = Utilities::ParseInput("../inputs/16.txt");

    std::vector<ActiveMirror> visitedMirrors;
    std::queue<ActiveMirror> activeMirrors;

    std::vector<ActiveMirror> startingMirrors;

    for (int i = 0; i < lines.size(); ++i) {
        startingMirrors.push_back({-1, i, 0}); // left column
        startingMirrors.push_back({(int)lines[0].size(), i, 2}); // right column
    }

    for (int i = 0; i < lines[0].size(); ++i) {
        startingMirrors.push_back({i, -1, 1}); // top row
        startingMirrors.push_back({i, (int)lines.size(), 3}); // bottom row
    }

    std::vector<std::string> grid = lines;

    std::vector<int> beamCounts;


    for (const ActiveMirror &mirror : startingMirrors) {
        activeMirrors.push(mirror);
        grid = lines;
        while (!activeMirrors.empty()) {
            ActiveMirror current = activeMirrors.front();
            activeMirrors.pop();

            switch (current.direction) {
                case 0: {
                    MoveBeamRight(grid, current.x + 1, current.y, activeMirrors, visitedMirrors);
                    break;
                }
                case 1: {
                    MoveBeamDown(grid, current.x, current.y + 1, activeMirrors, visitedMirrors);
                    break;
                }
                case 2: {
                    MoveBeamLeft(grid, current.x - 1, current.y, activeMirrors, visitedMirrors);
                    break;
                }
                case 3: {
                    MoveBeamUp(grid, current.x, current.y - 1, activeMirrors, visitedMirrors);
                    break;
                }
            }
        }
        CleanGridFromMirrors(grid, visitedMirrors);
        beamCounts.push_back(CountBeams(grid));
        visitedMirrors.clear();
    }

    std::cout << "Part 1: " << beamCounts[0] << std::endl;
    // part 2 is max of beamCounts
    std::cout << "Part 2: " << *std::max_element(beamCounts.begin(), beamCounts.end()) << std::endl;


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}
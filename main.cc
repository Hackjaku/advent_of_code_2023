#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

#include "./models/utilities.h"

struct Module {
    bool outSignal;
    virtual void Execute();
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

struct FlipFlop : public Module {
};

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/20.txt");


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Clock time: " << duration.count() << " us" << std::endl;

    return 0;
}

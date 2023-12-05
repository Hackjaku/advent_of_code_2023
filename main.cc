#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "models/utilities.h"


int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/04.txt");

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <boost/algorithm/string.hpp>

#include "models/utilities.h"

int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/05.txt");

    return 0;
}
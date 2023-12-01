#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../models/utilities.h"

using namespace std;


int main() {

    Utilities utils;
    vector<string> lines = utils.ParseInput("../inputs/01.txt");

    for (int i = 0; i < lines.size(); i++) {

        utils.ReplaceAll(lines[i], "one", "o1e");
        utils.ReplaceAll(lines[i], "two", "t2o");
        utils.ReplaceAll(lines[i], "three", "t3e");
        utils.ReplaceAll(lines[i], "four", "f4r");
        utils.ReplaceAll(lines[i], "five", "f5e");
        utils.ReplaceAll(lines[i], "six", "s6x");
        utils.ReplaceAll(lines[i], "seven", "s7n");
        utils.ReplaceAll(lines[i], "eight", "e8t");
        utils.ReplaceAll(lines[i], "nine", "n9e");
    }

    string line;
    int sum = 0;
    char dec, unit;

    for (auto line : lines) {
        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                dec = line[i];
                break;
            }
        }
        for (int i = line.length() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                unit = line[i];
                break;
            }
        }
        stringstream ss;
        ss << dec << unit;

        sum += stoi(ss.str());
    }

    cout << sum << endl;
}
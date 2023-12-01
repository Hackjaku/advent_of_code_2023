#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "models/utilities.h"

using namespace std;


int main() {

    Utilities utils;
    vector<string> lines = utils.ParseInput("../inputs/01.txt");

    for (int i = 0; i < lines.size(); i++) {

        utils.Replace(lines[i], "one", "o1e");
        utils.Replace(lines[i], "two", "t2o");
        utils.Replace(lines[i], "three", "t3e");
        utils.Replace(lines[i], "four", "f4r");
        utils.Replace(lines[i], "five", "f5e");
        utils.Replace(lines[i], "six", "s6x");
        utils.Replace(lines[i], "seven", "s7n");
        utils.Replace(lines[i], "eight", "e8t");
        utils.Replace(lines[i], "nine", "n9e");
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
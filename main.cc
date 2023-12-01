#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    fstream data("../inputs/01.txt", ios::in);

    string line;
    while (getline(data, line)) {
        cout << line << endl;
    }
}
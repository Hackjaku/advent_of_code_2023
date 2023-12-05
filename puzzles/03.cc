#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "../models/utilities.h"

class NumberGear {
private :
    int number;
    int position;
public:
    NumberGear(int number, int position) {
        this->number = number;
        this->position = position;
    }
    inline int GetNumber() { return this->number; }
    inline int GetPosition() { return this->position; }
};

int ExtractNumber(std::string matrix, int position, int &number) {

    if (!isdigit(matrix[position])) {
        number = -1;
        return 1;
    }

    std::string numberString = "";
    while (isdigit(matrix[position])) {
        numberString += matrix[position];
        position++;
    }
    std::stringstream ss(numberString);
    ss >> number;
    return numberString.size();
}

bool IsGear(char symbol) {
    if (symbol == '*') {
        return true;
    } else {
        return false;
    }
}

bool IsSymbol(char symbol) {
    if (!isdigit(symbol) && symbol != '.') {
        return true;
    } else {
        return false;
    }
}

bool TouchesSymbols(std::string matrix, int position, int row_size, int numer_size) {
    for (int i = 0; i < numer_size; i++) {
        // top right
        int check_position = position - row_size + i + 1;
        if (check_position >= 0 && IsSymbol(matrix[check_position])) {
            return true;
        }

        // top left
        check_position = position - row_size + i - 1;
        if (check_position >= 0 && IsSymbol(matrix[check_position])) {
            return true;
        }

        // bottom right
        check_position = position + row_size + i + 1;
        if (check_position < matrix.size() && IsSymbol(matrix[check_position])) {
            return true;
        }

        // bottom left
        check_position = position + row_size + i - 1;
        if (check_position < matrix.size() && IsSymbol(matrix[check_position])) {
            return true;
        }

        // top
        check_position = position + i - row_size;
        if (check_position >= 0 && IsSymbol(matrix[check_position])) {
            return true;
        }

        // bottom
        check_position = position + i + row_size;
        if (check_position < matrix.size() && IsSymbol(matrix[check_position])) {
            return true;
        }

        // left
        check_position = position + i - 1;
        if (check_position >= 0 && IsSymbol(matrix[check_position])) {
            return true;
        }

        // right
        check_position = position + i + 1;
        if (check_position < matrix.size() && IsSymbol(matrix[check_position])) {
            return true;
        }

    }
    return false;
}

bool TouchesGear(std::string matrix, int position, int row_size, int numer_size, int &gear_position) {
    for (int i = 0; i < numer_size; i++) {
        // top right
        int check_position = position - row_size + i + 1;
        if (check_position >= 0 && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // top left
        check_position = position - row_size + i - 1;
        if (check_position >= 0 && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // bottom right
        check_position = position + row_size + i + 1;
        if (check_position < matrix.size() && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // bottom left
        check_position = position + row_size + i - 1;
        if (check_position < matrix.size() && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // top
        check_position = position + i - row_size;
        if (check_position >= 0 && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // bottom
        check_position = position + i + row_size;
        if (check_position < matrix.size() && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // left
        check_position = position + i - 1;
        if (check_position >= 0 && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

        // right
        check_position = position + i + 1;
        if (check_position < matrix.size() && IsGear(matrix[check_position])) {
            gear_position = check_position;
            return true;
        }

    }
    gear_position = -1;
    return false;
}

std::string StringifyMatrix(std::vector<std::string> lines) {
    std::string matrix = "";
    for (int i = 0; i < lines.size(); i++) {
        matrix += lines[i];
    }
    return matrix;
}

int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/03.txt");

    int row = 0;
    int col = 0;
    int number = 0;
    int advance = 0;

    std::string matrixString = StringifyMatrix(lines);
    double sum = 0;

    std::vector<NumberGear> numberGears;
    int gear_position = 0;

    for (int i = 0; i < matrixString.size(); i += advance) {
        advance = ExtractNumber(matrixString, i, number);

        if (number == -1) {
            continue;
        }
        // bool touchesSymbols = TouchesSymbols(matrixString, i, lines[0].size(), advance);
        bool touchesGears = TouchesGear(matrixString, i, lines[0].size(), advance, gear_position);

        if (touchesGears) {
            numberGears.push_back(NumberGear(number, gear_position));
        }

        // if (touchesSymbols) {
        //     sum += number;
        // }
    }

    // sort by position
    std::sort(numberGears.begin(), numberGears.end(), [](NumberGear a, NumberGear b) {
        return a.GetPosition() < b.GetPosition();
    });

    // if the number has the same position as the previous number, multiply together
    for (int i = 0; i < numberGears.size() - 1; i++) {
        if (numberGears[i].GetPosition() == numberGears[i + 1].GetPosition()) {
            sum += numberGears[i].GetNumber() * numberGears[i + 1].GetNumber();
        }
    }

    std::cout  << std::fixed << "Sum: " << sum << std::endl;


    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <boost/algorithm/string.hpp>

#include "models/utilities.h"

class Card {
private:
    int id;
    std::vector<int> winning_numbers;
    std::vector<int> numbers;
    int copies;

public:
    Card(std::vector<int> winning_numbers, std::vector<int> numbers, int id) {
        this->winning_numbers = winning_numbers;
        this->numbers = numbers;
        this->id = id;
        this->copies = 1;
    }

    inline std::vector<int> GetWinningNumbers() { return this->winning_numbers; }
    inline std::vector<int> GetNumbers() { return this->numbers; }
    inline int GetId() { return this->id; }
    inline int GetCopies() { return this->copies; }
    inline void AddCopies(int copies) { this->copies += copies; }
};

int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/04.txt");

    std::vector<Card> cards;

    for (auto line : lines) {
        // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53

        // get the int between "Card " and ":"
        int id = std::stoi(line.substr(line.find("Card ") + 5, line.find(":") - line.find("Card ") - 5));

        // remove the part before the colon
        line = line.substr(line.find(":") + 2);

        // split the line into two parts, before and after the pipe
        std::vector<std::string> parts;
        boost::split(parts, line, boost::is_any_of("|"));

        std::vector<std::string> winning_numbers_str;
        std::vector<std::string> numbers_str;

        // split the first part into winning numbers
        boost::split(numbers_str, parts[0], boost::is_any_of(" "));
        // remove empty strings
        numbers_str.erase(std::remove(numbers_str.begin(), numbers_str.end(), ""), numbers_str.end());

        // split the second part into numbers
        boost::split(winning_numbers_str, parts[1], boost::is_any_of(" "));
        // remove empty strings
        winning_numbers_str.erase(std::remove(winning_numbers_str.begin(), winning_numbers_str.end(), ""), winning_numbers_str.end());

        std::vector<int> winning_numbers;
        std::vector<int> numbers;

        // convert the winning numbers to integers
        for (auto winning_number_str : winning_numbers_str) {
            winning_numbers.push_back(std::stoi(winning_number_str));
        }

        // convert the numbers to integers
        for (auto number_str : numbers_str) {
            numbers.push_back(std::stoi(number_str));
        }

        // create a card
        Card card(winning_numbers, numbers, id);
        cards.push_back(card);
    }

    // for each card, check how many winning numbers it has
    int sum = 0;
    int j = 0;
    for (int j = 0; j < cards.size(); ++j) {
        int count = 0;
        for (auto number : cards[j].GetNumbers()) {
            for (int i = 0; i < cards[j].GetWinningNumbers().size(); i++) {
                if (number == cards[j].GetWinningNumbers()[i]) {
                    count++;
                    break;
                }
            }
        }

        for (int i = 1; i <= count; ++i) {
            cards[j+i].AddCopies(cards[j].GetCopies());
        }
    }

    for (auto card : cards) {
        sum += card.GetCopies();
    }

    std::cout << sum << std::endl;

    return 0;
}
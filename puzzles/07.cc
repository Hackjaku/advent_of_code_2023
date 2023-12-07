#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "../models/utilities.h"

class Hand {
// A hand of cards
// A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, or K
private:
    std::string cards_str;
    std::vector<int> cards;
    int rank;
    int score;
    void calculate_rank_nojoker();
    void calculate_rank_joker();
    bool compare_nojoker(const Hand& hand) const;
    bool compare_joker(const Hand& hand) const;
public:
    void add_card(char);
    void calculate_rank(bool joker);
    inline void set_score(int score) { this->score = score; }
    inline void set_cards_str(std::string cards_str) { this->cards_str = cards_str; }
    inline std::string get_cards_str() { return this->cards_str; }
    inline int get_score() { return this->score; }
    inline int get_rank() { return this->rank; }
    bool operator < (const Hand& hand) const {
        return this->compare_nojoker(hand);
    }
    bool operator << (const Hand& hand) const {
        return this->compare_joker(hand);
    }
};

int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/07.txt");

    std::vector<Hand> hands;

    for (auto line : lines) {
        // split by the space
        std::vector<std::string> parts;
        boost::split(parts, line, boost::is_any_of(" "));

        // create a hand
        Hand hand;
        // second part is the score
        int score = std::stoi(parts[1]);
        hand.set_score(score);

        // first part is a string of cards
        std::string cards = parts[0];
        for (int i = 0; i < cards.size(); i++) {
            hand.add_card(cards[i]);
        }

        // set the cards string
        hand.set_cards_str(cards);

        // calculate the rank
        hand.calculate_rank(true);

        // add to the list
        hands.push_back(hand);
    }

    // sort the hands
    // std::sort(hands.begin(), hands.end());

    // sort the hands using the joker operator <<
    std::sort(hands.begin(), hands.end(), [](const Hand& a, const Hand& b) {
        return a << b;
    });

    int sum = 0;

    for (int i = 0; i < hands.size(); i++) {
        std::cout << hands[i].get_cards_str() << " " << hands[i].get_rank() << std::endl;
        sum += hands[i].get_score() * (i + 1);
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

void Hand::add_card(char card) {
    // Add a card to the hand
    // A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, or K
    switch (card) {
        case 'A':
            cards.push_back(14);
            break;
        case 'T':
            cards.push_back(10);
            break;
        case 'J':
            cards.push_back(11);
            break;
        case 'Q':
            cards.push_back(12);
            break;
        case 'K':
            cards.push_back(13);
            break;
        default:
            cards.push_back(card - '0');
            break;
    }
}

void Hand::calculate_rank(bool joker) {
    if (joker) {
        calculate_rank_joker();
    } else {
        calculate_rank_nojoker();
    }
}

void Hand::calculate_rank_joker() {

    if (this->cards_str == "JA6A3") {
        std::cout << "JA6A3" << std::endl;
    }

    // copy the cards
    std::vector<int> cards;

    // try to replace the joker with all the possible values
    // all the 11 are jokers

    int highest_rank = 0;

    for (int i = 2; i <= 14; ++i) {

        // copy the cards
        cards = this->cards;
        
        // replace the joker with the value
        for (int j = 0; j < cards.size(); j++) {
            if (cards[j] == 11) {
                cards[j] = i;
            }
        }
        // sort the cards
        std::sort(cards.begin(), cards.end());
        // check if all the same
        if (cards[0] == cards[4]) {
            highest_rank = std::max(highest_rank, 7);
            continue;
        }

        // check if four of a kind
        if (cards[0] == cards[3] || cards[1] == cards[4]) {
            highest_rank = std::max(highest_rank, 6);
            continue;
        }

        // check if full house
        if ((cards[0] == cards[2] && cards[3] == cards[4]) || (cards[0] == cards[1] && cards[2] == cards[4])) {
            highest_rank = std::max(highest_rank, 5);
            continue;
        }

        // check if three of a kind
        if (cards[0] == cards[2] || cards[1] == cards[3] || cards[2] == cards[4]) {
            highest_rank = std::max(highest_rank, 4);
            continue;
        }

        // check if two pairs
        if ((cards[0] == cards[1] && cards[2] == cards[3]) || (cards[0] == cards[1] && cards[3] == cards[4]) || (cards[1] == cards[2] && cards[3] == cards[4])) {
            highest_rank = std::max(highest_rank, 3);
            continue;
        }

        // check if one pair
        if (cards[0] == cards[1] || cards[1] == cards[2] || cards[2] == cards[3] || cards[3] == cards[4]) {
            highest_rank = std::max(highest_rank, 2);
            continue;
        }

        // high card
        highest_rank = std::max(highest_rank, 1);
    }
    this->rank = highest_rank;
}

void Hand::calculate_rank_nojoker() {
    // Calculate the rank of the hand
    // 1. High card: every card is different
    // 2. One pair: two cards are the same
    // 3. Two pairs: two pairs of cards are the same
    // 4. Three of a kind: three cards are the same
    // 5. Full house: three of a kind and a pair
    // 6. Four of a kind: four cards are the same
    // 7. Five of a kind: five cards are the same

    if (cards.size() != 5) {
        throw std::invalid_argument("Hand must have 5 cards");
    }

    // copy the cards
    std::vector<int> cards = this->cards;

    // Sort the cards
    std::sort(cards.begin(), cards.end());
    // check if all the same
    if (cards[0] == cards[4]) {
        this->rank = 7;
        return;
    }

    // check if four of a kind
    if (cards[0] == cards[3] || cards[1] == cards[4]) {
        this->rank = 6;
        return;
    }

    // check if full house
    if ((cards[0] == cards[2] && cards[3] == cards[4]) || (cards[0] == cards[1] && cards[2] == cards[4])) {
        this->rank = 5;
        return;
    }

    // check if three of a kind
    if (cards[0] == cards[2] || cards[1] == cards[3] || cards[2] == cards[4]) {
        this->rank = 4;
        return;
    }

    // check if two pairs
    if ((cards[0] == cards[1] && cards[2] == cards[3]) || (cards[0] == cards[1] && cards[3] == cards[4]) || (cards[1] == cards[2] && cards[3] == cards[4])) {
        this->rank = 3;
        return;
    }

    // check if one pair
    if (cards[0] == cards[1] || cards[1] == cards[2] || cards[2] == cards[3] || cards[3] == cards[4]) {
        this->rank = 2;
        return;
    }

    // high card
    this->rank = 1;
}

bool Hand::compare_nojoker(const Hand& hand) const {
    if (this->rank == hand.rank) {
        // same rank, compare the cards
        for (int i = 0; i < this->cards.size(); i++) {
            if (this->cards[i] == hand.cards[i]) {
                continue;
            }
            return this->cards[i] < hand.cards[i];
        }
    }
    return this->rank < hand.rank;
}

bool Hand::compare_joker(const Hand& hand) const {

    if (this->rank == hand.rank) {
        // same rank, compare the cards

        // substitute the joker with a one
        std::vector<int> cards = this->cards;
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i] == 11) {
                cards[i] = 1;
            }
        }

        std::vector<int> cards2 = hand.cards;
        for (int i = 0; i < cards2.size(); i++) {
            if (cards2[i] == 11) {
                cards2[i] = 1;
            }
        }

        for (int i = 0; i < cards.size(); i++) {
            if (cards[i] == cards2[i]) {
                continue;
            }
            return cards[i] < cards2[i];
        }
    }
    return this->rank < hand.rank;
}
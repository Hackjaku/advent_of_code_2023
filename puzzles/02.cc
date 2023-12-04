#include <vector>
#include <iostream>

#include "../models/utilities.h"
#include "../models/CubeGame.h"

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14


int main() {
    Utilities utils;
    std::vector<std::string> lines = utils.ParseInput("../inputs/02.txt");

    std::vector<CubeGame> games;
    int id_sum = 0;
    int power_sum = 0;
    for (auto line : lines) {
        CubeGame game(line);
        games.push_back(game);

        id_sum += game.GetId();

        if (game.GetMaxRed() > MAX_RED || game.GetMaxGreen() > MAX_GREEN || game.GetMaxBlue() > MAX_BLUE) {
            id_sum -= game.GetId();
        }

        power_sum += game.GetPower();

    }

    std::cout << "The sum of the valid game ids is " << id_sum << std::endl;
    std::cout << "The sum of the game powers is " << power_sum << std::endl;

    return 0;
}
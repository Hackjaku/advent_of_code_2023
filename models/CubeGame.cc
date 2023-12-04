#include "CubeGame.h"

GameSet::GameSet(std::string game_set) {
    // 3 blue, 4 red
    // 1 red, 2 green, 6 blue
    // 2 green
    // populate accordingly
    // split the string by ", " and determine the color
    // then split the string by " " and determine the number
    this->blue = 0;
    this->green = 0;
    this->red = 0;

    do {
        std::string color = game_set.substr(game_set.find(" ") + 1, game_set.find(",") - game_set.find(" ") - 1);
        // get the number
        std::string number = game_set.substr(0, game_set.find(" "));
        // convert the number to int
        int num = std::stoi(number);
        // populate the color accordingly
        if (color == "blue") {
            this->blue = num;
        } else if (color == "green") {
            this->green = num;
        } else if (color == "red") {
            this->red = num;
        }

        if (game_set.find(",") == std::string::npos) {
            break;
        }

        game_set.erase(0, game_set.find(",") + 2);

    } while (true);
}

CubeGame::CubeGame(std::string game) {
    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

    // get the game id between "Game " and ":" and convert it to int
    std::string game_id = game.substr(game.find("Game ") + 5, game.find(":") - game.find("Game ") - 5);
    this->id = std::stoi(game_id);

    // split all the game sets between the ":" and the end of the string
    std::string game_sets = game.substr(game.find(": ") + 2, game.length() - game.find(":") - 2);
    // for every set (delimited by ";"), create a GameSet object and add it to the vector
    do {
        std::string game_set = game_sets.substr(0, game_sets.find(";"));
        GameSet gs(game_set);
        this->game_sets.push_back(gs);
        if (game_sets.find(";") == std::string::npos) {
            break;
        }
        game_sets.erase(0, game_sets.find(";") + 2);
    } while (true);

    // get the max number of blue, green and red
    // for every game set, get the max number of blue, green and red
    // if the max number of blue, green or red is greater than the current max, replace it
    this->max_blue = 0;
    this->max_green = 0;
    this->max_red = 0;
    for (auto game_set : this->game_sets) {
        if (game_set.GetBlue() > this->max_blue) {
            this->max_blue = game_set.GetBlue();
        }
        if (game_set.GetGreen() > this->max_green) {
            this->max_green = game_set.GetGreen();
        }
        if (game_set.GetRed() > this->max_red) {
            this->max_red = game_set.GetRed();
        }
    }
}
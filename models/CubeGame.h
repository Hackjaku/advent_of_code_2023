#ifndef DAY02_H
#define DAY02_H

#include <iostream>
#include <vector>

class GameSet {
private:
    int blue;
    int green;
    int red;
public:
    // GameSet();
    GameSet(std::string);
    inline int GetBlue() { return this->blue; }
    inline int GetGreen() { return this->green; }
    inline int GetRed() { return this->red; }
};

class CubeGame {
private:
    int id;
    int max_blue;
    int max_green;
    int max_red;
    int power;
    std::vector<GameSet> game_sets;

public:
    // CubeGame();
    CubeGame(std::string);
    inline int GetId() { return this->id; }
    inline int GetMaxRed() { return this->max_red; }
    inline int GetMaxGreen() { return this->max_green; }
    inline int GetMaxBlue() { return this->max_blue; }
    inline int GetPower() { return this->max_blue * this->max_green * this->max_red; }
};

#endif // DAY02_H
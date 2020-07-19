#pragma once

#include <string>

#include "Clock.hpp"

struct Player {
    int x;
    int y;
    int score;
};

struct Ball {
    int x;
    int y;
    int xv;
    int yv;
    int l;
};

class Logic {
public:
    Logic();
    void Update();
    void TakeInput(int player, std::string input);
    bool GameFull();
private:
    Clock clock;

    Ball ball;
    Player p1;
    Player p2;
    int paddle_vy;
    int paddle_width;
    int paddle_height;
};
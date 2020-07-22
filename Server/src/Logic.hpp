#pragma once

#include <string>
#include <iostream>

#include "Clock.hpp"

struct Player {
    int x;
    int y;
    int score;
    std::string name;
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
    void NewPlayer();
    void Update();
    void TakeInput(int player, std::string input);
    std::string GetNetworkMsg();
    bool GameFull();
private:
    int window_length;
    Clock clock;

    Ball ball;
    Player p1;
    Player p2;
    int paddle_vy;
    int paddle_width;
    int paddle_height;

    std::string network_msg;
};
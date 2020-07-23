#pragma once

#include <string>
#include <iostream>

#include "Clock.hpp"

struct Player {
    float x;
    float y;
    int score;
    int direction;
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
    void NewPlayer();                              // If another player can join, the player's info is setup
    void Update();
    void UpdateBall();
    void UpdatePaddles();
    void TakeInput(int player, std::string input);
    std::string GetNetworkMsg();                   // Returns message to send to all connected players
    bool GameFull();                               // Checks if another player can join
private:
    int window_length;
    Clock clock;

    Ball ball;
    Player p1;
    Player p2;
    float paddle_vy;
    int paddle_width;
    int paddle_height;

    std::string network_msg;
};
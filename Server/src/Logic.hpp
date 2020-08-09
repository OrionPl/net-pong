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
    int NewPlayer_GetIndex();                       // sets up a new player and returns the index of that new player, i.e. 0 or 1
    void SetPlayerName(int p_index, std::string name);
    void RemovePlayer(int p_index);
    void Update();
    void UpdateBall();
    void UpdatePaddles();
    void TakeInput(int player, std::string input);
    void PauseGame();
    void UnpauseGame();
    std::string GetNetworkMsg();                   // Returns message to send to all connected players
private:
    int window_length;
    Clock clock;

    Ball ball;
    Player p1;
    Player p2;
    float paddle_vy;
    int paddle_width;
    int paddle_height;
    int default_offscreen_v;
    bool game_paused;


    std::string network_msg;
};
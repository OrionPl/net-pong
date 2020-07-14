#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Ball.hpp"

struct Paddle {
    float x;
    float y;
    int score;
};

class Paddles {
public:
    Paddles(int window_length);
    void Draw(SDL_Renderer* renderer);
    void Update(double dt, const Uint8* keys_down, Ball* ball);
    int GetScore1();
    int GetScore2();
private:
    SDL_Rect m_rect;
    Paddle m_paddle1;
    Paddle m_paddle2;
    int m_yv;
    int m_window_length;
};

#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Ball.hpp"

struct Paddle {
    float x;
    float y;
};

class Paddles {
public:
    Paddles(int window_length);
    void Draw(SDL_Renderer* renderer);
    void SetPaddle(int index, float x, float y);
private:
    SDL_Rect m_rect;
    Paddle m_paddle1;
    Paddle m_paddle2;
    int m_yv;
    int m_window_length;
};

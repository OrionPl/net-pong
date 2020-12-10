#pragma once

#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "GlobalData.hpp"
#include "Ball.hpp"

struct Paddle {
    float x;
    float y;
};

class Paddles {
public:
    Paddles();
    void Draw();
    void SetPaddles(float x1, float y1, float x2, float y2);
private:
    SDL_Rect m_rect;
    Paddle m_paddle1;
    Paddle m_paddle2;
    int m_yv;
};

#pragma once

#include <SDL2/SDL.h>
#include "Score.hpp"

class Ball {
public:
    Ball(int window_length);
    void Draw(SDL_Renderer* renderer);
    void Update(double dt, Score* score);
    void ReactToPaddle(float x, float y, int w, int h);
private:
    bool AABB(float x, float y, int w, int h, float x2, float y2, int w2, int h2);
    SDL_Rect m_rect;
    float m_x;
    float m_y;
    float m_old_x;
    float m_old_y;
    int m_initial_xv;
    int m_initial_yv;
    float m_xv;
    float m_yv;
    int m_window_length;
};

#pragma once

#include <SDL2/SDL.h>
//#include "Score.hpp"

#include "GlobalData.hpp"

class Ball {
public:
    Ball();
    void Draw();
    void SetPosition(float x, float y);
    //void Update(double dt, Score* score);
    //void ReactToPaddle(float x, float y, int w, int h);
private:
    SDL_Rect m_rect;
    float m_x;
    float m_y;
    float m_old_x;
    float m_old_y;
    int m_initial_xv;
    int m_initial_yv;
    float m_xv;
    float m_yv;
};

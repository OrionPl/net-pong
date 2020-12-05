#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GlobalWindowData.hpp"
#include "Text.hpp"

struct Score {

    Score(Text* _text);
    void Draw();
    void p1();
    void p2();
    void DestroyTextures();

    Text* text;

    SDL_Texture* texture_1;
    SDL_Texture* texture_2;
    SDL_Rect score_1_rect;
    SDL_Rect score_2_rect;
    int score_1;
    int score_2;
};
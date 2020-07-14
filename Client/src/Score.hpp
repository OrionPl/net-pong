#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <String>

class Score {
public:
    Score(SDL_Renderer* renderer);
    void Draw();
    void p1();
    void p2();
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture_1;
    SDL_Texture* m_texture_2;
    SDL_Rect m_score_1_rect;
    SDL_Rect m_score_2_rect;
    int m_score_1;
    int m_score_2;
    TTF_Font* m_font;
    SDL_Color m_color_white;
};
#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Text {
public:
    static void LoadFont();
    static void DestroyFont();
    static SDL_Texture* CreateTexture(SDL_Renderer* renderer, std::string text);
private:
    static TTF_Font* main_font;
    static constexpr SDL_Color white_color = {255, 255 ,255};
};
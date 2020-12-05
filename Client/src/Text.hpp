#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pch.h"

struct Text {
    void SetFontSize(int font_size);
    SDL_Texture* CreateTexture(SDL_Renderer* renderer, std::string text, int font_size, bool underlined = false);

    TTF_Font* font;
};
#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//TODO Change this class to Font and make Text a UIElement

struct Font {
public:
    Font(std::string fontDir, int fontSize, SDL_Color* _color);
    ~Font();

    void ChangeFont(std::string fontDir, int fontSize);
    void SetColor(SDL_Color* _color) { color = _color; };
    SDL_Texture* CreateTexture(SDL_Renderer* renderer, std::string text);
private:
    TTF_Font* font;
    SDL_Color* color;
    void DestroyFont();
};
#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Text.hpp"

class Menu {
public:
    Menu(SDL_Renderer* _renderer);
    void Draw();
    void MousePressed(int x, int y);
private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> text_textures;
    std::vector<SDL_Rect> text_rects;
    std::vector<int> button_indexes;
};
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GlobalWindowData.hpp"

class Window {
public:
    Window();
    void Clear();
    void Shutdown();
private:
    SDL_Window* window;
    SDL_Surface* icon;
};
#pragma once

#include <SDL2/SDL.h>

struct GlobalWindowData {
    int w;
    int h;
    SDL_Renderer* rdr;
};

extern GlobalWindowData global_window_data;
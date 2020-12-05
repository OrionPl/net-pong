#pragma once

#include <SDL2/SDL.h>

struct GlobalWindowData {
    int w;
    int h;
    int mx;
    int my;
    SDL_Renderer* rdr;
};

extern GlobalWindowData g_data;
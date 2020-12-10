#pragma once

#include <SDL2/SDL.h>

enum States {
    START_SCREEN,
    GAME
};

struct GlobalData {

    States cur_state = START_SCREEN;
    int ww = 500;
    int wh = 500;

    int mx;
    int my;
    SDL_Renderer* rdr;
};

extern GlobalData g_data;
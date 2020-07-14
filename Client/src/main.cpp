#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Clock.cpp"

#include "Window.hpp"
#include "Ball.hpp"
#include "Paddles.hpp"
#include "Score.hpp"


int main(int argc, char* argv[]) {
    TTF_Init();

    Window window;
    Ball ball(window.GetWindowLength());
    Paddles paddles(window.GetWindowLength());
    Score score(window.GetRenderer());

    Clock clock;
    SDL_Event event;
    const Uint8* keys_down = SDL_GetKeyboardState(NULL);

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;
                    break;
                default: break;
            }
        }
        clock.tick();

        ball.Update(clock.dt, &score);
        paddles.Update(clock.dt, keys_down, &ball);


        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.GetRenderer());
        SDL_SetRenderDrawColor(window.GetRenderer(), 255, 255, 255, 255);

        ball.Draw(window.GetRenderer());
        paddles.Draw(window.GetRenderer());
        score.Draw();

        SDL_RenderPresent(window.GetRenderer());
    }

    window.Shutdown();
    return 0;
}
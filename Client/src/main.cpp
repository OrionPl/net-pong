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

#include "Networking.hpp"


int main(int argc, char* argv[]) {
    TTF_Init();

    Window window;
    Ball ball(window.GetWindowLength());
    Paddles paddles(window.GetWindowLength());
    Score score(window.GetRenderer());

    Networking net("127.0.0.1", 66666, "orion1", &paddles);

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

        if (keys_down[SDL_SCANCODE_UP]) {
            net.Send("^");
        } else if (keys_down[SDL_SCANCODE_DOWN]) {
            net.Send("v");
        }


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
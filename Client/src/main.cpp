#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

    SDL_Event event;
    const Uint8* keys_down = SDL_GetKeyboardState(NULL);

    bool quit = false;
    while (!quit) {

        // UPDATE

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

        // Send no keys down if neither keys are down or both keys are down
        if ((keys_down[SDL_SCANCODE_UP] && keys_down[SDL_SCANCODE_DOWN]) || (!keys_down[SDL_SCANCODE_UP] && !keys_down[SDL_SCANCODE_DOWN])) {
            net.Send("-");
        } else {
            // ^ = up
            // v = down
            // ternary is possible because this code block can only have (down_arrow_down and up_arrow_up OR up_arrow_down and down_arrow_up)
            net.Send(keys_down[SDL_SCANCODE_UP] ? "^": "v");
        }



        // DRAW

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
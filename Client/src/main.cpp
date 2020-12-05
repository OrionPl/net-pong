#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "GlobalWindowData.hpp"
#include "Text.hpp"
#include "Menu.hpp"
#include "Ball.hpp"
#include "Paddles.hpp"
//#include "Score.hpp"
#include "Networking.hpp"

GlobalWindowData g_data = {500, 500, NULL, NULL, NULL};

// void ConnectToServer(Networking* net) {
//     if (net.Connect("127.0.0.1", 55555, "orion1"))
//         in_game = true;
// }


int main(int argc, char* argv[]) {
    TTF_Init();

    Window window;
    Text text;

    Menu menu(& text);

    Ball ball;
    Paddles paddles;
    Networking net(& paddles, & ball);

    bool in_game = false;

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
                    if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                default: break;
            }
        }

        if (in_game) {

            // Directions:
            // -1 : up
            //  1 : down
            //  0 : no movement

            // Send no keys down if neither keys are down or both keys are down.
            if ((keys_down[SDL_SCANCODE_UP] && keys_down[SDL_SCANCODE_DOWN]) || (!keys_down[SDL_SCANCODE_UP] && !keys_down[SDL_SCANCODE_DOWN])) {
                net.Send("0");
            } else {
                // ternary is possible because this code block can only have (down_arrow_down and up_arrow_up OR up_arrow_down and down_arrow_up).
                net.Send(keys_down[SDL_SCANCODE_UP] ? "-1": "1");
            }

        }

        SDL_GetMouseState(& g_data.mx, & g_data.my);
        menu.Update();


        // DRAW

        window.Clear();

        menu.Draw();
        ball.Draw();
        paddles.Draw();

        SDL_RenderPresent(g_data.rdr);
    }

    window.Shutdown();
    SDL_Quit();
    return 0;
}
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
//#include "UI/UI.hpp"

GlobalWindowData global_window_data = {500, 500, NULL};

bool tru = false;

void BtnHandler() {
    PRINT "btn click\n";
    tru = true;
}

int main(int argc, char* argv[]) {
    TTF_Init();
    Text::LoadFont();

    Window window;
    Ball ball;
    Paddles paddles;
    //Score score;

    // UI Initialization

    // UI ui = UI(global_window_data.rdr);

    // SDL_Color white = {255, 255, 255};
    // SDL_Color black = {0, 0, 0};

    // Font fnt1("assets/font.ttf", 60, & white);
    // Font fnt2("assets/font.ttf", 30, & black);

    // Button btn("btn", true, 0, 80, 80, 80, 80, false, white, global_window_data.rdr, &BtnHandler, "asd", & fnt1);
    // Text title("txt", true, 0, 15, 15, 280, 160, false, white, global_window_data.rdr, "pong", & fnt1);

    // ui.AddUIElement<Button>(&btn);
    //ui.AddUIElement<Text>(& title);
    Menu menu;

    bool connected_to_server = false;
    Networking net(&paddles, &ball);
    if (connected_to_server) net.Connect("127.0.0.1", 55555, "orion1");

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
                case SDL_MOUSEBUTTONDOWN:
                    //menu.MousePressed(event.button.x, event.button.y);
                    // btn.Click(event.button.x, event.button.y);
                    break;
                default: break;
            }
        }

        if (connected_to_server) {

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


        // DRAW

        window.Clear();

        ball.Draw();
        if (tru)
            paddles.Draw();
        //score.Draw();
        menu.Draw();

        SDL_RenderPresent(global_window_data.rdr);
    }

    //score.DestroyTextures();
    //Text::DestroyFont();
    TTF_Quit();
    window.Shutdown();
    SDL_Quit();
    return 0;
}
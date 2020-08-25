#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "GlobalWindowData.hpp"
//#include "Text.hpp"
//#include "Menu.hpp"
#include "Ball.hpp"
#include "Paddles.hpp"
//#include "Score.hpp"
#include "Networking.hpp"
#include "UI/UI.hpp"

GlobalWindowData global_window_data = {500, 500, NULL};

Window window;
Ball ball;
Paddles paddles;
Text* info_text;
Networking* net;
std::string ip = "127.0.0.1";
int port = 55555;
std::string name = "orion1";
bool in_game = false;

void ConnectToServer() {
    net = new Networking(&paddles, &ball);

    if (net->Connect(ip, port, name))
        in_game = true;
    else
        delete net;
}

void DisconnectFromServer() {
    delete net;
    in_game = false;
}

void GameLoop();

void MenuLoop() {
    UI menu_ui = UI(global_window_data.rdr);

    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};

    Font fnt1("assets/font.ttf", 18, & white);
    Font fnt2("assets/font.ttf", 60, & white);

    //Menu ui elements
    menu_ui.AddUIElement<Text>(info_text);

    Text title("txt", true, 0, 15, 15, 280, 160, false, white, global_window_data.rdr, "pong", & fnt2);
    menu_ui.AddUIElement<Text>(& title);

    Button connBtn("btn", true, 0, 15, 190, 160, 80, false, white, global_window_data.rdr, &ConnectToServer, "Connect", & fnt1);
    menu_ui.AddUIElement<Button>(&connBtn);

    SDL_Event event;
    const Uint8* keys_down = SDL_GetKeyboardState(NULL);

    bool quit = false;
    while (!quit && !in_game) {

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
                    connBtn.Click(event.button.x, event.button.y);
                    break;
                default: break;
            }
        }

        // DRAW

        window.Clear();

        //ball.Draw();
        //if (tru)
        //    paddles.Draw();
        //score.Draw();
        // menu.Draw();
        menu_ui.Draw();

        SDL_RenderPresent(global_window_data.rdr);
    }

    if (!quit)
        GameLoop();
}

void GameLoop() {
    UI game_ui = UI(global_window_data.rdr);

    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};

    Font fnt1("assets/font.ttf", 18, & white);
    Font fnt2("assets/font.ttf", 30, & white);

    //Game ui elements
    game_ui.AddUIElement<Text>(info_text);
    
    Button dis_conn_btn("dconBtn", true, 0, 80, 80, 80, 80, false, white, global_window_data.rdr, &DisconnectFromServer, "Disconnect", &fnt1);
    game_ui.AddUIElement<Button>(&dis_conn_btn);
    
    SDL_Event event;
    const Uint8* keys_down = SDL_GetKeyboardState(NULL);

    bool quit = false;
    while (!quit && in_game) {

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
                    dis_conn_btn.Click(event.button.x, event.button.y);
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
                net->Send("0");
            } else {
                // ternary is possible because this code block can only have (down_arrow_down and up_arrow_up OR up_arrow_down and down_arrow_up).
                net->Send(keys_down[SDL_SCANCODE_UP] ? "-1": "1");
            }

        }


        // DRAW

        window.Clear();

        ball.Draw();
        paddles.Draw();
        //score.Draw();
        // menu.Draw();
        game_ui.Draw();

        SDL_RenderPresent(global_window_data.rdr);
    }

    if (!quit)
        MenuLoop();
}

int main(int argc, char* argv[]) {
    TTF_Init();

    SDL_Color white = {255, 255, 255};
    Font fnt1("assets/font.ttf", 60, &white);

    info_text = new Text("infoText", true, 0, 500, 540, 100, 60, false, white, global_window_data.rdr, "ERROR BOX", &fnt1);
    
    MenuLoop();

    TTF_Quit();
    window.Shutdown();
    SDL_Quit();
    return 0;
}
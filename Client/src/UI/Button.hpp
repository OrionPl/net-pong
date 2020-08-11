#pragma once

#include <SDL2/SDL.h>

class Button {
public:
    Button(int sizeX, int sizeY, int posX, int posY); // PosX and PosY are both positions of the top left corner of the button
    Button(int sizeX, int sizeY, int posX, int posY, void (*_eventHandler));
    Button(int sizeX, int sizeY, int posX, int posY, void (*_eventHandler), SDL_Texture* _texture);
    Button(int sizeX, int sizeY, int posX, int posY, void (*_eventHandler), SDL_Texture* _texture, std::string );

    void Click(int mousePosX, int mousePosY); // Check if the mouse clicked the button
    void SetHandler(void (*_eventHandler)) { eventHandler = _eventHandler; }; // Set the function you want to handle the click of the button
private:
    void (*eventHandler);
}
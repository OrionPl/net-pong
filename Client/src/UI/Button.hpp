#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL2/SDL.h>

#include "UIElement.hpp"
#include "Font.hpp"

class UIElement;

class Button : public UIElement {
public:
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer); // PosX and PosY are both positions of the top left corner of the button
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, void (*_eventHandler)());
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, void (*_eventHandler)(), std::string _text, Font* text);
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, std::string _text, Font* text);

    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer); // PosX and PosY are both positions of the top left corner of the button
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, void (*_eventHandler)());
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, void (*_eventHandler)(), std::string _text, Font* text);
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, std::string _text, Font* text);

    void Draw();
    void Click(int mousePosX, int mousePosY); // Check if the mouse clicked the button
    void SetHandler(void (*_eventHandler)()) { eventHandler = _eventHandler; }; // Set the function you want to handle the click of the button
    void SetText(std::string _text, Font* text);
private:
    void (* eventHandler)();
    SDL_Texture* textTexture;
};
#endif
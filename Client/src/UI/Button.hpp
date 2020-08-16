#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL2/SDL.h>

#include "UI.hpp"

class UIElement;

class Button : public UIElement {
public:
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui); // PosX and PosY are both positions of the top left corner of the button
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, void (*_eventHandler));
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, void (*_eventHandler), std::string text);
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, std::string text);

    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui); // PosX and PosY are both positions of the top left corner of the button
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, void (*_eventHandler));
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, void (*_eventHandler), std::string text);
    Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, std::string text);

    void Click(int mousePosX, int mousePosY); // Check if the mouse clicked the button
    void SetHandler(void (*_eventHandler)) { eventHandler = _eventHandler; }; // Set the function you want to handle the click of the button
private:
    void (*eventHandler);
};
#endif
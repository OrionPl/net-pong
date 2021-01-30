#pragma once

#include <SDL2/SDL.h>

#include "UIElement.hpp"
#include "Font.hpp"

class UIElement;

class Text : public UIElement {
public:
    Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer);
    Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, std::string _text, Font* text);

    Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer);
    Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, std::string _text, Font* text);

    void Draw();
    void SetText(std::string _text);
    void SetText(std::string _text, Font* text);
private:
    SDL_Texture* textTexture;
    Font* font;
};
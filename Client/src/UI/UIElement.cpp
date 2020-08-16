#include "UIElement.hpp"

UIElement::UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer) {
    name = _name;
    active = _active;
    uiAnchor = _uiAnchor;
    xPos = _xPos;
    yPos = _yPos;
    xSize = _xSize;
    ySize = _ySize;
    texture = _texture;
    renderer = _renderer;

    backgroundType = UI_BACKGROUND_TEXTURED;
}

UIElement::UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer) {
    name = _name;
    active = _active;
    uiAnchor = _uiAnchor;
    xPos = _xPos;
    yPos = _yPos;
    xSize = _xSize;
    ySize = _ySize;
    filled = _filled;
    color = _color; //TODO Color of the background (rect color) (NOT GLOBAL COLOR)
    renderer = _renderer;

    if (filled)
        backgroundType = UI_BACKGROUND_RECT_FILLED;
    else
        backgroundType = UI_BACKGROUND_RECT_UNFILLED;
}

void UIElement::Draw() { // TODO Make anchor work
    if (active) {
        SDL_Rect rect;
            rect.x = xPos;
            rect.y = yPos;
            rect.w = xSize;
            rect.h = ySize;

        switch(backgroundType) {
            case UI_BACKGROUND_TEXTURED:
                SDL_RenderCopy(renderer, texture, NULL, &rect);
                break;
            case UI_BACKGROUND_RECT_UNFILLED:
                SDL_RenderDrawRect(renderer, &rect);
                break;
            case UI_BACKGROUND_RECT_FILLED:
                SDL_RenderFillRect(renderer, &rect);
                break;
        }
    }
}
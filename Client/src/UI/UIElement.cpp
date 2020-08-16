#include "UIElement.hpp"

UIElement::UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui) {
    name = _name;
    active = _active;
    uiAnchor = _uiAnchor;
    xPos = _xPos;
    yPos = _yPos;
    xSize = _xSize;
    ySize = _ySize;
    texture = _texture;
    ui = _ui;

    backgroundType = UI_BACKGROUND_TEXTURED;
}

UIElement::UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui) {
    name = _name;
    active = _active;
    uiAnchor = _uiAnchor;
    xPos = _xPos;
    yPos = _yPos;
    xSize = _xSize;
    ySize = _ySize;
    filled = _filled;
    color = _color; //TODO Color of the background (rect color) (NOT GLOBAL COLOR)
    ui = _ui;

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
                SDL_RenderCopy(ui->GetRenderer(), texture, NULL, &rect);
                break;
            case UI_BACKGROUND_RECT_UNFILLED:
                SDL_RenderDrawRect(ui->GetRenderer(), &rect);
                break;
            case UI_BACKGROUND_RECT_FILLED:
                SDL_RenderFillRect(ui->GetRenderer(), &rect);
                break;
        }
    }
}
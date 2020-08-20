#include "Button.hpp"

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {
    
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, void (*_eventHandler)()) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {
    eventHandler = _eventHandler;
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, void (*_eventHandler)(), std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {
    eventHandler = _eventHandler;    
    textTexture = text->CreateTexture(renderer, _text);
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {
    textTexture = text->CreateTexture(renderer, _text);
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {

}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, void (*_eventHandler)()) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {
    eventHandler = _eventHandler;
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, void (*_eventHandler)(), std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {
    eventHandler = _eventHandler;
    textTexture = text->CreateTexture(renderer, _text);
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {
    textTexture = text->CreateTexture(renderer, _text);
}

void Button::Draw() {
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

        if (textTexture)
            SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    }
}

void Button::Click(int mousePosX, int mousePosY) {
    if (mousePosX >= xPos && mousePosX <= (xPos + xSize) && mousePosY >= yPos && mousePosY <= (yPos + ySize))
        eventHandler();
}

void Button::SetText(std::string _text, Font* text) {
    textTexture = text->CreateTexture(renderer, _text);
}
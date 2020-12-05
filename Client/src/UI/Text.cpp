#include "Text.hpp"

Text::Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {

}

Text::Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, SDL_Renderer* _renderer, std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _renderer) {
    textTexture = text->CreateTexture(renderer, _text);
    font = text;
}

Text::Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {

}

Text::Text(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, SDL_Renderer* _renderer, std::string _text, Font* text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _renderer) {
    textTexture = text->CreateTexture(renderer, _text);
    font = text;
}

void Text::Draw() {
    if (active) {
        SDL_Rect rect;
        rect.x = xPos;
        rect.y = yPos;
        rect.w = xSize;
        rect.h = ySize;

        SDL_Rect text_rect;
        int tw, th;
        SDL_QueryTexture(textTexture, NULL, NULL, &tw, &th);
        text_rect.x = xPos + (xSize / 2) - (tw / 2);
        text_rect.y = yPos + (ySize / 2) - (th / 2);
        text_rect.w = tw;
        text_rect.h = th;

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
            SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
    }
}

void Text::SetText(std::string _text) {
    textTexture = font->CreateTexture(renderer, _text);
}

void Text::SetText(std::string _text, Font* text) {
    textTexture = text->CreateTexture(renderer, _text);
    font = text;
}
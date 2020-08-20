#include "Text.hpp"

Text::Text(std::string fontDir, int fontSize, SDL_Color* _color) {
    font = TTF_OpenFont(fontDir.c_str(), fontSize);
    if (!font) SDL_Log("can't load font");
    color = _color;
}

Text::~Text() {
    DestroyFont();
}

void Text::ChangeFont(std::string fontDir, int fontSize) {
    DestroyFont();
    font = TTF_OpenFont(fontDir.c_str(), fontSize);
    if (!font) SDL_Log("can't load font");
}

SDL_Texture* Text::CreateTexture(SDL_Renderer* renderer, std::string text) {
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), *color);
    if (!temp_surface) SDL_Log("Failed to create surface of font\n");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    
    SDL_FreeSurface(temp_surface);
    
    return texture;
}

void Text::DestroyFont() {
    TTF_CloseFont(font);
}
#include "Text.hpp"

void Text::SetFontSize(int font_size) {
    if (font) TTF_CloseFont(font);
    font = TTF_OpenFont("assets/font.ttf", 35);
    if (!font) SDL_Log("can't load font");
}

SDL_Texture* Text::CreateTexture(SDL_Renderer* renderer, std::string text, int font_size, bool underlined) {
    SetFontSize(font_size);
    if (underlined) TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE); else TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), CLR_WHITE);
    if (!temp_surface) SDL_Log("failed to create surface\n");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}
#include "Text.hpp"


constexpr SDL_Color Text::white_color;
TTF_Font* Text::main_font;

void Text::LoadFont() {
    main_font = TTF_OpenFont("assets/font.ttf", 35);
    if (!main_font) SDL_Log("can't load font");

}

void Text::DestroyFont() {
    TTF_CloseFont(main_font);
}

SDL_Texture* Text::CreateTexture(SDL_Renderer* renderer, std::string text) {
    SDL_Surface* temp_surface = TTF_RenderText_Solid(main_font, text.c_str(), white_color);
    if (!temp_surface) SDL_Log("failed to create surface\n");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}
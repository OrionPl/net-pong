#include "Menu.hpp"

Menu::Menu(SDL_Renderer* _renderer) {
    renderer = _renderer;

    //Text text("assets/font.ttf", 35); // TODO Move to main.cpp (or InitializeAssets()) and name pixel_font or main_font or menu_font

    SDL_Texture* title_texture = Text::CreateTexture(renderer, "Net Pong");
    //SDL_Texture* title_texture = text.CreateTexture(renderer, "Net Pong");
    SDL_Rect title_rect;
    SDL_QueryTexture(title_texture, NULL, NULL, & title_rect.w, & title_rect.h);
    title_rect.x = title_rect.y = 15;

    text_textures.push_back(title_texture);
    text_rects.push_back(title_rect);



    SDL_Texture* connect_texture = Text::CreateTexture(renderer, "Connect");
    //SDL_Texture* connect_texture = text.CreateTexture(renderer, "Connect");
    SDL_Rect connect_rect;
    SDL_QueryTexture(connect_texture, NULL, NULL, & connect_rect.w, & connect_rect.h);
    connect_rect.x = 15;
    connect_rect.y = 155;

    text_textures.push_back(connect_texture);
    text_rects.push_back(connect_rect);
    button_indexes.push_back(text_textures.size() - 1);
}

void Menu::Draw() {
    for (unsigned int i = 0; i < text_textures.size(); i++) {
        SDL_RenderCopy(renderer, text_textures[i], NULL, & text_rects[i]);
    }
}

void Menu::MousePressed(int x, int y) {
    for (int i : button_indexes) {
        if (x > text_rects[i].x && x < text_rects[i].x + text_rects[i].w && y > text_rects[i].y && y < text_rects[i].y + text_rects[i].h) {
            // do some shit
        }
    }
}
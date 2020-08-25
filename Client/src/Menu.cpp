#include "Menu.hpp"

Menu::Menu() {
    AddItem(15, 15, 300, 300, "hello", NULL);
}

void Menu::Draw() {
    SDL_Rect iter_pos;
    for (unsigned int i = 0; i < items.xs.size(); i++) {
        iter_pos = {items.xs[i], items.ys[i], items.ws[i], items.hs[i]};
        SDL_RenderCopy(global_window_data.rdr, items.textures[i], NULL, & iter_pos);
    }
}

void Menu::MousePressed(int x, int y) {
    for (unsigned int i = 0; i < items.functions.size(); i++) {
        if (items.functions[i] != NULL && x > items.xs[i] && x < items.xs[i] + items.ws[i] && y > items.ys[i] && y < items.ys[i] + items.hs[i]) {
            // do some shit
        }
    }
}

void Menu::DestroyTextures() {
    for (unsigned int i = 0; i < items.textures.size(); i++) {
        SDL_DestroyTexture(items.textures[i]);
    }
}

inline void Menu::AddItem(int x, int y, int w, int h, std::string text, void(*function)()) {
    items.xs.push_back(x);
    items.ys.push_back(y);
    items.ws.push_back(w);
    items.hs.push_back(h);

    SDL_Texture* main_texture = SDL_CreateTexture(global_window_data.rdr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_Texture* text_texture = Text::CreateTexture(global_window_data.rdr, text);

    int text_w, text_h;
    SDL_QueryTexture(text_texture, NULL, NULL, & text_w, & text_h);
    SDL_Rect text_rect = {(w - text_w) / 2, (h - text_h) / 2, text_w, text_h};
    SDL_Rect outline_rect = {0, 0, w, h};
    SDL_SetRenderTarget(global_window_data.rdr, main_texture);
    SDL_RenderCopy(global_window_data.rdr, text_texture, NULL, & text_rect);
    SDL_RenderDrawRect(global_window_data.rdr, & outline_rect);
    SDL_SetRenderTarget(global_window_data.rdr, NULL);

    items.textures.push_back(main_texture);
}